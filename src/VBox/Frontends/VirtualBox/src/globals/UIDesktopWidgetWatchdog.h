/* $Id$ */
/** @file
 * VBox Qt GUI - UIDesktopWidgetWatchdog class declaration.
 */

/*
 * Copyright (C) 2015-2016 Oracle Corporation
 *
 * This file is part of VirtualBox Open Source Edition (OSE), as
 * available from http://www.virtualbox.org. This file is free software;
 * you can redistribute it and/or modify it under the terms of the GNU
 * General Public License (GPL) as published by the Free Software
 * Foundation, in version 2 as it comes in the "COPYING" file of the
 * VirtualBox OSE distribution. VirtualBox OSE is distributed in the
 * hope that it will be useful, but WITHOUT ANY WARRANTY of any kind.
 */

#ifndef ___UIDesktopWidgetWatchdog_h___
#define ___UIDesktopWidgetWatchdog_h___

/* Qt includes: */
#include <QObject>
#ifdef VBOX_WS_X11
# include <QVector>
# include <QRect>
#endif /* VBOX_WS_X11 */

/* Forward declarations: */
#if QT_VERSION >= 0x050000
class QScreen;
#endif /* QT_VERSION >= 0x050000 */

/** QObject extension used as
  * a desktop-widget watchdog aware
  * of the host-screen geometry changes. */
class UIDesktopWidgetWatchdog : public QObject
{
    Q_OBJECT;

signals:

    /** Notifies about host-screen count change to @a cHostScreenCount. */
    void sigHostScreenCountChanged(int cHostScreenCount);

    /** Notifies about resize for the host-screen with @a iHostScreenIndex. */
    void sigHostScreenResized(int iHostScreenIndex);

    /** Notifies about work-area resize for the host-screen with @a iHostScreenIndex. */
    void sigHostScreenWorkAreaResized(int iHostScreenIndex);

public:

    /** Constructs watchdog for the @a pParent being passed into the base-class. */
    UIDesktopWidgetWatchdog(QObject *pParent);
    /** Destructs watchdog. */
    ~UIDesktopWidgetWatchdog();

    /** Returns the host-screen count. */
    int screenCount() const;

    /** Returns the geometry of the host-screen with @a iHostScreenIndex.
      * @note The default screen is used if @a iHostScreenIndex is -1. */
    const QRect screenGeometry(int iHostScreenIndex = -1) const;
    /** Returns the available-geometry of the host-screen with @a iHostScreenIndex.
      * @note The default screen is used if @a iHostScreenIndex is -1. */
    const QRect availableGeometry(int iHostScreenIndex = -1) const;

private slots:

    /** Handles host-screen count change to @a cHostScreenCount. */
    void sltHandleHostScreenCountChanged(int cHostScreenCount);
    /** Handles @a pHostScreen adding. */
    void sltHostScreenAdded(QScreen *pHostScreen);
    /** Handles @a pHostScreen removing. */
    void sltHostScreenRemoved(QScreen *pHostScreen);

    /** Handles resize for the host-screen with @a iHostScreenIndex. */
    void sltHandleHostScreenResized(int iHostScreenIndex);

    /** Handles work-area resize for the host-screen with @a iHostScreenIndex. */
    void sltHandleHostScreenWorkAreaResized(int iHostScreenIndex);

#ifdef VBOX_WS_X11
    /** Handles @a availableGeometry calculation result for the host-screen with @a iHostScreenIndex. */
    void sltHandleHostScreenAvailableGeometryCalculated(int iHostScreenIndex, QRect availableGeometry);
#endif /* VBOX_WS_X11 */

private:

    /** Prepare routine. */
    void prepare();
    /** Cleanup routine. */
    void cleanup();

#ifdef VBOX_WS_X11
    /** Updates host-screen configuration according to new @a cHostScreenCount.
      * @note If cHostScreenCount is equal to -1 we have to acquire it ourselves. */
    void updateHostScreenConfiguration(int cHostScreenCount = -1);

    /** Update available-geometry for the host-screen with @a iHostScreenIndex. */
    void updateHostScreenAvailableGeometry(int iHostScreenIndex);

    /** Cleanups existing workers. */
    void cleanupExistingWorkers();

    /** Holds current host-screen available-geometries. */
    QVector<QRect> m_availableGeometryData;
    /** Holds current workers determining host-screen available-geometries. */
    QVector<QWidget*> m_availableGeometryWorkers;
#endif /* VBOX_WS_X11 */
};

#endif /* !___UIDesktopWidgetWatchdog_h___ */

