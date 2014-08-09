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

var Categories = new function() {
    this.categories = [];

    this.load = function () {
                categoryView.clear();
                http.get(ipaddress + "/categories",
                         {},
                         function (response) {
                             Categories.categories = JSON.parse(response);

                             for (var i = 0; i < Categories.categories.length; i++) {
                                 Categories.appendRow(Categories.categories[i]);
                             }
                         }
                );
    };

    this.addCategory = function (name, path) {
        http.get(ipaddress + "/categories/addCategory?name=" + name + "&path=" + path,
                {},
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Categories.appendRow(result);
                    }
                }
        );
    };

    this.updateCategory = function (name, path) {
        http.get(ipaddress + "/categories/addCategory?name=" + name + "&path=" + path,
                {},
                function (response) {
                    var result = JSON.parse(response);

                    if (result.error) {
                        notifications.error(result.error);
                    }
                    else {
                        Categories.updateRow(categoryView.currentIndex, result);
                    }
                }
        );
    };

    this.removeCategory = function (name) {
        if (notifications.confirm("Remove category '" + name + "'?")) {
            http.get(ipaddress + "/categories/removeCategory?name=" + name,
                    {},
                    function (response) {
                        var result = JSON.parse(response);

                        if (result.error) {
                            notifications.error(result.error);
                        }
                        else {
                            Categories.removeRow(categoryView.currentIndex);
                        }
                    }
            );
        }
    };

    this.insertRow = function (i, category) {
        if (i < 0) {
            this.appendRow(category);
        }
        else {
            categoryView.insertItem(i, category.name + "\n" + category.path, category);
        }
    };

    this.appendRow = function (category) {
        categoryView.addItem(category.name + "\n" + category.path, category);
    };

    this.updateRow = function (i, category) {
        categoryView.removeItem(i);
        categoryView.insertItem(i, category.name + "\n" + category.path, category);
    };

    this.removeRow = function (i) {
        categoryView.removeItem(i);
    };

    this.showEditCategoryDialog = function (category) {
        if (category) {
            editCategoryDialog.mode = "edit";
            editCategoryDialog.title = "Edit category";
            categoryNameEdit.text = category.name;
            categoryPathEdit.text = category.path;
        }
        else {
            editCategoryDialog.mode = "";
            editCategoryDialog.title = "Add category";
            categoryNameEdit.clear();
            categoryPathEdit.clear();
        }

        editCategoryDialog.open();
    };
}
