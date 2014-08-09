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

#include "scriptengine.h"
#include "notifications.h"
#include "screen.h"
#include "../prototypes/prototypes.h"
#ifdef HTTP_PROTOCOL
#include "../protocols/http/http.h"
#endif
#ifdef BT_PROTOCOL
#include "../protocols/bluetooth/bluetooth.h"
#endif
#ifdef IR_PROTOCOL
#include "../protocols/infrared/infrared.h"
#endif

ScriptEngine* ScriptEngine::self = 0;

ScriptEngine::ScriptEngine(QObject *parent) :
    QScriptEngine(parent)
{
    if (!self) {
        self = this;
    }

    QScriptValue keyProto = this->newQObject(new KeyEventPrototype(this));
    QScriptValue mouseProto = this->newQObject(new MouseEventPrototype(this));
    QScriptValue itemProto = this->newQObject(new SelectionItemPrototype(this));

    this->setDefaultPrototype(qMetaTypeId<QKeyEvent*>(), keyProto);
    this->setDefaultPrototype(qMetaTypeId<QMouseEvent*>(), mouseProto);
    this->setDefaultPrototype(qMetaTypeId<SelectionItem*>(), itemProto);

    this->globalObject().setProperty("Qt", this->newQMetaObject(&ScriptEngine::staticQtMetaObject));
    this->globalObject().setProperty("notifications", this->newQObject(new Notifications(this)));
    this->globalObject().setProperty("screen", this->newQObject(new Screen(this)));
#ifdef HTTP_PROTOCOL
    this->globalObject().setProperty("http", this->newQObject(new Http(this)));
#endif
#ifdef BT_PROTOCOL
    this->globalObject().setProperty("bluetooth", this->newQObject(new Bluetooth(this)));
#endif
#ifdef IR_PROTOCOL
    this->globalObject().setProperty("infrared", this->newQObject(new Infrared(this)));
#endif
    this->installTranslatorFunctions();
}
