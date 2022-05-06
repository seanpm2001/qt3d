/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

#include "qscene2d.h"
#include "qscene2d_p.h"
#include "scene2d_p.h"
#include "scene2dmanager_p.h"
#include "scene2devent_p.h"
#include "scene2dsharedobject_p.h"

QT_BEGIN_NAMESPACE

using namespace Qt3DCore;

namespace Qt3DRender {

namespace Quick {


/*!
    \internal
     Constructs object shared by the front-end and back-end to synchronize the rendering.
 */
Scene2DSharedObject::Scene2DSharedObject(Scene2DManager *manager)
    : m_renderControl(nullptr)
    , m_quickWindow(nullptr)
    , m_renderManager(manager)
    , m_surface(nullptr)
    , m_renderThread(nullptr)
    , m_renderObject(nullptr)
    , m_disallowed(false)
    , m_quit(false)
    , m_requestSync(false)
    , m_prepared(false)
    , m_initialized(false)
{
}

Scene2DSharedObject::~Scene2DSharedObject()
{
}

void Scene2DSharedObject::cleanup()
{
    delete m_renderControl;
    delete m_quickWindow;
    delete m_surface;
    m_renderControl = nullptr;
    m_quickWindow = nullptr;
    m_surface = nullptr;
    m_initialized = false;
}

bool Scene2DSharedObject::canRender() const
{
    return m_initialized && m_prepared && !m_disallowed;
}

bool Scene2DSharedObject::isInitialized() const
{
    return m_initialized;
}

void Scene2DSharedObject::disallowRender()
{
    m_disallowed = true;
}

void Scene2DSharedObject::setInitialized()
{
    m_initialized = true;
}

bool Scene2DSharedObject::isPrepared() const
{
    return m_prepared;
}

void Scene2DSharedObject::setPrepared()
{
    m_prepared = true;
}

// not protected, call only from main thread
bool Scene2DSharedObject::isQuit() const
{
    Q_ASSERT(QThread::currentThread() == QCoreApplication::instance()->thread());
    return m_quit;
}

// not protected, call only from main thread
void Scene2DSharedObject::requestQuit()
{
    Q_ASSERT(QThread::currentThread() == QCoreApplication::instance()->thread());
    m_quit = true;
    QCoreApplication::postEvent(m_renderObject, new Scene2DEvent(Scene2DEvent::Quit));
}

bool Scene2DSharedObject::isSyncRequested() const
{
    return m_requestSync;
}

void Scene2DSharedObject::requestRender(bool sync)
{
    m_requestSync = sync;
    QCoreApplication::postEvent(m_renderObject, new Scene2DEvent(Scene2DEvent::Render));
}

void Scene2DSharedObject::wait()
{
    m_cond.wait(&m_mutex);
}

void Scene2DSharedObject::wake()
{
    m_cond.wakeOne();
}

void Scene2DSharedObject::clearSyncRequest()
{
    m_requestSync = false;
}

} // namespace Quick
} // namespace Qt3DRender

QT_END_NAMESPACE
