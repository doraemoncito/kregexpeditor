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

#ifndef CHARSELECTOR_H
#define CHARSELECTOR_H

#include <QWidget>

class QComboBox;
class QStackedWidget;
class LimitedCharLineEdit;

class CharSelector : public QWidget
{
    Q_OBJECT

public:
    explicit CharSelector(QWidget *parent);
    QString text() const;
    void setText(const QString &text);
    bool isEmpty() const;

protected:
    void fillComboBox();

private Q_SLOTS:
    void slotNewItem(int which);

private:
    QComboBox *_type = nullptr;
    QStackedWidget *_stack = nullptr;
    LimitedCharLineEdit *_normal = nullptr;
    LimitedCharLineEdit *_hex = nullptr;
    LimitedCharLineEdit *_oct = nullptr;
    int _oldIndex = 0;
};

#endif // CHARSELECTOR_H
