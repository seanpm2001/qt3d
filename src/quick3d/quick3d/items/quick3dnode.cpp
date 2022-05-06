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

#include "quick3dnode_p.h"

#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {
namespace Quick {

/*!
    \qmltype Node
    \inqmlmodule Qt3D.Core
    \since 5.5

    \brief A base QML type that other types inherit. It cannot be directly
    created.
*/

Quick3DNode::Quick3DNode(QObject *parent)
    : QObject(parent)
{
}

/*!
    \qmlproperty list<QtQml::QtObject> Qt3DCore::Node::data
    \qmldefault
*/

QQmlListProperty<QObject> Quick3DNode::data()
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    using qt_size_type = qsizetype;
#else
    using qt_size_type = int;
#endif

    using ListContentType = QObject;
    auto appendFunction = [](QQmlListProperty<ListContentType> *list, ListContentType *obj) {
        if (!obj)
            return;

        Quick3DNode *self = static_cast<Quick3DNode *>(list->object);
        self->childAppended(0, obj);
    };
    auto countFunction = [](QQmlListProperty<ListContentType> *list) -> qt_size_type {
        Quick3DNode *self = static_cast<Quick3DNode *>(list->object);
        return self->parentNode()->children().count();
    };
    auto atFunction = [](QQmlListProperty<ListContentType> *list, qt_size_type index) -> ListContentType * {
        Quick3DNode *self = static_cast<Quick3DNode *>(list->object);
        return self->parentNode()->children().at(index);
    };
    auto clearFunction = [](QQmlListProperty<ListContentType> *list) {
        Quick3DNode *self = static_cast<Quick3DNode *>(list->object);
        for (QObject *const child : self->parentNode()->children())
            self->childRemoved(0, child);
    };

    return QQmlListProperty<ListContentType>(this, nullptr, appendFunction, countFunction, atFunction, clearFunction);
}

/*!
    \qmlproperty list<Node> Qt3DCore::Node::childNodes
    \readonly
*/

QQmlListProperty<QNode> Quick3DNode::childNodes()
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    using qt_size_type = qsizetype;
#else
    using qt_size_type = int;
#endif

    using ListContentType = QNode;
    auto appendFunction = [](QQmlListProperty<ListContentType> *list, ListContentType *obj) {
        if (!obj)
            return;

        Quick3DNode *self = static_cast<Quick3DNode *>(list->object);
        Q_ASSERT(!self->parentNode()->children().contains(obj));

        self->childAppended(0, obj);
    };
    auto countFunction = [](QQmlListProperty<ListContentType> *list) -> qt_size_type {
        Quick3DNode *self = static_cast<Quick3DNode *>(list->object);
        return self->parentNode()->children().count();
    };
    auto atFunction = [](QQmlListProperty<ListContentType> *list, qt_size_type index) -> ListContentType * {
        Quick3DNode *self = static_cast<Quick3DNode *>(list->object);
        return qobject_cast<QNode *>(self->parentNode()->children().at(index));
    };
    auto clearFunction = [](QQmlListProperty<ListContentType> *list) {
        Quick3DNode *self = static_cast<Quick3DNode *>(list->object);
        for (QObject *const child : self->parentNode()->children())
            self->childRemoved(0, child);
    };

    return QQmlListProperty<ListContentType>(this, nullptr, appendFunction, countFunction, atFunction, clearFunction);
}

void Quick3DNode::childAppended(int, QObject *obj)
{
    QNode *parentNode = this->parentNode();
    if (obj->parent() == parentNode)
        obj->setParent(nullptr);
    // Set after otherwise addChild might not work
    if (QNode *n = qobject_cast<QNode *>(obj))
        n->setParent(parentNode);
    else
        obj->setParent(parentNode);
}

void Quick3DNode::childRemoved(int, QObject *obj)
{
    if (QNode *n = qobject_cast<QNode *>(obj))
        n->setParent(Q_NODE_NULLPTR);
    else
        obj->setParent(nullptr);
}

} // namespace Quick
} // namespace Qt3DCore

QT_END_NAMESPACE
