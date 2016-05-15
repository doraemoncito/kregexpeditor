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

#include "kmultiformlistbox-windowed.h"

#include <QVBoxLayout>

#include <KLocale>
#include <KListWidget>
#include <KMessageBox>
#include <KPushButton>

#include "widgetwindow.h"
#include "windowlistboxitem.h"

KMultiFormListBoxWindowed::KMultiFormListBoxWindowed(KMultiFormListBoxFactory *factory, QWidget *parent,
																	 bool showUpDownButtons, bool showHelpButton,
																	 QString addButtonText)
  : QWidget( parent )
{
  _layout = new QVBoxLayout(this);

	QHBoxLayout *innerLayout = new QHBoxLayout();
	_layout->addLayout(innerLayout);

  _listbox = new KListWidget(this/*,"listbox"*/);
  _listbox->setSelectionMode(QAbstractItemView::SingleSelection);
  innerLayout->addWidget(_listbox);

  QVBoxLayout *buttons = new QVBoxLayout();
  innerLayout->addLayout(buttons);

  KPushButton *but = new KPushButton(addButtonText, this);
  but->setObjectName("Add Button");
  buttons->addWidget(but,0);
  connect(but, SIGNAL(clicked()), this, SLOT(addNewElement()));

  but = new KPushButton(i18n("Edit"), this);
  but->setObjectName("Edit Button");
  buttons->addWidget(but,0);
  connect(but,SIGNAL(clicked()), this, SLOT(slotEditSelected()));
  connect(_listbox, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(slotEditSelected(QListWidgetItem *)));
	_buttonList.append(but);

  but = new KPushButton(i18n("Delete"), this);
  but->setObjectName("Delete Button");
  buttons->addWidget(but,0);
  connect(but, SIGNAL(clicked()), this, SLOT(slotDeleteEntry()));
	_buttonList.append(but);

  but = new KPushButton(i18n("Copy"), this);
  but->setObjectName("Copy Button");
  buttons->addWidget(but,0);
  connect(but, SIGNAL(clicked()), this, SLOT(slotCopySelected()));
	_buttonList.append(but);

	if (showUpDownButtons) {
		but = new KPushButton(i18n("Up"), this);
		but->setObjectName("Up Button");
		buttons->addWidget(but, 0);
		connect(but, SIGNAL(clicked()), this, SLOT(slotMoveItemUp()));
		_buttonList.append(but);

		but = new KPushButton(i18n("Down"), this);
		but->setObjectName( "Down Button");
		buttons->addWidget(but, 0);
		connect(but, SIGNAL(clicked()), this, SLOT(slotMoveItemDown()));
		_buttonList.append(but);
	}

	if (showHelpButton) {
		but = new KPushButton(KStandardGuiItem::help(), this);
		but->setObjectName( "Help Button");
		buttons->addWidget(but, 0);
		connect(but, SIGNAL(clicked()), this, SIGNAL(showHelp()));
	}

  buttons->addStretch(1);
  _factory = factory;
	slotUpdateButtonState();

}

KMultiFormListBoxEntryList KMultiFormListBoxWindowed::elements()
{
  KMultiFormListBoxEntryList list;
  for ( int i=0; i < _listbox->count(); ++i) {
    WindowListboxItem *item = (WindowListboxItem *) _listbox->item(i);
    list.append(item->entry());
  }
  return list;
}

void KMultiFormListBoxWindowed::delElement(QWidget * /*elm*/)
{
    // kDebug() << "KMultiFormListBoxWindowed::delElement NOT YET IMPLEMENTED";
	// TODO
}

void KMultiFormListBoxWindowed::delAnElement()
{
    // kDebug() << "KMultiFormListBoxWindowed::delAnElement NOT YET IMPLEMENTED";
  // TODO
}


void KMultiFormListBoxWindowed::append(KMultiFormListBoxEntry *elm)
{
  (void) new WidgetWindow(_factory, elm, _listbox);
	slotUpdateButtonState();
}

void KMultiFormListBoxWindowed::addNewElement()
{
	// kDebug() << "addNewElement " << _factory << "," << _listbox ;

  QWidget *widget = new WidgetWindow(_factory, _listbox);
	widget->show();
	connect(widget, SIGNAL(finished()), this, SLOT(slotUpdateButtonState()));
}

void KMultiFormListBoxWindowed::addElement()
{
  new WidgetWindow(_factory, _listbox);
	slotUpdateButtonState();
}

void KMultiFormListBoxWindowed::slotEditSelected(QListWidgetItem *item)
{
  ((WindowListboxItem *) item)->displayWidget();
}

void KMultiFormListBoxWindowed::slotEditSelected()
{
  WindowListboxItem *item = selected();
  if (item) {
    slotEditSelected(item);
  }
}

void KMultiFormListBoxWindowed::slotDeleteEntry()
{
  WindowListboxItem *item = selected();
  if (item) {
		int answer =
			KMessageBox::warningContinueCancel(0, i18n("Delete item \"%1\"?", item->text()),i18n("Delete Item"),KStandardGuiItem::del());
		if (answer == KMessageBox::Continue) {
			delete item;
			slotUpdateButtonState();
		}
  }
}

void KMultiFormListBoxWindowed::slotCopySelected()
{
  WindowListboxItem *item = selected();
  if (item) {
    item->cloneItem();
  }
}

WindowListboxItem *KMultiFormListBoxWindowed::selected()
{
    /*
  int i = _listbox->currentItem();
  if (i == -1) {
    return 0;
  } else {
    return (WindowListboxItem *) _listbox->item(i);
  }
  */
    return (WindowListboxItem *) _listbox->currentItem();
}

void KMultiFormListBoxWindowed::slotMoveItemUp()
{
	WindowListboxItem *item = selected();
	if (item == 0)
		return;

	int index = _listbox->row(item);
	if (index != 0) {
		_listbox->takeItem(index);
		_listbox->insertItem(index-1, item);
		_listbox->setCurrentItem(item);
	}
}

void KMultiFormListBoxWindowed::slotMoveItemDown()
{
	WindowListboxItem *item = selected();
	if (item == 0)
		return;

	int index = _listbox->row(item);
	if (index < _listbox->count()) {
		_listbox->takeItem(index);
		_listbox->insertItem(index+1, item);
		_listbox->setCurrentItem(item);
	}
}

void KMultiFormListBoxWindowed::slotUpdateButtonState()
{
	bool on = (_listbox->count() != 0);
	for (int i=0; i<_buttonList.count(); i++) {
		_buttonList.at(i)->setEnabled(on);
	}
}

