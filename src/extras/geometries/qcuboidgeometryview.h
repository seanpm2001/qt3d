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

#ifndef QT3DEXTRAS_CUBOIDGEOMETRYVIEW_H
#define QT3DEXTRAS_CUBOIDGEOMETRYVIEW_H

#include <Qt3DExtras/qt3dextras_global.h>
#include <Qt3DCore/qgeometryview.h>
#include <QtCore/QSize>

QT_BEGIN_NAMESPACE

namespace Qt3DExtras {

class Q_3DEXTRASSHARED_EXPORT QCuboidGeometryView : public Qt3DCore::QGeometryView
{
    Q_OBJECT

    Q_PROPERTY(float xExtent READ xExtent WRITE setXExtent NOTIFY xExtentChanged)
    Q_PROPERTY(float yExtent READ yExtent WRITE setYExtent NOTIFY yExtentChanged)
    Q_PROPERTY(float zExtent READ zExtent WRITE setZExtent NOTIFY zExtentChanged)
    Q_PROPERTY(QSize yzMeshResolution READ yzMeshResolution WRITE setYZMeshResolution NOTIFY yzMeshResolutionChanged)
    Q_PROPERTY(QSize xzMeshResolution READ xzMeshResolution WRITE setXZMeshResolution NOTIFY xzMeshResolutionChanged)
    Q_PROPERTY(QSize xyMeshResolution READ xyMeshResolution WRITE setXYMeshResolution NOTIFY xyMeshResolutionChanged)

public:
    explicit QCuboidGeometryView(Qt3DCore::QNode *parent = nullptr);
    ~QCuboidGeometryView();

    float xExtent() const;
    float yExtent() const;
    float zExtent() const;
    QSize yzMeshResolution() const;
    QSize xzMeshResolution() const;
    QSize xyMeshResolution() const;

public Q_SLOTS:
    void setXExtent(float xExtent);
    void setYExtent(float yExtent);
    void setZExtent(float zExtent);
    void setYZMeshResolution(const QSize &resolution);
    void setXZMeshResolution(const QSize &resolution);
    void setXYMeshResolution(const QSize &resolution);

Q_SIGNALS:
    void xExtentChanged(float xExtent);
    void yExtentChanged(float yExtent);
    void zExtentChanged(float zExtent);

    void yzMeshResolutionChanged(const QSize &yzMeshResolution);
    void xzMeshResolutionChanged(const QSize &xzMeshResolution);
    void xyMeshResolutionChanged(const QSize &xyMeshResolution);

private:
    // As this is a default provided geometry renderer, no one should be able
    // to modify the QGeometryRenderer's properties

    void setInstanceCount(int instanceCount);
    void setVertexCount(int vertexCount);
    void setIndexOffset(int indexOffset);
    void setFirstInstance(int firstInstance);
    void setRestartIndexValue(int index);
    void setPrimitiveRestartEnabled(bool enabled);
    void setGeometry(Qt3DCore::QGeometry *geometry);
    void setPrimitiveType(PrimitiveType primitiveType);
};

} // namespace Qt3DExtras

QT_END_NAMESPACE

#endif // QT3DEXTRAS_CUBOIDGEOMETRYVIEW_H
