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

var Proxy = new function() {
    this.load = function () {
        http.get(ipaddress + "/preferences/getProperties?properties=networkProxyHostName,networkProxyPort,networkProxyUser,networkProxyPassword,networkProxyType",
                 {},
                 function (response) {
                     var result = JSON.parse(response);

                     if (result.error) {
                         notifications.error(result.error);
                     }
                     else {
                         proxyCheckbox.checked = (result.networkProxyHostName !== "");
                         proxyTypeSelector.currentValue = result.networkProxyType;
                         proxyHostEdit.text = result.networkProxyHostName;
                         proxyPortEdit.text = result.networkProxyPort;
                         proxyUsernameEdit.text = result.networkProxyUser;
                         proxyPasswordEdit.text = result.networkProxyPassword;
                     }
                 }
        );
    };

    this.save = function () {
        var prefs = {};
        prefs["networkProxyType"] = proxyTypeSelector.currentValue;
        prefs["networkProxyHostName"] = proxyHostEdit.text;
        prefs["networkProxyPort"] = proxyPortEdit.text;
        prefs["networkProxyUser"] = proxyUsernameEdit.text;
        prefs["networkProxyPassword"] = proxyPasswordEdit.text;
        Preferences.setPreferences(prefs);
    };
}

proxyCheckbox.toggled.connect(
            function (checked) {
                proxyTypeSelector.enabled = checked;
                proxyHostLabel.enabled = checked;
                proxyHostEdit.enabled = checked;
                proxyPortLabel.enabled = checked;
                proxyPortEdit.enabled = checked;
                proxyUsernameLabel.enabled = checked;
                proxyUsernameEdit.enabled = checked;
                proxyPasswordLabel.enabled = checked;
                proxyPasswordEdit.enabled = checked;
            }
);
