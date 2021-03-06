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

#ifndef VERIFIER_H
#define VERIFIER_H

#include <KTextEdit>

class RegexpHighlighter;

class Verifier : public KTextEdit
{
    Q_OBJECT
public:
    explicit Verifier(QWidget *parent);
    void setHighlighter(RegexpHighlighter *);

public Q_SLOTS:
    void verify(const QString &regexp);
    void clearRegexp();
    void setCaseSensitive(bool);
    void setMinimal(bool);

    // I have no way of telling the current paragrahp when highlighting - thefore scrolling to next/prev match
    // do not work. Enable this when they work.
    // void gotoFirst();
    // void gotoPrev();
    // void gotoNext();
    // void gotoLast();
    //Q_SIGNALS:
    //    void countChanged( int );
    // void currentChanged( int );
    // void goBackwardPossible( bool );
    // void goForwardPossible( bool );

    // protected:
    //   void gotoNum( int );

private:
    int _count;
    // int _current;
    RegexpHighlighter *_highlighter = nullptr;
};

#endif // VERIFIER_H
