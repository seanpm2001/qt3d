/****************************************************************************
**
** Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
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

#include "lerpclipblend_p.h"
#include <Qt3DAnimation/qlerpclipblend.h>
#include <Qt3DAnimation/private/qlerpclipblend_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DAnimation {

namespace Animation {

LerpClipBlend::LerpClipBlend()
    : ClipBlendNode(ClipBlendNode::LerpBlendType)
    , m_startClipId()
    , m_endClipId()
    , m_blendFactor(0.0f)
{
}

LerpClipBlend::~LerpClipBlend()
{
}

void LerpClipBlend::syncFromFrontEnd(const Qt3DCore::QNode *frontEnd, bool firstTime)
{
    BackendNode::syncFromFrontEnd(frontEnd, firstTime);
    const QLerpClipBlend *node = qobject_cast<const QLerpClipBlend *>(frontEnd);
    if (!node)
        return;

    m_blendFactor = node->blendFactor();
    m_startClipId = Qt3DCore::qIdForNode(node->startClip());
    m_endClipId = Qt3DCore::qIdForNode(node->endClip());
}

ClipResults LerpClipBlend::doBlend(const QList<ClipResults> &blendData) const
{
    Q_ASSERT(blendData.size() == 2);
    Q_ASSERT(blendData[0].size() == blendData[1].size());
    const int elementCount = blendData.first().size();
    ClipResults blendResults(elementCount);

    for (int i = 0; i < elementCount; ++i)
        blendResults[i] = (1.0f - m_blendFactor) * blendData[0][i] + (m_blendFactor * blendData[1][i]);

    return blendResults;
}

double LerpClipBlend::duration() const
{
    ClipBlendNode *startNode = clipBlendNodeManager()->lookupNode(m_startClipId);
    const double startNodeDuration = startNode ? startNode->duration() : 0.0;

    ClipBlendNode *endNode = clipBlendNodeManager()->lookupNode(m_endClipId);
    const double endNodeDuration = endNode ? endNode->duration() : 0.0;

    return (1.0 - static_cast<double>(m_blendFactor)) * startNodeDuration + static_cast<double>(m_blendFactor) * endNodeDuration;
}

} // Animation

} // Qt3DAnimation

QT_END_NAMESPACE
