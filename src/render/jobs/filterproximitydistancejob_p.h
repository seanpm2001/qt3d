/****************************************************************************
**
** Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB).
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

#ifndef QT3DRENDER_RENDER_FILTERPROXIMITYDISTANCEJOB_P_H
#define QT3DRENDER_RENDER_FILTERPROXIMITYDISTANCEJOB_P_H

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

#include <Qt3DCore/qaspectjob.h>
#include <Qt3DCore/qnodeid.h>
#include <Qt3DRender/private/qt3drender_global_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

namespace Render {

class Entity;
class NodeManagers;

class Q_3DRENDERSHARED_PRIVATE_EXPORT FilterProximityDistanceJob : public Qt3DCore::QAspectJob
{
public:
    FilterProximityDistanceJob();
    ~FilterProximityDistanceJob();

    inline void setManager(NodeManagers *manager) { m_manager = manager; }
    inline void setProximityFilterIds(const Qt3DCore::QNodeIdVector &proximityFilterIds) { m_proximityFilterIds = proximityFilterIds; }
    inline bool hasProximityFilter() const { return !m_proximityFilterIds.empty(); }

    // QAspectJob interface
    void run() final;
    const std::vector<Entity *> &filteredEntities() const { return m_filteredEntities; }
    bool isRequired() override;

#if defined (QT_BUILD_INTERNAL)
    // For unit testing
    inline Qt3DCore::QNodeIdVector proximityFilterIds() const { return m_proximityFilterIds; }
    inline NodeManagers *manager() const { return m_manager; }
#endif

private:
    void selectAllEntities();
    void filterEntities(const std::vector<Entity *> &entitiesToFilter);

    NodeManagers *m_manager;
    Qt3DCore::QNodeIdVector m_proximityFilterIds;
    Entity *m_targetEntity;
    float m_distanceThresholdSquared;
    std::vector<Entity *> m_filteredEntities;
};

typedef QSharedPointer<FilterProximityDistanceJob> FilterProximityDistanceJobPtr;

} // Render

} // Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_FILTERPROXIMITYDISTANCEJOB_P_H
