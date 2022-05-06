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

#ifndef QT3DRENDER_RENDER_NODEFUNCTOR_P_H
#define QT3DRENDER_RENDER_NODEFUNCTOR_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <Qt3DCore/qnode.h>
#include <Qt3DRender/private/backendnode_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

namespace Render {

class AbstractRenderer;

template<class Backend, class Manager>
class NodeFunctor : public Qt3DCore::QBackendNodeMapper
{
public:
    explicit NodeFunctor(AbstractRenderer *renderer)
        : m_manager(renderer->nodeManagers()->manager<Backend, Manager>())
        , m_renderer(renderer)
    {
    }

    Qt3DCore::QBackendNode *create(Qt3DCore::QNodeId id) const final
    {
        Backend *backend = m_manager->getOrCreateResource(id);
        backend->setRenderer(m_renderer);
        return backend;
    }

    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const final
    {
        return m_manager->lookupResource(id);
    }

    void destroy(Qt3DCore::QNodeId id) const final
    {
        m_manager->releaseResource(id);
    }

private:
    Manager *m_manager;
    AbstractRenderer *m_renderer;
};

} // namespace Render

} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_NODEFUNCTOR_P_H
