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
var isOn = false;

function powerOn() {
    http.get(ipaddress + "/bacpac/PW?t=" + password + "&p=%01");
}

function powerOff() {
    http.get(ipaddress + "/bacpac/PW?t=" + password + "&p=");
}

function togglePower() {
    if (isOn) {
        powerOff();
    }
    else {
        powerOn();
    }

    isOn = !isOn;
}

function startCapture() {
    http.get(ipaddress + "/bacpac/SH?t=" + password + "&p=%01");
}

function stopCapture() {
    http.get(ipaddress + "/bacpac/SH?t=" + password + "&p=");
}

function setMode(mode) {
    http.get(ipaddress + "/camera/CM?t=" + password + "&p=" + mode);
}

function setOrientation(orientation) {
    http.get(ipaddress + "/camera/UP?t=" + password + "&p=" + orientation);
}

function setVideoResolution(res) {
    http.get(ipaddress + "/camera/VR?t=" + password + "&p=" + res);
}

function setPhotoResolution(res) {
    http.get(ipaddress + "/camera/PR?t=" + password + "&p=" + res);
}
