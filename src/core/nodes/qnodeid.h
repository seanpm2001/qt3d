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

#ifndef QT3DCORE_QNODEID_H
#define QT3DCORE_QNODEID_H

#include <Qt3DCore/qt3dcore_global.h>
#include <QtCore/QDebug>
#include <QtCore/QHashFunctions>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {

class QNodeId
{
    constexpr explicit QNodeId(quint64 i) noexcept
        : m_id(i)
    {}
public:
    constexpr QNodeId() noexcept
        : m_id(0)
    {}

    Q_3DCORESHARED_EXPORT static QNodeId createId() noexcept;

    constexpr bool isNull() const noexcept
    {
        return m_id == 0;
    }

    constexpr bool operator ==(QNodeId other) const noexcept
    {
        return other.m_id == m_id;
    }

    constexpr bool operator !=(QNodeId other) const noexcept
    {
        return !operator ==(other);
    }

    constexpr bool operator <(QNodeId other) const noexcept
    {
        return m_id < other.m_id;
    }

    constexpr bool operator >(QNodeId other) const noexcept
    {
        return m_id > other.m_id;
    }

    constexpr quint64 id() const noexcept
    {
        return m_id;
    }

    constexpr operator bool() const noexcept
    {
        return m_id != 0;
    }

private:
    quint64 m_id;
};
QT3D_DECLARE_TYPEINFO(Qt3DCore, QNodeId, Q_PRIMITIVE_TYPE)

using QNodeIdVector = QList<QNodeId>;

#ifndef QT_NO_DEBUG_STREAM
Q_3DCORESHARED_EXPORT QDebug operator<<(QDebug d, QNodeId id);
#endif

//! [nodeid-qhash]
inline constexpr size_t qHash(QNodeId id, size_t seed = 0) noexcept
{
    using QT_PREPEND_NAMESPACE(qHash);
    return qHash(id.id(), seed);
}

} // Qt3DCore

QT_END_NAMESPACE

Q_DECLARE_METATYPE(Qt3DCore::QNodeId) // LCOV_EXCL_LINE


#endif // QT3DCORE_QNODEID_H
