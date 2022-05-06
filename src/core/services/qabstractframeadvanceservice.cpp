/****************************************************************************
**
** Copyright (C) 2015 Paul Lemire
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

#include "qabstractframeadvanceservice_p.h"
#include "qabstractframeadvanceservice_p_p.h"

QT_BEGIN_NAMESPACE

namespace Qt3DCore {


/* !\internal
    \class Qt3DCore::QAbstractFrameAdvanceService
    \inmodule Qt3DCore
    \brief Interface for a Qt3D frame advance service.

    This is an interface class that should be subclassed by providers of the
    frame advance service. When used with the Renderer aspect, the aspect needs to
    be the one providing the ticks depending on the vertical refresh rate. When
    used with no Renderer aspect, a default tick clock implementation can be
    used.
*/


QAbstractFrameAdvanceService::QAbstractFrameAdvanceService(const QString &description)
    : QAbstractServiceProvider(QServiceLocator::FrameAdvanceService, description)
{

}

QAbstractFrameAdvanceService::QAbstractFrameAdvanceService(QAbstractFrameAdvanceServicePrivate &dd)
    : QAbstractServiceProvider(dd)
{

}

/*
    \fn qint64 Qt3DCore::QAbstractFrameAdvanceService::waitForNextFrame()

    Returns the current time, the call may be blocking if waiting for a tick.
*/

/*
    \fn void Qt3DCore::QAbstractFrameAdvanceService::start()

    Starts the service.
*/

/*
    \fn void Qt3DCore::QAbstractFrameAdvanceService::stop()

    Stops the service, performing any cleanup deemed necessary.
*/

} // Qt3D

QT_END_NAMESPACE
