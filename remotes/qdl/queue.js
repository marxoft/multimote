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

var Queue = new function() {
    this.totalTransfers = 0;
    this.activeTransfers = 0;
    this.downloadSpeed = 0;
    this.maximumConcurrentTransfers = 1;
    this.maximumConnectionsPerTransfer = 1;
    this.downloadRateLimit = 0;
    this.nextAction = 0;
    this.transfers = [];
    this.categories = [];

    this.currentIndex = 0;
    this.limitPerPage = 30;
    this.filter = "";
    this.query = "";

    this.load = function () {
        queueView.clear();
        categorySelector.clear();
        urlCategorySelector.clear();
        reloadButton.enabled = false;
        
        this.captchaId = "";
        this.captchaFileName = "";
        this.captchaTimeOut = 0;

        http.get(ipaddress + "/status", {}, 
                function (response) {
                    var status = JSON.parse(response);
                    Queue.totalTransfers = status.totalTransfers;
                    Queue.activeTransfers = status.activeTransfers;
                    Queue.downloadSpeed = status.downloadSpeed;
                    Queue.maximumConcurrentTransfers = status.maximumConcurrentTransfers;
                    Queue.maximumConnectionsPerTransfer = status.maximumConnectionsPerTransfer;
                    Queue.downloadRateLimit = status.downloadRateLimit;
                    Queue.nextAction = status.nextAction;

                    speedLabel.text = Queue.downloadSpeed + " kB/s";
                    nextActionSelector.currentValue = Queue.nextAction;
                    concurrentSelector.currentValue = Queue.maximumConcurrentTransfers;
                    globalConnectionsSelector.currentValue = Queue.maximumConnectionsPerTransfer;
                    rateLimitSelector.currentValue = Queue.downloadRateLimit;
                }
        );

        http.get(ipaddress + "/categoryNames", 
                {}, 
                function (response) { 
                    Queue.categories = JSON.parse(response);

                    for (var i = 0; i < Queue.categories.length; i++) {
                        categorySelector.addItem(Queue.categories[i], Queue.categories[i]);
                        urlCategorySelector.addItem(Queue.categories[i], Queue.categories[i]);
                    }

                    categorySelector.currentIndex = 0;
                    urlCategorySelector.currentIndex = 0;
                }
        );

        http.get(ipaddress + "/transfers?filter=" + this.filter + "&query=" + this.query + "&start=" + this.currentIndex + "&limit=" + this.limitPerPage, 
                {}, 
                function (response) { 
                    Queue.transfers = JSON.parse(response).transfers;
                    
                    for (var i = 0; i < Queue.transfers.length; i++) {
                        var transfer = Queue.transfers[i];
                        Queue.appendRow(transfer);

                        if ((transfer.status === 8) && (!Queue.captchaId)) {
                            Queue.captchaId = transfer.id;
                            Queue.captchaFileName = transfer.captchaFileName;
                            Queue.captchaTimeOut = transfer.captchaTimeOut;
                        }
                    }

                    if (Queue.captchaId) {
                        Queue.showCaptchaDialog();
                    }
                    else if (Queue.filter !== "CaptchaRequired") {
                        http.get(ipaddress + "/transfers?filter=CaptchaRequired&start=0&limit=1",
                                 {},
                                 function (response) {
                                     var captchaTransfers = JSON.parse(response).transfers;

                                     for (var i = 0; i < captchaTransfers.length; i++) {
                                         var transfer = captchaTransfers[i];

                                         if ((transfer.status === 8) && (!Queue.captchaId)) {
                                             Queue.captchaId = transfer.id;
                                             Queue.captchaFileName = transfer.captchaFileName;
                                             Queue.captchaTimeOut = transfer.captchaTimeOut;
                                         }
                                     }

                                     if (Queue.captchaId) {
                                         Queue.showCaptchaDialog();
                                     }
                                 }
                        );
                    }
                }
        );

        reloadButton.enabled = true;
    };

    this.search = function (q) {
        this.query = q;
        this.currentIndex = 0;
        this.load();
    };

    this.setStatusFilter = function (f) {
        this.filter = f;
        this.currentIndex = 0;
        this.load();
    };

    this.firstPage = function () {
        this.currentIndex = 0;
        this.load();
    };

    this.previousPage = function() {
        this.currentIndex = Math.max(0, this.currentIndex - this.limitPerPage);
        this.load();
    };

    this.nextPage = function () {
        this.currentIndex = Math.min(this.totalTransfers - this.limitPerPage, this.currentIndex + queueView.count);
        this.load();
    };

    this.lastPage = function () {
        this.currentIndex = this.totalTransfers - this.limitPerPage;
        this.load();
    };

    this.insertRow = function (i, transfer) {
        if (i < 0) {
            this.appendRow(transfer);
        }
        else {
            queueView.insertItem(i, ipaddress + transfer.icon,
                                 transfer.name
                                 + "\n"
                                 + transfer.statusString
                                 + ": "
                                 + Utils.formatBytes(transfer.position)
                                 + " of "
                                 + (transfer.size ? Utils.formatBytes(transfer.size) : "Unknown")
                                 + " (" + transfer.progress + "%)",
                                 transfer);
        }
    };

    this.appendRow = function (transfer) {
        queueView.addItem(ipaddress + transfer.icon,
                          transfer.name
                          + "\n"
                          + transfer.statusString
                          + ": "
                          + Utils.formatBytes(transfer.position)
                          + " of "
                          + (transfer.size ? Utils.formatBytes(transfer.size) : "Unknown")
                          + " (" + transfer.progress + "%)",
                          transfer);

    };

    this.updateRow = function (i, transfer) {
        var item = queueView.itemAt(i);

        if (item) {
            item.iconSource = ipaddress + transfer.icon;
            item.text = transfer.name
                        + "\n"
                        + transfer.statusString
                        + ": "
                        + Utils.formatBytes(transfer.position)
                        + " of "
                        + (transfer.size ? Utils.formatBytes(transfer.size) : "Unknown")
                        + " (" + transfer.progress + "%)"
            item.data = transfer;
        }
    };

    this.removeRow = function (i) {
        queueView.removeItem(i);
    };

    this.showDownloadPropertiesDialog = function (transfer) {
        /*
        switch (transfer.status) {
        case 0:
        case 3:
            startButton.enabled = true;
            pauseButton.enabled = false;
            break;
        default:
            startButton.enabled = false;
            pauseButton.enabled = true;
            break;
        }
        */

        serviceIcon.source = ipaddress + transfer.icon;
        nameLabel.text = transfer.name;
        audioCheckbox.checked = transfer.convertToAudio;
        audioCheckbox.enabled = transfer.convertibleToAudio;
        connectionsSelector.clear();

        for (var i = 1; i <= transfer.maximumConnections; i++) {
            connectionsSelector.addItem(i, i);
        }

        connectionsSelector.currentValue = transfer.preferredConnections;
        categorySelector.currentValue = transfer.category;
        prioritySelector.currentValue = transfer.priority;
        downloadProgressBar.value = transfer.progress;
        statusLabel.text = transfer.statusString;

        downloadPropertiesDialog.open();
    };

    this.showAddUrlsDialog = function (urls) {
        if (urls) {
            addUrlsEdit.text = urls;
        }
        else {
            addUrlsEdit.clear();
        }

        addUrlsDialog.open();
    };

    this.addUrls = function (urls, category) {
        http.get(ipaddress + "/urls/addUrls?urls=" + urls.replace(/\s+/g, ",") + "&category=" + category,
                {},
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else if (result.progress < 100) {
                        Queue.showProgressDialog("Checking URLs");
                        Queue.updateProgressDialog(result.progress);
                        progressTimer.triggered.connect(Queue.updateUrlChecks);
                        progressDialog.rejected.connect(Queue.cancelUrlChecks);
                        progressTimer.start();
                    }
                    else {
                        http.get(ipaddress + "/urls/clearUrlChecks");
                    }
                }
        );
    };

    this.updateUrlChecks = function () {
        http.get(ipaddress + "/urls/urlCheckProgress",
                {},
                function (response) {
                    var result = JSON.parse(response);
                    
                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Queue.updateProgressDialog(result.progress);

                        if (result.progress < 100) {
                            progressTimer.start();
                        }
                        else {
                            http.get(ipaddress + "/urls/clearUrlChecks");

                            try {
                                progressTimer.triggered.disconnect(Queue.updateUrlChecks);
                                progressDialog.rejected.disconnect(Queue.cancelUrlChecks);
                            }
                            catch (error) {
                                print("Queue.updateUrlChecks: " + error);
                            }
                        }
                    }
                }
        );
    };

    this.cancelUrlChecks = function () {
        http.get(ipaddress + "/urls/cancelUrlChecks");

        try {
            progressTimer.triggered.disconnect(Queue.updateUrlChecks);
            progressDialog.rejected.disconnect(Queue.cancelUrlChecks);
        }
        catch (error) {
            print("Queue.cancelUrlChecks: " + error);
        }
    };

    this.showRetrieveUrlsDialog = function () {
        retrieveUrlsEdit.clear();
        retrieveUrlsDialog.open();
    };

    this.retrieveUrls = function (urls) {
        http.get(ipaddress + "/urls/retrieveUrls?urls=" + urls.replace(/\s+/g, ","),
                {},
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else if (result.progress < 100) {
                        Queue.showProgressDialog("Retrieving URLs");
                        Queue.updateProgressDialog(result.progress);
                        progressTimer.triggered.connect(Queue.updateUrlRetrieval);
                        progressDialog.rejected.connect(Queue.cancelUrlRetrieval);
                        progressTimer.start();
                    }
                    else if (result.urls.length > 0) {
                        Queue.showAddUrlsDialog(result.urls.join("\n"));
                        http.get(ipaddress + "/urls/clearRetrievedUrls");
                    }
                    else {
                        notifications.information("No supported URLs found");
                    }
                }
        );
    };

    this.updateUrlRetrieval = function () {
        http.get(ipaddress + "/urls/urlRetrievalProgress",
                {},
                function (response) {
                    var result = JSON.parse(response);
                    
                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Queue.updateProgressDialog(result.progress);

                        if (result.progress == 100) {
                            if (result.urls.length > 0) {
                                Queue.showAddUrlsDialog(result.urls.join("\n"));
                                http.get(ipaddress + "/urls/clearRetrievedUrls");
                            }
                            else {
                                notifications.information("No supported URLs found");
                            }

                            try {
                                progressTimer.triggered.disconnect(Queue.updateUrlRetrieval);
                                progressDialog.rejected.disconnect(Queue.cancelUrlRetrieval);
                            }
                            catch (error) {
                                print("Queue.updateUrlRetrieval: " + error);
                            }
                        }
                        else {
                            progressTimer.start();
                        }
                    }
                }
        );
    };

    this.cancelUrlRetrieval = function () {
        http.get(ipaddress + "/urls/cancelUrlRetrieval");

        try {
            progressTimer.triggered.disconnect(Queue.updateUrlRetrieval);
            progressDialog.rejected.disconnect(Queue.cancelUrlRetrieval);
        }
        catch (error) {
            print("Queue.cancelUrlRetrieval: " + error);
        }
    };

    this.showProgressDialog = function (message) {
        progressLabel.text = message;
        progressBar.value = 0;
        progressDialog.open();
    };

    this.updateProgressDialog = function (progress) {
        progressBar.value = progress;
        
        if (progressBar.value >= progressBar.maximum) {
            progressDialog.close();
        }
    };

    this.showCaptchaDialog = function () {
        captchaImage.source = ipaddress + this.captchaFileName;
        captchaResponseEdit.clear();
        captchaTimeOutLabel.text = Utils.formatSecs(this.captchaTimeOut);
        captchaDialog.open();
        captchaTimer.start();
    };

    this.updateCaptchaDialog = function () {
        this.captchaTimeOut--;
        
        if (this.captchaTimeOut > 0) {
            captchaTimeOutLabel.text = Utils.formatSecs(this.captchaTimeOut);
        }
        else {
            captchaTimer.stop();
            captchaDialog.reject();
        }
    };

    this.setProperty = function (property, value) {
        http.get(ipaddress + "/transfers/setProperty?property=" + property + "&value=" + value,
                {},
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                }
        ); 
    };

    this.setTransferProperty = function (id, property, value) {
        http.get(ipaddress + "/transfers/setTransferProperty?id=" + id + "&property=" + property + "&value=" + value, {}, 
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Queue.updateRow(queueView.currentIndex, result);
                    }
                }
        );
    };

    this.startTransfer = function (id) {
        http.get(ipaddress + "/transfers/start?id=" + id, {}, 
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Queue.updateRow(queueView.currentIndex, result);
                    }
                }
        );
    };

    this.pauseTransfer = function (id) {
        http.get(ipaddress + "/transfers/pause?id=" + id, {}, 
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Queue.updateRow(queueView.currentIndex, transfer);
                    }
                }
        );
    };

    this.removeTransfer = function (id) {
        if (!notifications.confirm("Do you wish to remove this transfer from the queue?")) {
            return;
        }

        http.get(ipaddress + "/transfers/remove?id=" + id, {}, 
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Queue.removeRow(queueView.currentIndex);
                    }
                }
        );
    };

    this.startAllTransfers = function () {
        http.get(ipaddress + "/transfers/start", {}, 
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Queue.load();
                    }
                }
        );
    };

    this.pauseAllTransfers = function () {
        http.get(ipaddress + "/transfers/pause", {}, 
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Queue.load();
                    }
                }
        );
    };  
}

if (ipaddress) {
    Queue.load();
}
