/*
 *  Copyright (c) 2002-2003 Jesper K. Pedersen <blackie@kde.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License version 2 as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 **/
#ifndef __selectablelineedit
#define __selectablelineedit

#include <QLineEdit>

class RegExpWidget;

/**
   A specialized QLineEdit for use in @ref TextWidget.

   This widget has two main features:
   @li when the @ref TextWidget which contains it is selected, then the
        line edit is grayed like the rest of the widgets.
   @li When the widget does not have the focus, it is resized to only be
        large enough to contain the text written in it.

   @internal
*/
class SelectableLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit SelectableLineEdit(RegExpWidget *owner, QWidget *parent = nullptr, const QString &name = QString());
    void setSelected(bool selected);
    QSize sizeHint() const override;

protected Q_SLOTS:
    void slotKeyPressed();

Q_SIGNALS:
    void parentPleaseUpdate();

private:
    RegExpWidget *_owner = nullptr;
};

#endif
