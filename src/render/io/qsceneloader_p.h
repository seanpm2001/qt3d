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

#ifndef QT3DRENDER_QSCENELOADER_P_H
#define QT3DRENDER_QSCENELOADER_P_H

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

#include <private/qcomponent_p.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/private/qt3drender_global_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

class QSceneImporter;

class Q_3DRENDERSHARED_PRIVATE_EXPORT QSceneLoaderPrivate : public Qt3DCore::QComponentPrivate
{
public:
    QSceneLoaderPrivate();

    void setStatus(QSceneLoader::Status status);
    void setSceneRoot(Qt3DCore::QEntity *root);

    Q_DECLARE_PUBLIC(QSceneLoader)

    void populateEntityMap(Qt3DCore::QEntity *parentEntity);

    QUrl m_source;
    QSceneLoader::Status m_status;
    Qt3DCore::QEntity *m_subTreeRoot;
    QHash<QString, Qt3DCore::QEntity *> m_entityMap;
};

} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_QSCENELOADER_P_H
