/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

// Global variables
var services = {};

// Change available options when timer event type is changed
timerTypeSelector.selected.connect(
    function() {
        if (timerTypeSelector.currentIndex == 0) {
            timerStartDateSelector.enabled = true;
            timerEndDateSelector.enabled = true;
            timerDaysSelector.enabled = false;
        }
        else {
            timerStartDateSelector.enabled = false;
            timerEndDateSelector.enabled = false;
            timerDaysSelector.enabled = true;
        }
    }
);

function dateTimeToString(dateTime) {
    /* Format a JS date to a string in "day/month/year hours:mins" format */

    return dateTime.getDate()
            + "/"
            + (dateTime.getMonth() + 1)
            + "/"
            + dateTime.getFullYear()
            + " "
            + dateTime.getHours()
            + ":"
            + dateTime.getMinutes()
}

function keyNav(event) {
    /* Respond to key press event */

    switch (event.key) {
    case Qt.Key_Left:
        pageStack.previousPage();
        return;
    case Qt.Key_Right:
        pageStack.nextPage();
        return;
    default:
        return;
    }
}

function sendRemoteKey(key) {
    /* Send a remote key event to the DreamBox */

    http.get(ipaddress + "/cgi-bin/rc?" + key);
}

function setVolume(volume) {
    http.get(ipaddress + "/setVolume?volume=" + volume);
}

function toggleMute(xy) {
    http.get(ipaddress + "/setVolume?mute=" + xy);
}

function loadServices(ref, callback) {
    http.get(ipaddress + "/cgi-bin/getServices?ref=" + ref, {}, callback ? callback : "");
}

function populateServices(response) {
    var list = response.split("\n");

    for (var i = 0; i < list.length; i++) {
        var s = list[i].split(";");
        services[s[1]] = s[0];
    }
}

function loadBouquets() {
    bouquetSelector.clear();
    timerBouquetSelector.clear();
    loadServices(services["Bouquets (TV)"], populateBouquetList);
}

function populateBouquetList(response) {
    bouquetSelector.addItem(qsTr("All services"), services["All services (TV)"]);
    bouquetSelector.addItem(qsTr("History"), services["History"]);
    timerBouquetSelector.addItem(qsTr("All services"), services["All services (TV)"]);
    timerBouquetSelector.addItem(qsTr("History"), services["History"]);

    var list = response.split("\n");

    for (var i = 0; i < list.length - 1; i++) {
        var s = list[i].split(";");
        bouquetSelector.addItem(s[1], s[0]);
        timerBouquetSelector.addItem(s[1], s[0]);
    }

    bouquetSelector.sort();
    timerBouquetSelector.sort();
}

function loadChannels(bouquet) {
    channelListView.clear();
    loadServices(bouquet, populateChannelList);
}

function populateChannelList(response) {
    var list = response.split("\n");

    for (var i = 0; i < list.length - 1; i++) {
        var s = list[i].split(";");
        channelListView.addItem(s[1], s[0]);
    }

    channelListView.sort();
}

function switchChannel(xy) {
    http.get(ipaddress + "/cgi-bin/zapTo?path=" + xy);
}

function getEPG(ref) {
    http.get(ipaddress + '/getcurrentepg?type=extended' + (ref ? "&ref=" + ref : ""), {}, function (epg) { loadInfo(qsTr("EPG"), epg); });
}

function getMultiEPG(ref) {
    http.get(ipaddress + '/getMultiEPG?ref=' + ref, {}, function (epg) { loadInfo(qsTr("Multi EPG"), epg); });
}

function getStreamInfo() {
    http.get(ipaddress + "/cgi-bin/streaminfo", {}, function (info) { loadInfo(qsTr("Stream info"), info); });
}

function getChannelInfo() {
    http.get(ipaddress + "/cgi-bin/channelinfo", {}, function (info) { loadInfo(qsTr("Channel info"), info); });
}

function loadInfo(title, info) {
    infoDialog.title = title;
    infoLabel.text = info;
    infoDialog.open();
}

function DVRrecord(command) {
    http.get(ipaddress + "/cgi-bin/videocontrol?command=" + command);
}

function sendMessageToTV(message) {
    http.get(ipaddress + "/cgi-bin/message?message=" + message);
    messageField.clear();
}

function getScreenShot() {
    screenshotImage.source = "";
    http.get(ipaddress + "/body?mode=controlScreenShot", {}, loadScreenShot);
}

