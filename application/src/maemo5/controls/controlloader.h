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

#ifndef CONTROLLOADER_H
#define CONTROLLOADER_H

class QDomElement;
class QObject;
class QWidget;
class Action;
class Button;
class CheckBox;
class DateSelector;
class DoubleSpinBox;
class Slider;
class Label;
class ToolButton;
class Keyboard;
class VolumeKeys;
class Dialog;
class Dpad;
class Image;
class ListSelector;
class ListView;
class MultiListSelector;
class Numberpad;
class RemotePage;
class RemotePageStack;
class SpinBox;
class TextField;
class Timer;
class TimeSelector;
class ToolBar;
class Touchpad;

class ControlLoader {

public:
    static QObject* loadControl(const QDomElement &el, bool registerHandlers, QObject *parent = 0);
    static RemotePageStack* loadPageStack(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static RemotePage* loadPage(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static Dialog* loadDialog(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static Keyboard* loadKeyboard(const QDomElement &el, bool registerHandlers, QObject *parent = 0);
    static VolumeKeys* loadVolumeKeys(const QDomElement &el, bool registerHandlers, QObject *parent = 0);
    static Action* loadAction(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static Button* loadButton(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static CheckBox* loadCheckBox(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static DoubleSpinBox* loadDoubleSpinBox(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static Dpad* loadDpad(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static Image* loadImage(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static Label* loadLabel(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static ListSelector* loadListSelector(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static MultiListSelector* loadMultiListSelector(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static DateSelector* loadDateSelector(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static TimeSelector* loadTimeSelector(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static ListView* loadListView(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static Numberpad* loadNumberpad(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static Slider* loadSlider(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static SpinBox* loadSpinBox(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static TextField* loadTextField(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static Timer* loadTimer(const QDomElement &el, bool registerHandlers, QObject *parent = 0);
    static ToolBar* loadToolBar(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static ToolButton* loadToolButton(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);
    static Touchpad* loadTouchpad(const QDomElement &el, bool registerHandlers, QWidget *parent = 0);

private:
    static void loadProperties(QObject *obj, const QDomElement &el);

    static void loadWidgetLayout(QWidget *widget, const QDomElement &el);

    static void registerHandlersWithScriptEngine(QObject *obj, const QDomElement &el);
};

#endif // CONTROLLOADER_H
