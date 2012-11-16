/* Copyright (C) 2012 Carlos Pais 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "get_user_input.h"

#include <QTextCodec>

GetUserInputEditorWidget* mEditorWidget = 0;
ActionInfo GetUserInput::Info;

GetUserInput::GetUserInput(QObject *parent) :
    Action(parent)
{
    init();
}

GetUserInput::GetUserInput(const QVariantMap& data, QObject *parent):
    Action(parent)
{
    init();

    QTextCodec * codec = QTextCodec::codecForName("utf-8");
    if (! codec)
        codec = QTextCodec::codecForTr();

    if (data.contains("message") && data.value("message").type() == QVariant::String)
        mMessage = codec->toUnicode( data.value("message").toByteArray());

    if (data.contains("variableName") && data.value("variableName").type() == QVariant::String)
        mVariableName = data.value("variableName").toByteArray();

    if (data.contains("defaultValue") && data.value("defaultValue").type() == QVariant::String)
        mDefaultValue = codec->toUnicode(data.value("defaultValue").toByteArray());

}

void GetUserInput::init()
{
    setType(Info.type);
    setName(Info.name);
    setIcon(Info.icon);
}

void GetUserInput::setGetUserInputEditorWidget(GetUserInputEditorWidget* widget)
{
    mEditorWidget = widget;
}

GetUserInputEditorWidget* GetUserInput::getUserInputEditorWidget()
{
    return mEditorWidget;
}

ActionEditorWidget* GetUserInput::editorWidget()
{
    return mEditorWidget;
}

QString GetUserInput::variableName()
{
    return mVariableName;
}

void GetUserInput::setVariableName(const QString & name)
{
    mVariableName = name;
}

QString GetUserInput::message()
{
    return mMessage;
}

void GetUserInput::setMessage(const QString & msg)
{
    mMessage = msg;
}

QString GetUserInput::defaultValue()
{
    return mDefaultValue;
}

void GetUserInput::setDefaultValue(const QString & value)
{
    mDefaultValue = value;
}

QVariantMap GetUserInput::toJsonObject()
{
    QVariantMap object = Action::toJsonObject();

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    if (! codec)
        codec = QTextCodec::codecForTr();

    object.insert("message", mMessage);
    object.insert("variableName", mVariableName);
    object.insert("defaultValue", mDefaultValue);

    return object;
}