function loadScreenShot(response) {
    var ratio = response.match(/\d+:\d+/)[0].split(":");

    if (ratio.length === 2) {
        screenshotImage.height = Math.floor(screenshotImage.width * (parseInt(ratio[1]) / parseInt(ratio[0])));
    }

    screenshotImage.source = ipaddress + "/root/tmp/screenshot.bmp";
}

function loadTimerChannels(bouquet) {
    timerChannelSelector.clear();
    loadServices(bouquet, populateTimerChannelList);
}

function populateTimerChannelList(response) {
    var list = response.split("\n");

    for (var i = 0; i < list.length - 1; i++) {
        var s = list[i].split(";");
        timerChannelSelector.addItem(s[1], s[0]);
    }

    timerChannelSelector.sort();
}

function getTimerEvents() {
    timerList.clear();
    http.get(ipaddress + "/body?mode=timers", {}, loadTimerEvents);
}

function loadTimerEvents(response) {
    var links = response.match(/editLink = escape\('[^']+/g);

    if (links) {
        for (var i = 0; i < links.length; i++) {
            var link = decodeURIComponent(links[0]);
            var ref = link.split("ref=")[1].split("&")[0];
            var channel = link.split("channel=")[1].split("&")[0];
            var start = parseInt(link.split("start=")[1].split("&")[0]);
            var duration = parseInt(link.split("duration=")[1].split("&")[0]);
            var description = link.split("descr=")[1].split("&")[0];
            var type = link.split("type=")[1].split("&")[0];
            var data = { "ref": ref, "channel": channel, "start": start, "duration": duration, "descr": description, "type": type };
            var date = new Date(start * 1000);
            var startString = dateTimeToString(date);
            date.setTime((start + duration) * 1000);
            var endString = dateTimeToString(date);
            timerList.addItem(channel + ": " + startString + " - " + endString, data);
        }
    }

    if (timerList.count > 0) {
        cleanupTimersButton.enabled = true;
        clearTimersButton.enabled = true;
    }
    else {
        cleanupTimersButton.enabled = false;
        clearTimersButton.enabled = false;
    }
}

function addTimerEvent() {
    var url = ipaddress + "/addTimerEvent?timer=" + timerTypeSelector.currentValue + "&ref=" + timerChannelSelector.currentValue + "&channel=" + timerChannelSelector.currentValueText + "&descr=" + timerDescriptionField.text + "&action=" + timerActionSelector.currentValue + "&after_event=" + timerAfterSelector.currentValue;

    url += "&shour=" + timerStartTimeSelector.currentHour + "&smin=" + timerStartTimeSelector.currentMinute + "&sampm=" + (timerStartTimeSelector.currentHour > 11 ? "pm" : "am");
    url += "&ehour=" + timerEndTimeSelector.currentHour + "&emin=" + timerEndTimeSelector.currentMinute + "&eampm=" + (timerEndTimeSelector.currentHour > 11 ? "pm" : "am");

    if (timerTypeSelector.currentValue == "repeating") {
        var days = { "mo": "off", "tu": "off", "we": "off", "th": "off", "fr": "off", "sa": "off", "su": "off" };

        for (var i = 0; i < timerDaysSelector.currentValues.length; i++) {
            days[timerDaysSelector.currentValues[i]] = "on";
        }

        for (var day in days) {
            url += "&" + day + "=" + days[day];
        }
    }
    else {
        url += "&sday=" + timerStartDateSelector.currentDay + "&smonth=" + timerStartDateSelector.currentMonth + "&syear=" + timerStartDateSelector.currentYear;
        url += "&eday=" + timerEndDateSelector.currentDay + "&emonth=" + timerEndDateSelector.currentMonth + "&eyear=" + timerEndDateSelector.currentYear;
    }

    http.get(url);
    getTimerEvents();
}

function removeTimerEvent(event) {
    if (notifications.confirm(qsTr("Remove the selected timer event?"), pageStack)) {
        http.get(ipaddress 
                + "/deleteTimerEvent?ref=" 
                + event.ref 
                + "&start=" 
                + event.start 
                + "&type=" 
                + event.type 
                + "&force=no",
                {},
                function (message) { notifications.information(message); }
                );

        getTimerEvents();
    }
}

function cleanupTimerEvents() {
    if (notifications.confirm(qsTr("Remove all completed timer events?"), pageStack)) {
        http.get(ipaddress + "/cleanupTimerList");
        getTimerEvents();
    }
}

function clearTimerEvents() {
    if (notifications.confirm(qsTr("Remove all timer events?"), pageStack)) {
        http.get(ipaddress + "/clearTimerList");
        getTimerEvents();
    }
}

if (ipaddress) {
    loadServices("0", populateServices);
}
