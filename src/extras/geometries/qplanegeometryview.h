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

#ifndef QT3DEXTRAS_QPLANEGEOMETRYVIEW_H
#define QT3DEXTRAS_QPLANEGEOMETRYVIEW_H

#include <Qt3DExtras/qt3dextras_global.h>
#include <Qt3DCore/qgeometryview.h>
#include <QtCore/QSize>

QT_BEGIN_NAMESPACE

namespace Qt3DExtras {

class Q_3DEXTRASSHARED_EXPORT QPlaneGeometryView : public Qt3DCore::QGeometryView
{
    Q_OBJECT
    Q_PROPERTY(float width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(float height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QSize meshResolution READ meshResolution WRITE setMeshResolution NOTIFY meshResolutionChanged)
    Q_PROPERTY(bool mirrored READ mirrored WRITE setMirrored NOTIFY mirroredChanged REVISION 9)

public:
    explicit QPlaneGeometryView(Qt3DCore::QNode *parent = nullptr);
    ~QPlaneGeometryView();

    float width() const;
    float height() const;
    QSize meshResolution() const;
    bool mirrored() const;

public Q_SLOTS:
    void setWidth(float width);
    void setHeight(float height);
    void setMeshResolution(const QSize &resolution);
    void setMirrored(bool mirrored);

Q_SIGNALS:
    void meshResolutionChanged(const QSize &meshResolution);
    void widthChanged(float width);
    void heightChanged(float height);
    void mirroredChanged(bool mirrored);

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

#endif // QT3DEXTRAS_QPLANEGEOMETRYVIEW_H
