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

#include "controlloader.h"
#include "action.h"
#include "button.h"
#include "checkbox.h"
#include "dateselector.h"
#include "dialog.h"
#include "doublespinbox.h"
#include "dpad.h"
#include "image.h"
#include "label.h"
#include "listselector.h"
#include "listview.h"
#include "multilistselector.h"
#include "numberpad.h"
#include "progressbar.h"
#include "remotepage.h"
#include "remotepagestack.h"
#include "slider.h"
#include "spinbox.h"
#include "textfield.h"
#include "toolbar.h"
#include "toolbutton.h"
#include "touchpad.h"
#include "keyboard.h"
#include "timer.h"
#include "timeselector.h"
#include "volumekeys.h"
#include "../../base/scriptengine.h"
#include <QDomElement>
#include <QMetaMethod>
#include <QDebug>

QObject* ControlLoader::loadControl(const QDomElement &el, bool registerHandlers, QObject *parent) {
    QString name = el.tagName().toLower();

    if (name == "action") {
        return loadAction(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "button") {
        return loadButton(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "checkbox") {
        return loadCheckBox(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "dateselector") {
        return loadDateSelector(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "dialog") {
        return loadDialog(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "doublespinbox") {
        return loadDoubleSpinBox(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "dpad") {
        return loadDpad(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "image") {
        return loadImage(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "keyboard") {
        return loadKeyboard(el, registerHandlers, parent);
    }

    if (name == "label") {
        return loadLabel(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "listselector") {
        return loadListSelector(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "listview") {
        return loadListView(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "multilistselector") {
        return loadMultiListSelector(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "numberpad") {
        return loadNumberpad(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "page") {
        return loadPage(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "pagestack") {
        return loadPageStack(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "progressbar") {
        return loadProgressBar(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "slider") {
        return loadSlider(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "spinbox") {
        return loadSpinBox(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "textfield") {
        return loadTextField(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "timer") {
        return loadTimer(el, registerHandlers, parent);
    }

    if (name == "timeselector") {
        return loadTimeSelector(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "toolbar") {
        return loadToolBar(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "toolbutton") {
        return loadToolButton(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "touchpad") {
        return loadTouchpad(el, registerHandlers, qobject_cast<QWidget*>(parent));
    }

    if (name == "volumekeys") {
        return loadVolumeKeys(el, registerHandlers, parent);
    }

    return 0;
}

RemotePageStack* ControlLoader::loadPageStack(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    RemotePageStack* stack = new RemotePageStack(parent);
    stack->setObjectName("pageStack");
    loadProperties(stack, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(stack, el);
    }

    QDomNodeList pages = el.elementsByTagName("page");

    for (int i = 0; i < pages.size(); i++) {
        if (RemotePage *page = loadPage(pages.at(i).toElement(), registerHandlers, stack)) {
            stack->addWidget(page);
        }
    }

    return stack;
}

RemotePage* ControlLoader::loadPage(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    RemotePage *page = new RemotePage(parent);
    page->setObjectName(el.attribute("name"));
    loadProperties(page, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(page, el);
    }

    QDomNodeList controls = el.childNodes();

    for (int i = 0; i < controls.size(); i++) {
        if (QObject* control = loadControl(controls.at(i).toElement(), registerHandlers, page)) {
            if (control->isWidgetType()) {
                page->addWidget(qobject_cast<QWidget*>(control));
            }
        }
    }

    return page;
}

Dialog* ControlLoader::loadDialog(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    Dialog *dialog = new Dialog(parent);
    dialog->setObjectName(el.attribute("name"));
    loadProperties(dialog, el);
    loadWidgetLayout(dialog, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(dialog, el);
    }

    QDomNodeList controls = el.childNodes();

    for (int i = 0; i < controls.size(); i++) {
        if (controls.at(i).nodeName() == "buttons") {
            QDomNodeList buttons = controls.at(i).childNodes();

            for (int ii = 0; ii < buttons.size(); ii++) {
                dialog->addButton(loadButton(buttons.at(ii).toElement(), registerHandlers, dialog));
            }
        }
        else if (QObject* control = loadControl(controls.at(i).toElement(), registerHandlers, dialog)) {
            if (control->isWidgetType()) {
                dialog->addWidget(qobject_cast<QWidget*>(control));
            }
        }
    }

    return dialog;
}

Keyboard* ControlLoader::loadKeyboard(const QDomElement &el, bool registerHandlers, QObject *parent) {
    Keyboard *keyboard = new Keyboard(parent);
    keyboard->setObjectName(el.attribute("name"));

    if (parent) {
        parent->installEventFilter(keyboard);
    }

    if (registerHandlers) {
        registerHandlersWithScriptEngine(keyboard, el);
    }

    return keyboard;
}

VolumeKeys* ControlLoader::loadVolumeKeys(const QDomElement &el, bool registerHandlers, QObject *parent) {
    VolumeKeys *keys = new VolumeKeys(parent);
    keys->setObjectName(el.attribute("name"));

    if (parent) {
        parent->installEventFilter(keys);
    }

    if (registerHandlers) {
        registerHandlersWithScriptEngine(keys, el);
    }

    return keys;
}

Action* ControlLoader::loadAction(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    Action *action = new Action(parent);
    action->setObjectName(el.attribute("name"));
    loadProperties(action, el);

    if (parent) {
        parent->addAction(action);
    }

    if (registerHandlers) {
        registerHandlersWithScriptEngine(action, el);
    }

    return action;
}

Button* ControlLoader::loadButton(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    Button *button = new Button(parent);
    button->setObjectName(el.attribute("name"));
    loadProperties(button, el);
    loadWidgetLayout(button, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(button, el);
    }

    return button;
}

CheckBox* ControlLoader::loadCheckBox(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    CheckBox *checkbox = new CheckBox(parent);
    checkbox->setObjectName(el.attribute("name"));
    loadProperties(checkbox, el);
    loadWidgetLayout(checkbox, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(checkbox, el);
    }

    return checkbox;
}

DoubleSpinBox* ControlLoader::loadDoubleSpinBox(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    DoubleSpinBox *spinbox = new DoubleSpinBox(parent);
    spinbox->setObjectName(el.attribute("name"));
    loadProperties(spinbox, el);
    loadWidgetLayout(spinbox, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(spinbox, el);
    }

    return spinbox;
}

Dpad* ControlLoader::loadDpad(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    Dpad* dpad = new Dpad(parent);
    dpad->setObjectName(el.attribute("name"));
    loadWidgetLayout(dpad, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(dpad, el);
    }

    QHash<QString, Dpad::ButtonRole> roles;
    roles["left"] = Dpad::Left;
    roles["right"] = Dpad::Right;
    roles["up"] = Dpad::Up;
    roles["down"] = Dpad::Down;
    roles["enter"] = Dpad::Enter;

    QDomNodeList buttons = el.childNodes();

    for (int i = 0; i < buttons.size(); i++) {
        QDomElement key = buttons.at(i).toElement();
        QString role = key.tagName().toLower();

        if (roles.contains(role)) {
            Button *button = loadButton(key, registerHandlers, dpad);
            dpad->addButton(button, roles.value(role));
        }
    }

    return dpad;
}

Image* ControlLoader::loadImage(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    Image *image = new Image(parent);
    image->setObjectName(el.attribute("name"));
    loadProperties(image, el);
    loadWidgetLayout(image, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(image, el);
    }

    return image;
}

Label* ControlLoader::loadLabel(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    Label *label = new Label(parent);
    label->setObjectName(el.attribute("name"));
    loadProperties(label, el);
    loadWidgetLayout(label, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(label, el);
    }

    return label;
}

ListSelector* ControlLoader::loadListSelector(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    ListSelector *selector = new ListSelector(parent);
    selector->setObjectName(el.attribute("name"));

    QDomNodeList nodes = el.elementsByTagName("element");

    for (int i = 0; i < nodes.size(); i++) {
        QDomElement element = nodes.at(i).toElement();

        if (element.hasAttribute("iconSource")) {
            selector->addItem(element.attribute("iconSource"), element.attribute("name"), element.attribute("value"));
        }
        else {
            selector->addItem(element.attribute("name"), element.attribute("value"));
        }
    }

    loadProperties(selector, el);
    loadWidgetLayout(selector, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(selector, el);
    }

    return selector;
}

MultiListSelector* ControlLoader::loadMultiListSelector(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    MultiListSelector *selector = new MultiListSelector(parent);
    selector->setObjectName(el.attribute("name"));

    QDomNodeList nodes = el.elementsByTagName("element");

    for (int i = 0; i < nodes.size(); i++) {
        QDomElement element = nodes.at(i).toElement();

        if (element.hasAttribute("iconSource")) {
            selector->addItem(element.attribute("iconSource"), element.attribute("name"), element.attribute("value"));
        }
        else {
            selector->addItem(element.attribute("name"), element.attribute("value"));
        }
    }

    loadProperties(selector, el);
    loadWidgetLayout(selector, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(selector, el);
    }

    return selector;
}

DateSelector* ControlLoader::loadDateSelector(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    DateSelector *selector = new DateSelector(parent);
    selector->setObjectName(el.attribute("name"));
    loadProperties(selector, el);
    loadWidgetLayout(selector, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(selector, el);
    }

    return selector;
}

TimeSelector* ControlLoader::loadTimeSelector(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    TimeSelector *selector = new TimeSelector(parent);
    selector->setObjectName(el.attribute("name"));
    loadProperties(selector, el);
    loadWidgetLayout(selector, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(selector, el);
    }

    return selector;
}

ListView* ControlLoader::loadListView(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    ListView *view = new ListView(parent);
    view->setObjectName(el.attribute("name"));

    QDomNodeList nodes = el.elementsByTagName("element");

    for (int i = 0; i < nodes.size(); i++) {
        QDomElement element = nodes.at(i).toElement();

        if (element.hasAttribute("iconSource")) {
            view->addItem(element.attribute("iconSource"), element.attribute("name"), element.attribute("value"));
        }
        else {
            view->addItem(element.attribute("name"), element.attribute("value"));
        }
    }

    loadProperties(view, el);
    loadWidgetLayout(view, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(view, el);
    }

    return view;
}

Numberpad* ControlLoader::loadNumberpad(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    Numberpad* pad = new Numberpad(parent);
    pad->setObjectName(el.attribute("name"));
    loadWidgetLayout(pad, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(pad, el);
    }

    QHash<QString, Numberpad::ButtonRole> roles;
    roles["one"] = Numberpad::One;
    roles["two"] = Numberpad::Two;
    roles["three"] = Numberpad::Three;
    roles["four"] = Numberpad::Four;
    roles["five"] = Numberpad::Five;
    roles["six"] = Numberpad::Six;
    roles["seven"] = Numberpad::Seven;
    roles["eight"] = Numberpad::Eight;
    roles["nine"] = Numberpad::Nine;
    roles["zero"] = Numberpad::Zero;
    roles["back"] = Numberpad::Back;
    roles["forward"] = Numberpad::Forward;

    QDomNodeList buttons = el.childNodes();

    for (int i = 0; i < buttons.size(); i++) {
        QDomElement key = buttons.at(i).toElement();
        QString role = key.tagName().toLower();

        if (roles.contains(role)) {
            Button *button = loadButton(key, registerHandlers, pad);
            pad->addButton(button, roles.value(role));
        }
    }

    return pad;
}

ProgressBar* ControlLoader::loadProgressBar(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    ProgressBar *bar = new ProgressBar(parent);
    bar->setObjectName(el.attribute("name"));
    loadProperties(bar, el);
    loadWidgetLayout(bar, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(bar, el);
    }

    return bar;
}

Slider* ControlLoader::loadSlider(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    Slider *slider = new Slider(parent);
    slider->setObjectName(el.attribute("name"));
    loadProperties(slider, el);
    loadWidgetLayout(slider, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(slider, el);
    }

    return slider;
}

SpinBox* ControlLoader::loadSpinBox(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    SpinBox *spinbox = new SpinBox(parent);
    spinbox->setObjectName(el.attribute("name"));
    loadProperties(spinbox, el);
    loadWidgetLayout(spinbox, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(spinbox, el);
    }

    return spinbox;
}

TextField* ControlLoader::loadTextField(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    TextField* field = new TextField(parent);
    field->setObjectName(el.attribute("name"));
    loadProperties(field, el);
    loadWidgetLayout(field, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(field, el);
    }

    return field;
}

Timer* ControlLoader::loadTimer(const QDomElement &el, bool registerHandlers, QObject *parent) {
    Timer *timer = new Timer(parent);
    timer->setObjectName(el.attribute("name"));
    loadProperties(timer, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(timer, el);
    }

    return timer;
}

ToolBar* ControlLoader::loadToolBar(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    ToolBar *toolbar = new ToolBar(parent);
    toolbar->setObjectName(el.attribute("name"));
    loadWidgetLayout(toolbar, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(toolbar, el);
    }

    QDomNodeList controls = el.childNodes();

    for (int i = 0; i < controls.size(); i++) {
        if (QObject* control = loadControl(controls.at(i).toElement(), registerHandlers, toolbar)) {
            if (control->isWidgetType()) {
                toolbar->addWidget(qobject_cast<QWidget*>(control));
            }
        }
    }

    return toolbar;
}

ToolButton* ControlLoader::loadToolButton(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    ToolButton *button = new ToolButton(parent);
    button->setObjectName(el.attribute("name"));
    loadProperties(button, el);
    loadWidgetLayout(button, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(button, el);
    }

    return button;
}

Touchpad* ControlLoader::loadTouchpad(const QDomElement &el, bool registerHandlers, QWidget *parent) {
    Touchpad* pad = new Touchpad(parent);
    pad->setObjectName(el.attribute("name"));
    loadWidgetLayout(pad, el);

    if (registerHandlers) {
        registerHandlersWithScriptEngine(pad, el);
    }

    return pad;
}

void ControlLoader::loadProperties(QObject *obj, const QDomElement &el) {
    QDomNodeList properties = el.childNodes();

    for (int i = 0; i < properties.size(); i++) {
        QDomElement property = properties.at(i).toElement();
        obj->setProperty(property.tagName().toUtf8(), property.text());
    }
}

void ControlLoader::loadWidgetLayout(QWidget *widget, const QDomElement &el) {
    QDomElement widthEl = el.firstChildElement("width");

    if (!widthEl.firstChild().isNull()) {
        widget->setProperty("widthPortrait", qMax(0, widthEl.firstChildElement("portrait").text().toInt()));
        widget->setProperty("widthLandscape", qMax(0, widthEl.firstChildElement("landscape").text().toInt()));
    }

    QDomElement heightEl = el.firstChildElement("height");

    if (!heightEl.firstChild().isNull()) {
        widget->setProperty("heightPortrait", qMax(0, heightEl.firstChildElement("portrait").text().toInt()));
        widget->setProperty("heightLandscape", qMax(0, heightEl.firstChildElement("landscape").text().toInt()));
    }

    QDomElement rowEl = el.firstChildElement("row");

    if (rowEl.firstChild().isText()) {
        widget->setProperty("rowPortrait", qMax(0, rowEl.text().toInt()));
        widget->setProperty("rowLandscape", qMax(0, rowEl.text().toInt()));
    }
    else {
        widget->setProperty("rowPortrait", qMax(0, rowEl.firstChildElement("portrait").text().toInt()));
        widget->setProperty("rowLandscape", qMax(0, rowEl.firstChildElement("landscape").text().toInt()));
    }

    QDomElement colEl = el.firstChildElement("column");

    if (colEl.firstChild().isText()) {
        widget->setProperty("columnPortrait", qMax(0, colEl.text().toInt()));
        widget->setProperty("columnLandscape", qMax(0, colEl.text().toInt()));
    }
    else {
        widget->setProperty("columnPortrait", qMax(0, colEl.firstChildElement("portrait").text().toInt()));
        widget->setProperty("columnLandscape", qMax(0, colEl.firstChildElement("landscape").text().toInt()));
    }

    QDomElement rowSpanEl = el.firstChildElement("rowSpan");

    if (rowSpanEl.firstChild().isText()) {
        widget->setProperty("rowSpanPortrait", qMax(1, rowSpanEl.text().toInt()));
        widget->setProperty("rowSpanLandscape", qMax(1, rowSpanEl.text().toInt()));
    }
    else {
        widget->setProperty("rowSpanPortrait", qMax(1, rowSpanEl.firstChildElement("portrait").text().toInt()));
        widget->setProperty("rowSpanLandscape", qMax(1, rowSpanEl.firstChildElement("landscape").text().toInt()));
    }

    QDomElement colSpanEl = el.firstChildElement("colSpan");

    if (colSpanEl.firstChild().isText()) {
        widget->setProperty("colSpanPortrait", qMax(1, colSpanEl.text().toInt()));
        widget->setProperty("colSpanLandscape", qMax(1, colSpanEl.text().toInt()));
    }
    else {
        widget->setProperty("colSpanPortrait", qMax(1, colSpanEl.firstChildElement("portrait").text().toInt()));
        widget->setProperty("colSpanLandscape", qMax(1, colSpanEl.firstChildElement("landscape").text().toInt()));
    }

    QDomElement alignEl = el.firstChildElement("alignment");

    if (alignEl.firstChild().isText()) {
        widget->setProperty("alignmentPortrait", alignEl.text());
        widget->setProperty("alignmentLandscape", alignEl.text());
    }
    else if (!alignEl.firstChild().isNull()) {
        widget->setProperty("alignmentPortrait", alignEl.firstChildElement("portrait").text());
        widget->setProperty("alignmentLandscape", alignEl.firstChildElement("landscape").text());
    }
}

void ControlLoader::registerHandlersWithScriptEngine(QObject *obj, const QDomElement &el) {
    ScriptEngine::instance()->globalObject().setProperty(obj->objectName(), ScriptEngine::instance()->newQObject(obj));

    QDomNodeList nodes = el.childNodes();

    for (int i = 0; i < nodes.size(); i++) {
        QDomElement elem = nodes.at(i).toElement();
        QString tagName = elem.tagName();

        if ((tagName.startsWith("on")) && (tagName.size() > 3)) {
            QString handler = elem.text();

            if (!handler.isEmpty()) {
                QString signal = tagName.at(2).toLower() + tagName.mid(3);

                for (int i = 0; i < obj->metaObject()->methodCount(); i++) {
                    QMetaMethod method = obj->metaObject()->method(i);
                    QString signature = method.signature();

                    if (signature.left(signature.indexOf('(')) == signal) {
                        QStringList params;

                        foreach (QByteArray param, method.parameterNames()) {
                            params << param;
                        }

                        QScriptValue val = ScriptEngine::instance()->evaluate(QString("%1.%2.connect( %3 );").arg(obj->objectName()).arg(signal)
                                                                       .arg(handler.startsWith("function") ? handler : QString("function (%1) { %2 }").arg(params.join(",")).arg(handler)));

                        if (val.isError()) {
                            qWarning() << QObject::tr("Cannnot connect to signal %1: %2").arg(signal).arg(val.toString());
                        }

                        break;
                    }
                }
            }
        }
    }
}
