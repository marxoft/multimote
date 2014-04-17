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

#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QScriptEngine>

class ScriptEngine : public QScriptEngine
{
    Q_OBJECT

public:
    explicit ScriptEngine(QObject *parent = 0);
    
    inline static ScriptEngine* instance() { return self; }
    
private:
    static ScriptEngine *self;

    Q_DISABLE_COPY(ScriptEngine)
};

#endif // SCRIPTENGINE_H
