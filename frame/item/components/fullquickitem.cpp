/*
 * Copyright (C) 2022 ~ 2022 Deepin Technology Co., Ltd.
 *
 * Author:     donghualin <donghualin@uniontech.com>
 *
 * Maintainer: donghualin <donghualin@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "fullquickitem.h"
#include "pluginsiteminterface.h"

FullQuickItem::FullQuickItem(PluginsItemInterface *const pluginInter, QWidget *parent)
    : QuickSettingItem(pluginInter, parent)
    , m_centerWidget(pluginInter->itemWidget(QUICK_ITEM_KEY))
    , m_effectWidget(new DBlurEffectWidget(this))
{
    initUi();
}

FullQuickItem::~FullQuickItem()
{
    if (m_centerWidget)
        m_centerWidget->setParent(nullptr);
}

QuickSettingItem::QuickSettingType FullQuickItem::type() const
{
    return QuickSettingItem::QuickSettingType::Full;
}

bool FullQuickItem::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_centerWidget && event->type() == QEvent::Resize) {
        m_effectWidget->setFixedHeight(m_centerWidget->height());
        setFixedHeight(m_centerWidget->height());
    }
    return QuickSettingItem::eventFilter(obj, event);
}

void FullQuickItem::initUi()
{
    m_effectWidget->setMaskColor(QColor(239, 240, 245));
    m_effectWidget->setBlurRectXRadius(8);
    m_effectWidget->setBlurRectYRadius(8);

    QIcon icon = pluginItem()->icon(DockPart::QuickPanel);
    if (icon.isNull())
        return;

    // 如果图标不为空
    if (!m_centerWidget)
        return;

    QHBoxLayout *layout = new QHBoxLayout(m_effectWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignHCenter);
    layout->addWidget(m_centerWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_effectWidget);

    m_centerWidget->installEventFilter(this);
}