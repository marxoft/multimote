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

var Preferences = new function() {
    this.setPreferences = function (prefs) {
        var prefString = "";

        for (var pref in prefs) {
            prefString += pref + "=" + prefs[pref] + "&";
        }

        http.get(ipaddress + "/preferences/setProperties?" + prefString, {}, 
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                }
        );
    };

    this.load = function () {
        http.get(ipaddress + "/preferences/getProperties?properties=downloadPath,startTransfersAutomatically,extractDownloadedArchives,createSubfolderForArchives,deleteExtractedArchives",
                 {},
                 function (response) {
                     var result = JSON.parse(response);

                     if (result.error) {
                         notifications.error(result.error);
                     }
                     else {
                         downloadPathEdit.text = result.downloadPath;
                         downloadPathEdit.enabled = (Queue.totalTransfers == 0);
                         autoCheckbox.checked = result.startTransfersAutomatically;
                         extractArchivesCheckbox.checked = result.extractDownloadedArchives;
                         archiveSubfoldersCheckbox.checked = result.createSubfolderForArchives;
                         deleteArchivesCheckbox.checked = result.deleteExtractedArchives;
                     }
                 }
        );
    };

    this.save = function () {
        var prefs = {};
        prefs["downloadPath"] = downloadPathEdit.text;
        prefs["startTransfersAutomatically"] = autoCheckbox.checked ? "true" : "false";
        prefs["extractDownloadedArchives"] = extractArchivesCheckbox.checked ? "true" : "false";
        prefs["createSubfolderForArchives"] = archiveSubfoldersCheckbox.checked ? "true" : "false";
        prefs["deleteExtractedArchives"] = deleteArchivesCheckbox.checked ? "true" : "false";
        this.setPreferences(preferences);
    };
}
