/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
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

#include "viewportnode_p.h"
#include <Qt3DRender/qviewport.h>
#include <Qt3DRender/private/qviewport_p.h>

QT_BEGIN_NAMESPACE

using namespace Qt3DCore;

namespace Qt3DRender {
namespace Render {

ViewportNode::ViewportNode()
    : FrameGraphNode(FrameGraphNode::Viewport)
    , m_xMin(0.0f)
    , m_yMin(0.0f)
    , m_xMax(1.0f)
    , m_yMax(1.0f)
    , m_gamma(2.2f)
{
}


void ViewportNode::syncFromFrontEnd(const QNode *frontEnd, bool firstTime)
{
    const QViewport *node = qobject_cast<const QViewport *>(frontEnd);
    if (!node)
        return;

    FrameGraphNode::syncFromFrontEnd(frontEnd, firstTime);

    const QRectF oldRect(m_xMin, m_yMin, m_xMax, m_yMax);
    if (oldRect != node->normalizedRect()) {
        m_xMin = node->normalizedRect().x();
        m_yMin = node->normalizedRect().y();
        m_xMax = node->normalizedRect().width();
        m_yMax = node->normalizedRect().height();
        markDirty(AbstractRenderer::FrameGraphDirty);
    }

    if (node->gamma() != m_gamma) {
        m_gamma = node->gamma();
        markDirty(AbstractRenderer::FrameGraphDirty);
    }
}

float ViewportNode::xMin() const
{
    return m_xMin;
}

void ViewportNode::setXMin(float xMin)
{
    m_xMin = xMin;
}
float ViewportNode::yMin() const
{
    return m_yMin;
}

void ViewportNode::setYMin(float yMin)
{
    m_yMin = yMin;
}
float ViewportNode::xMax() const
{
    return m_xMax;
}

void ViewportNode::setXMax(float xMax)
{
    m_xMax = xMax;
}
float ViewportNode::yMax() const
{
    return m_yMax;
}

void ViewportNode::setYMax(float yMax)
{
    m_yMax = yMax;
}

float ViewportNode::gamma() const
{
    return m_gamma;
}

void ViewportNode::setGamma(float gamma)
{
    m_gamma = gamma;
}

QRectF ViewportNode::computeViewport(const QRectF &childViewport, const ViewportNode *parentViewport)
{
    QRectF vp(parentViewport->xMin(),
              parentViewport->yMin(),
              parentViewport->xMax(),
              parentViewport->yMax());

    if (childViewport.isEmpty()) {
        return vp;
    } else {
        return QRectF(vp.x() + vp.width() * childViewport.x(),
                      vp.y() + vp.height() * childViewport.y(),
                      vp.width() * childViewport.width(),
                      vp.height() * childViewport.height());
    }
}

} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE
