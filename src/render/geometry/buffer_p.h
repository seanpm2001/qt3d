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

#ifndef QT3DRENDER_RENDER_BUFFER_H
#define QT3DRENDER_RENDER_BUFFER_H

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

#include <QtCore>
#include <Qt3DRender/private/backendnode_p.h>
#include <Qt3DCore/qbuffer.h>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {
    struct QBufferUpdate;
}

namespace Qt3DRender {
namespace Render {

class BufferManager;

class Q_3DRENDERSHARED_PRIVATE_EXPORT Buffer : public BackendNode
{
public:
    Buffer();
    ~Buffer();
    void cleanup();

    void syncFromFrontEnd(const Qt3DCore::QNode *frontEnd, bool firstTime) override;

    void setManager(BufferManager *manager);
    void updateDataFromGPUToCPU(QByteArray data);
    inline Qt3DCore::QBuffer::UsageType usage() const { return m_usage; }
    inline QByteArray data() const { return m_data; }
    inline std::vector<Qt3DCore::QBufferUpdate> &pendingBufferUpdates() { return m_bufferUpdates; }
    inline bool isDirty() const { return m_bufferDirty; }
    inline Qt3DCore::QBuffer::AccessType access() const { return m_access; }
    void unsetDirty();

private:
    void forceDataUpload();

    Qt3DCore::QBuffer::UsageType m_usage;
    QByteArray m_data;
    std::vector<Qt3DCore::QBufferUpdate> m_bufferUpdates;
    bool m_bufferDirty;
    Qt3DCore::QBuffer::AccessType m_access;
    BufferManager *m_manager;
};

class BufferFunctor : public Qt3DCore::QBackendNodeMapper
{
public:
    explicit BufferFunctor(AbstractRenderer *renderer, BufferManager *manager);
    Qt3DCore::QBackendNode *create(Qt3DCore::QNodeId id) const override;
    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const override;
    void destroy(Qt3DCore::QNodeId id) const override;
private:
    BufferManager *m_manager;
    AbstractRenderer *m_renderer;
};

} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_BUFFER_H
