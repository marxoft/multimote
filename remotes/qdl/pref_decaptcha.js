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

var Decaptcha = new function() {
    this.accounts = [];

    this.load = function () {
                decaptchaAccountView.clear();
                http.get(ipaddress + "/decaptchaAccounts",
                         {},
                         function (response) {
                             Decaptcha.accounts = JSON.parse(response);

                             for (var i = 0; i < Decaptcha.accounts.length; i++) {
                                 Decaptcha.appendRow(Decaptcha.accounts[i]);
                             }
                         }
                );
    };

    this.addAccount = function (serviceName, username, password) {
        http.get(ipaddress + "/decaptchaAccounts/addAccount?serviceName=" + serviceName + "&username=" + username + "&password=" + password,
                {},
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Decaptcha.updateRow(decaptchaAccountView.currentIndex, result);
                    }
                }
        );
    };

    this.removeAccount = function (serviceName) {
        if (notifications.confirm("Remove account '" + serviceName + "'?")) {
            http.get(ipaddress + "/decaptchaAccounts/removeAccount?serviceName=" + serviceName,
                    {},
                    function (response) {
                        var result = JSON.parse(response);

                        if (result.error) {
                            notifications.error(result.error);
                        }
                        else {
                            Decaptcha.removeRow(decaptchaAccountView.currentIndex);
                        }
                    }
            );
        }
    };

    this.insertRow = function (i, account) {
        if (i < 0) {
            this.appendRow(account);
        }
        else {
            decaptchaAccountView.insertItem(i, ipaddress + account.serviceIcon, account.serviceName + "\n" + (account.username ? account.username : "No account"), account);
        }
    };

    this.appendRow = function (account) {
        decaptchaAccountView.addItem(ipaddress + account.serviceIcon, account.serviceName + "\n" + (account.username ? account.username : "No account"), account);
    };

    this.updateRow = function (i, account) {
        decaptchaAccountView.removeItem(i);
        decaptchaAccountView.insertItem(i, ipaddress + account.serviceIcon, account.serviceName + "\n" + (account.username ? account.username : "No account"), account);
    };

    this.removeRow = function (i) {
        decaptchaAccountView.removeItem(i);
    };

    this.showEditAccountDialog = function (account) {
        decaptchaUsernameEdit.text = account.username;
        decaptchaPasswordEdit.text = account.password;
        editDecaptchaAccountDialog.open();
    };
}
