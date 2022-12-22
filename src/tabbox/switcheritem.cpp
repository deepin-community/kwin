/*
    KWin - the KDE window manager
    This file is part of the KDE project.

    SPDX-FileCopyrightText: 2013 Martin Gräßlin <mgraesslin@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "switcheritem.h"
// KWin
#include "abstract_output.h"
#include "composite.h"
#include "tabboxhandler.h"
#include "screens.h"
#include "workspace.h"
#include "tabbox.h"
#include "abstract_client.h"
#include "composite.h"
// Qt
#include <QAbstractItemModel>

namespace KWin
{
namespace TabBox
{

SwitcherItem::SwitcherItem(QObject *parent)
    : QObject(parent)
    , m_model(nullptr)
    , m_item(nullptr)
    , m_visible(false)
    , m_allDesktops(false)
    , m_currentIndex(0)
{
    m_selectedIndexConnection = connect(tabBox, &TabBoxHandler::selectedIndexChanged, this, [this] {
        if (isVisible()) {
            setCurrentIndex(tabBox->currentIndex().row());
        }
    });
    connect(screens(), &Screens::changed, this, &SwitcherItem::screenGeometryChanged);
    connect(Compositor::self(), &Compositor::compositingToggled, this, &SwitcherItem::compositingChanged);
}

SwitcherItem::~SwitcherItem()
{
    disconnect(m_selectedIndexConnection);
}

void SwitcherItem::setItem(QObject *item)
{
    if (m_item == item) {
        return;
    }
    m_item = item;
    Q_EMIT itemChanged();
}

void SwitcherItem::setModel(QAbstractItemModel *model)
{
    m_model = model;
    Q_EMIT modelChanged();
}

void SwitcherItem::setVisible(bool visible)
{
    if (m_visible == visible) {
        return;
    }
    if (visible)
        Q_EMIT screenGeometryChanged();
    m_visible = visible;
    Q_EMIT visibleChanged();
}

QRect SwitcherItem::screenGeometry() const
{
    return workspace()->activeOutput()->geometry();
}

void SwitcherItem::setCurrentIndex(int index)
{
    if (m_currentIndex == index) {
        return;
    }
    m_currentIndex = index;
    if (m_model) {
        tabBox->setCurrentIndex(m_model->index(index, 0));
    }
    if (!Compositor::compositing() && index == 0) {
        if (index != tabBox->clientList().count() -1) {
            for (int i = 0; i < tabBox->clientList().count() -1; i++) {
                AbstractClient *c = TabBox::self()->currentClientList().at(i);
                if (i != index) {
                    c->setMinimized(TabBox::self()->getAllClientIsMinisize().at(i));
                }
            }
        }
    }
    Q_EMIT currentIndexChanged(m_currentIndex);
}

void SwitcherItem::setAllDesktops(bool all)
{
    if (m_allDesktops == all) {
        return;
    }
    m_allDesktops = all;
    Q_EMIT allDesktopsChanged();
}

void SwitcherItem::setNoModifierGrab(bool set)
{
    if (m_noModifierGrab == set) {
        return;
    }
    m_noModifierGrab = set;
    Q_EMIT noModifierGrabChanged();
}

bool SwitcherItem::compositing()
{
    return Compositor::compositing();
}

}
}
