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

#include "quick3dentity_p.h"

#include <Qt3DCore/qcomponent.h>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {
namespace Quick {

/*!
    \qmltype Entity
    \instantiates Qt3DCore::QEntity
    \inherits Node
    \inqmlmodule Qt3D.Core
    \since 5.5

    \brief Entity is a \l Node subclass that can aggregate several
    \l Component3D instances that will specify its behavior.

    By itself a Entity is an empty shell. The behavior of a Entity
    object is defined by the \l Component3D objects it references. Each Qt3D
    backend aspect will be able to interpret and process an Entity by
    recognizing which components it is made up of. One aspect may decide to only
    process entities composed of a single \l Transform component whilst
    another may focus on \l MouseHandler.

    \sa Qt3D.Core::Component3D, Qt3D.Core::Transform
 */

/*!
    \qmlproperty list<Component3D> Entity::components
    Holds the list of \l Component3D instances, which define the behavior
    of the entity.
    \readonly
 */

Quick3DEntity::Quick3DEntity(QObject *parent)
    : QObject(parent)
{
}


QQmlListProperty<QComponent> Quick3DEntity::componentList()
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    using qt_size_type = qsizetype;
#else
    using qt_size_type = int;
#endif

    using ListContentType = Qt3DCore::QComponent;
    auto appendFunction = [](QQmlListProperty<ListContentType> *list, ListContentType *comp) {
        if (comp == nullptr)
            return;
        Quick3DEntity *self = static_cast<Quick3DEntity *>(list->object);
        self->m_managedComponents.push_back(comp);
        self->parentEntity()->addComponent(comp);
    };
    auto countFunction = [](QQmlListProperty<ListContentType> *list) -> qt_size_type {
        Quick3DEntity *self = static_cast<Quick3DEntity *>(list->object);
        return self->parentEntity()->components().count();
    };
    auto atFunction = [](QQmlListProperty<ListContentType> *list, qt_size_type index) -> ListContentType * {
        Quick3DEntity *self = static_cast<Quick3DEntity *>(list->object);
        return self->parentEntity()->components().at(index);
    };
    auto clearFunction = [](QQmlListProperty<ListContentType> *list) {
        Quick3DEntity *self = static_cast<Quick3DEntity *>(list->object);
        for (QComponent *comp : qAsConst(self->m_managedComponents))
            self->parentEntity()->removeComponent(comp);
        self->m_managedComponents.clear();
    };

    return QQmlListProperty<ListContentType>(this, nullptr, appendFunction, countFunction, atFunction, clearFunction);
}


} // namespace Quick
} // namespace Qt3DCore

QT_END_NAMESPACE
