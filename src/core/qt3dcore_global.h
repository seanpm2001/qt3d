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

#ifndef QT3DCORE_GLOBAL_H
#define QT3DCORE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <Qt3DCore/qt3dcore-config.h>

QT_BEGIN_NAMESPACE

#if defined(QT_SHARED) || !defined(QT_STATIC)
#  if defined(QT_BUILD_3DCORE_LIB)
#    define Q_3DCORESHARED_EXPORT Q_DECL_EXPORT
#  else
#    define Q_3DCORESHARED_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_3DCORESHARED_EXPORT
#endif

#define QT3D_DECLARE_TYPEINFO(NS, Class, Flags) \
    } /* NS */ \
    Q_DECLARE_TYPEINFO(NS :: Class, Flags); \
    namespace NS { \
    /*end*/

#define QT3D_DECLARE_TYPEINFO_2(OuterNS, InnerNS, Class, Flags) \
    } /* InnerNS */ \
    QT3D_DECLARE_TYPEINFO(OuterNS, InnerNS :: Class, Flags) \
    namespace InnerNS { \
    /*end*/

#define QT3D_DECLARE_TYPEINFO_3(OuterNS, InnerNS, InnerMostNS, Class, Flags) \
    } /* InnerMostNS */ \
    QT3D_DECLARE_TYPEINFO_2(OuterNS, InnerNS, InnerMostNS :: Class, Flags) \
    namespace InnerMostNS { \
    /*end*/

#define QT3D_DECLARE_SHARED(NS, Class) \
    inline void swap(Class &lhs, Class &rhs) \
        noexcept(noexcept(lhs.swap(rhs))) \
    { lhs.swap(rhs); } \
    QT3D_DECLARE_TYPEINFO(NS, Class, Q_RELOCATABLE_TYPE) \
    /*end*/

#define QT3D_DECLARE_SHARED_2(OuterNS, InnerNS, Class) \
    inline void swap(Class &lhs, Class &rhs) \
        noexcept(noexcept(lhs.swap(rhs))) \
    { lhs.swap(rhs); } \
    QT3D_DECLARE_TYPEINFO_2(OuterNS, InnerNS, Class, Q_RELOCATABLE_TYPE) \
    /*end*/

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#define QT3D_REVISION(major, minor) Q_REVISION(minor)
#define QT3D_PROPERTY_REVISION(major, minor) REVISION minor
#else
#define QT3D_REVISION(major, minor) Q_REVISION(major, minor)
#define QT3D_PROPERTY_REVISION(major, minor) REVISION(major, minor)
#endif

QT_END_NAMESPACE

#endif // QT3DCORE_GLOBAL_H
