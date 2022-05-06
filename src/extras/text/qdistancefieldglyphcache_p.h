/****************************************************************************
**
** Copyright (C) 2016 Klaralvdalens Datakonsult AB (KDAB).
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

#ifndef QT3DEXTRAS_QDISTANCEFIELDGLYPHCACHE_P_H
#define QT3DEXTRAS_QDISTANCEFIELDGLYPHCACHE_P_H

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

#include <QtCore/QRectF>
#include <Qt3DCore/qnode.h>
#include <Qt3DExtras/qt3dextras_global.h>

QT_BEGIN_NAMESPACE

class QRawFont;
class QGlyphRun;

namespace Qt3DCore {
class QNode;
}

namespace Qt3DRender {
class QAbstractTexture;
}

namespace Qt3DExtras {

class DistanceFieldFont;
class QDistanceFieldGlyphCachePrivate;

class QDistanceFieldGlyphCache
{
public:
    QDistanceFieldGlyphCache();
    ~QDistanceFieldGlyphCache();

    void setRootNode(Qt3DCore::QNode *rootNode);
    Qt3DCore::QNode *rootNode() const;

    struct Glyph {
        Qt3DRender::QAbstractTexture *texture = nullptr;
        QRectF glyphPathBoundingRect;   // bounding rect of the QPainterPath used to draw the glyph
        QRectF texCoords;               // texture coordinates within texture
    };

    bool doubleGlyphResolution(const QRawFont &font);

    QList<Glyph> refGlyphs(const QGlyphRun &run);
    Glyph refGlyph(const QRawFont &font, quint32 glyph);

    void derefGlyphs(const QGlyphRun &run);
    void derefGlyph(const QRawFont &font, quint32 glyph);

private:
    DistanceFieldFont* getOrCreateDistanceFieldFont(const QRawFont &font);
    static QString fontKey(const QRawFont &font);

    QHash<QString, DistanceFieldFont*> m_fonts;
    Qt3DCore::QNode *m_rootNode;
};

} // namespace Qt3DExtras

QT_END_NAMESPACE

#endif // QT3DEXTRAS_QDISTANCEFIELDGLYPHCACHE_P_H
