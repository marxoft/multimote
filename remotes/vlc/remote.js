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
var status = {};
var homeDir = { "path": "~/", "uri": "file://~" };
var currentDir = homeDir;
var upDir = { "path": "/", "uri": "file:///" };
var aspectRatios = [ "1:1", "4:3", "16:9", "16:10", "5:4", "1:1" ];
var connectedToVLC = false;

function processKeyEvent(event) {
    /* Repsond to key press event */

    if (event.modifiers & Qt.ControlModifier) {
        switch (event.key) {
        case Qt.Key_O:
            fileDialog.open();
            cd(currentDir);
            return;
        case Qt.Key_L:
            switch (pageStack.currentIndex) {
            case 1:
                pageStack.currentIndex = 0;
                return;
            default:
                pageStack.currentIndex = 1;
                return;
            }
        default:
            return;
        }
    }

    switch (event.key) {
    case Qt.Key_Left:
        seek(seekMode === "percent" ? Math.floor(status.time - status.length * seekPercent / 100) : status.time - seekInterval);
        return;
    case Qt.Key_Right:
        seek(seekMode === "percent" ? Math.floor(status.time + status.length * seekPercent / 100) : status.time + seekInterval);
        return;
    case Qt.Key_Space:
        playPause();
        return;
    case Qt.Key_P:
        previous();
        return;
    case Qt.Key_N:
        next();
        return;
    case Qt.Key_A:
        toggleAspectRatio();
        return;
    case Qt.Key_F:
        toggleFullscreen();
        return;
    }
}

function connectToVLC() {
    /* Test connection to VLC web interface */

    http.get(ipaddress + "/requests/status.json", {}, checkConection);
}

function checkConection(response) {
    if (response) {
        connectedToVLC = true;
        status = JSON.parse(response);
        updateUI();

        if (syncUI) {
            syncTimer.start();
        }
    }
    else {
        syncTimer.stop();
        connectedToVLC = false;
    }
}

function getStatus() {
    /* Retreive current status to update the UI */

    http.get(ipaddress + "/requests/status.json", {}, loadStatus);
}

function loadStatus(json) {
    /* Update the global status variable and the UI */

    if (!json) {
        return;
    }

    status = JSON.parse(json);
    updateUI();
}

function updateUI() {
    /* Update the UI with the current status */

    if (status.hasOwnProperty("information")) {
        var metadata = status.information.category.meta;

        if (metadata.filename !== titleLabel.text) {
            if (metadata.artwork_url) {
                getCoverArt();
            }
            else {
                coverImage.source = "/home/user/MultiMote/remotes/VLC/vlc.png";
            }
        }

        titleLabel.text = metadata.filename;
        artistLabel.text = metadata.artist;
    }
    else {
        coverImage.source = "/home/user/MultiMote/remotes/VLC/vlc.png";
        titleLabel.text = "";
        artistLabel.text = "";
    }

    seekSlider.maximum = status.length;

    if (!seekSlider.sliderDown) {
        seekSlider.value = status.time;
    }

    positionLabel.text = !status.time ? "--:--:--" : new Date(status.time * 1000).toTimeString().substring(0, 8);
    durationLabel.text = !status.length ? "--:--:--" : new Date(status.length * 1000).toTimeString().substring(0, 8);

    playPauseButton.iconSource = "/etc/hildon/theme/mediaplayer/" + (status.state === "playing" ? "Pause.png" : "Play.png");
    repeatAction.checked = status.loop;
    randomAction.checked = status.random;
    fullscreenAction.checked = status.fullscreen;
}

function sendCommand(command) {
    /* Send a command to the web interface */

    http.get(ipaddress + "/requests/status.json?command=" + command, {}, loadStatus);
}

function getCoverArt(id) {
    coverImage.source = "/home/user/MultiMote/remotes/VLC/vlc.png";

    if ((status.state) && (status.state !== "stopped")) {
        coverImage.source = ipaddress + "/art" + (id ? "?id=" + id : "");
    }
}

// Playback controls
function playPause() {
    http.get(ipaddress + "/requests/status.json?command=pl_pause", {}, loadStatus);
}

