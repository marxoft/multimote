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

var Accounts = new function() {
    this.accounts = [];

    this.load = function () {
                accountView.clear();
                http.get(ipaddress + "/serviceAccounts",
                         {},
                         function (response) {
                             Accounts.accounts = JSON.parse(response);

                             for (var i = 0; i < Accounts.accounts.length; i++) {
                                 Accounts.appendRow(Accounts.accounts[i]);
                             }
                         }
                );
    };

    this.addAccount = function (serviceName, username, password) {
        http.get(ipaddress + "/serviceAccounts/addAccount?serviceName=" + serviceName + "&username=" + username + "&password=" + password,
                {},
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Accounts.updateRow(accountView.currentIndex, result);
                    }
                }
        );
    };

    this.removeAccount = function (serviceName) {
        if (notifications.confirm("Remove account '" + serviceName + "'?")) {
            http.get(ipaddress + "/serviceAccounts/removeAccount?serviceName=" + serviceName,
                    {},
                    function (response) {
                        var result = JSON.parse(response);

                        if (result.error) {
                            notifications.error(result.error);
                        }
                        else {
                            Accounts.removeRow(accountView.currentIndex);
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
            accountView.insertItem(i, ipaddress + account.serviceIcon, account.serviceName + "\n" + (account.username ? account.username : "No account"), account);
        }
    };

    this.appendRow = function (account) {
        accountView.addItem(ipaddress + account.serviceIcon, account.serviceName + "\n" + (account.username ? account.username : "No account"), account);
    };

    this.updateRow = function (i, account) {
        accountView.removeItem(i);
        accountView.insertItem(i, ipaddress + account.serviceIcon, account.serviceName + "\n" + (account.username ? account.username : "No account"), account);
    };

    this.removeRow = function (i) {
        accountView.removeItem(i);
    };

    this.showEditAccountDialog = function (account) {
        accountUsernameEdit.text = account.username;
        accountPasswordEdit.text = account.password;
        editAccountDialog.open();
    };
}
