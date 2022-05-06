/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
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

#include "computecommand_p.h"
#include <Qt3DCore/qnode.h>
#include <Qt3DRender/private/qcomputecommand_p.h>
#include <Qt3DRender/private/abstractrenderer_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

namespace Render {

ComputeCommand::ComputeCommand()
    : BackendNode(ReadWrite)
    , m_frameCount(0)
    , m_runType(QComputeCommand::Continuous)
    , m_hasReachedFrameCount(false)
{
    m_workGroups[0] = 1;
    m_workGroups[1] = 1;
    m_workGroups[2] = 1;
}

ComputeCommand::~ComputeCommand()
{
}

void ComputeCommand::cleanup()
{
    QBackendNode::setEnabled(false);
    m_workGroups[0] = 1;
    m_workGroups[1] = 1;
    m_workGroups[2] = 1;
    m_frameCount = 0;
    m_runType = QComputeCommand::Continuous;
    m_hasReachedFrameCount = false;
}

void ComputeCommand::syncFromFrontEnd(const Qt3DCore::QNode *frontEnd, bool firstTime)
{
    const QComputeCommand *node = qobject_cast<const QComputeCommand *>(frontEnd);
    if (!node)
        return;

    const bool wasEnabled = isEnabled();
    BackendNode::syncFromFrontEnd(frontEnd, firstTime);
    if (wasEnabled != isEnabled())
        markDirty(AbstractRenderer::ComputeDirty);

    if (m_workGroups[0] != node->workGroupX()) {
        m_workGroups[0] = node->workGroupX();
        markDirty(AbstractRenderer::ComputeDirty);
    }
    if (m_workGroups[1] != node->workGroupY()) {
        m_workGroups[1] = node->workGroupY();
        markDirty(AbstractRenderer::ComputeDirty);
    }
    if (m_workGroups[2] != node->workGroupZ()) {
        m_workGroups[2] = node->workGroupZ();
        markDirty(AbstractRenderer::ComputeDirty);
    }
    if (node->runType() != m_runType) {
        m_runType = node->runType();
        markDirty(AbstractRenderer::ComputeDirty);
    }
    const QComputeCommandPrivate *d = static_cast<const QComputeCommandPrivate *>(Qt3DCore::QNodePrivate::get(node));
    // Check frame count only if frontend is enabled
    // If disabled that means we might have disabled the frontend because
    // framecount reached 0
    if (d->m_enabled && d->m_frameCount != m_frameCount) {
        m_frameCount = d->m_frameCount;
        m_hasReachedFrameCount = m_frameCount <= 0;
        markDirty(AbstractRenderer::ComputeDirty);
    }

    if (firstTime)
        markDirty(AbstractRenderer::ComputeDirty);
}

// Called from buildComputeRenderCommands in a job
void ComputeCommand::updateFrameCount()
{
    // Disable frontend node when reaching 0
    --m_frameCount;
    if (m_frameCount <= 0)
        m_hasReachedFrameCount = true;
    // Backend will be disabled on the next sync
}

void ComputeCommand::resetHasReachedFrameCount()
{
    m_hasReachedFrameCount = false;
}

bool ComputeCommand::hasReachedFrameCount() const
{
    return m_hasReachedFrameCount;
}

} // Render

} // Qt3DRender

QT_END_NAMESPACE
