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

#ifndef __multicontainerwidget
#define __multicontainerwidget

#include "regexpwidget.h"

#include <QList>

/**
   Abstract RegExp widget class representing widgets having multiple children.
   @internal
*/
class MultiContainerWidget : public RegExpWidget
{
public:
    explicit MultiContainerWidget(RegExpEditorWindow *editorWindow, QWidget *parent = nullptr);
    bool hasSelection() const override;
    void clearSelection() override;
    void deleteSelection() override;
    void addNewChild(DragAccepter *accepter, RegExpWidget *child) override;
    bool updateSelection(bool parentSelected) override;
    QRect selectionRect() const override;
    RegExpWidget *widgetUnderPoint(QPoint globalPos, bool justVisibleWidgets) override;
    RegExpWidget *findWidgetToEdit(QPoint globalPos) override;
    void selectWidget(bool sel) override;
    void updateAll() override;
    void updateCursorRecursively() override;

protected:
    void append(RegExpWidget *child);
    QList<RegExpWidget *> _children;
};

#endif // __multicontainerwidget