function playFile(uri) {
    http.get(ipaddress + "/requests/status.json?command=in_play&input=" + uri, {}, loadStatus);
}

function queueFile(uri) {
    http.get(ipaddress + "/requests/status.json?command=in_enqueue&input=" + uri, {}, loadStatus);
}

function playPlaylistItem(id) {
    http.get(ipaddress + "/requests/status.xml?command=pl_play&id=" + id);
}

function removePlaylistItem(id) {
    http.get(ipaddress + "/requests/status.xml?command=pl_delete&id=" + id, {}, getPlaylist);
}

function clearPlaylist() {
    http.get(ipaddress + "/requests/status.json?command=pl_empty", {}, getPlaylist);
}

function stop() {
    http.get(ipaddress + "/requests/status.json?command=pl_stop", {}, loadStatus);
}

function next() {
    http.get(ipaddress + "/requests/status.json?command=pl_next", {}, loadStatus);
}

function previous() {
    http.get(ipaddress + "/requests/status.json?command=pl_previous", {}, loadStatus);
}

function toggleRepeat() {
    http.get(ipaddress + "/requests/status.json?command=pl_loop", {}, loadStatus);
}

function toggleRandom() {
    http.get(ipaddress + "/requests/status.json?command=pl_random", {}, loadStatus);
}

function seek(pos) {
    http.get(ipaddress + "/requests/status.json?command=seek&val=" + pos, {}, loadStatus);
}

function setVolume(vol) {
    http.get(ipaddress + "/requests/status.json?command=volume&val=" + vol, {}, loadStatus);
}

function increaseVolume(step) {
    setVolume(status.volume + step);
}

function decreaseVolume(step) {
    setVolume(status.volume - step);
}

function setFullscreen(fs) {
    http.get(ipaddress + "/requests/status.json?command=fullscreen&val=" + fs, {}, loadStatus);
}

function toggleFullscreen() {
    setFullscreen(status.fullscreen ? "false" : "true");
}

function setAspectRatio(aspect) {
    http.get(ipaddress + "/requests/status.json?command=aspectratio&val=" + aspect, {}, loadStatus);
}

function toggleAspectRatio() {
    var aspect = status.aspectratio;

    for (var i = 0; i < aspectRatios.length; i++) {
        if (aspect === aspectRatios[i]) {
            setAspectRatio(aspectRatios[i + 1]);
            return;
        }
    }

    setAspectRatio("default");
}

function getPlaylist() {
    playlist.clear();
    http.get(ipaddress + "/requests/playlist.json", {}, loadPlaylist);
}

function loadPlaylist(json) {
    var pl = JSON.parse(json);
    var items = pl.children[0].children;

    for (var i = 0; i < items.length; i++) {
        playlist.addItem(items[i].name, items[i]);

        if (items[i].current) {
            playlist.currentIndex = i;
        }
    }

    clearButton.enabled = items.length > 0;
}

function cd(dir) {
    if (!dir) {
        dir = currentDir;
    }
    else {
        currentDir = dir;
    }

    fileList.clear();
    dirLabel.text = dir.path;
    backButton.enabled = dir.path !== "/";
    http.get(ipaddress + "/requests/browse.json?uri=" + dir.uri, {}, loadFiles);
}

function cdUp() {
    cd(upDir);
}

function cdHome() {
    cd(homeDir);
}

function loadFiles(json) {
    var files = JSON.parse(json);

    if (!files.hasOwnProperty("element")) {
        print("No files found");
        return;
    }

    files = files.element;

    if (files.length === 0) {
        return;
    }

    upDir = files[0];

    for (var i = 1; i < files.length; i++) {
        fileList.addItem(files[i].name, files[i]);
    }
}

function onFileChosen(file) {
    if (file.type === "file") {
        playFile(file.uri);
        fileDialog.close();
    }
    else {
        cd(file);
    }
}

screen.lockStateChanged.connect(
            function (locked) {
                syncTimer.running = (!locked) && (syncUI);

                if (syncTimer.running) {
                    getStatus();
                }
            }
            );

pageStack.currentChanged.connect(
            function (index) {
                if (index === 1) {
                    getPlaylist();
                }
            }
            );

if (ipaddress) {
    connectToVLC();
}
