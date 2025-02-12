// Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
// SPDX-FileCopyrightText: 2018 - 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef FASHIONTRAYITEM_H
#define FASHIONTRAYITEM_H

#include "constants.h"
#include "../trayplugin.h"
#include "fashiontraywidgetwrapper.h"
#include "fashiontraycontrolwidget.h"
#include "containers/normalcontainer.h"
#include "containers/attentioncontainer.h"
#include "containers/holdcontainer.h"

#include <QWidget>
#include <QPointer>
#include <QBoxLayout>
#include <QLabel>

#include "../abstracttraywidget.h"

#define FASHION_MODE_ITEM_KEY   "fashion-mode-item"

class FashionTrayItem : public QWidget
{
    Q_OBJECT

public:
    explicit FashionTrayItem(TrayPlugin *trayPlugin, QWidget *parent = 0);

    void setTrayWidgets(const QMap<QString, AbstractTrayWidget *> &itemTrayMap);
    void trayWidgetAdded(const QString &itemKey, AbstractTrayWidget *trayWidget);
    void trayWidgetRemoved(AbstractTrayWidget *trayWidget);
    void clearTrayWidgets();

    void setDockPosition(Dock::Position pos);

    inline static int trayWidgetWidth() {return TrayWidgetWidth;}
    inline static int trayWidgetHeight() {return TrayWidgetHeight;}

public slots:
    void onExpandChanged(const bool expand);
    void setRightSplitVisible(const bool visible);
    void onPluginSettingsChanged();

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    bool event(QEvent *event) override;

private:
    void init();
    void resizeTray();

private Q_SLOTS:
    void onWrapperAttentionChanged(FashionTrayWidgetWrapper *wrapper, const bool attention);
    void attentionWrapperToNormalWrapper();
    void normalWrapperToAttentionWrapper(FashionTrayWidgetWrapper *wrapper);
    void requestResize();
    void onRequireDraggingWrapper();

private:
    QBoxLayout *m_mainBoxLayout;
    QTimer *m_attentionDelayTimer;

    TrayPlugin *m_trayPlugin;
    FashionTrayControlWidget *m_controlWidget;          //展开按钮

    NormalContainer *m_normalContainer;                 //左侧可展开窗口
    AttentionContainer *m_attentionContainer;
    HoldContainer *m_holdContainer;                     //常驻窗口

    static int TrayWidgetWidth;
    static int TrayWidgetHeight;
    QWidget *m_leftSpace;
    Dock::Position m_dockpos;
    int m_iconSize  = 40;
};

#endif // FASHIONTRAYITEM_H
