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

#include "qclipblendvalue.h"
#include "qclipblendvalue_p.h"
#include <Qt3DAnimation/qabstractanimationclip.h>

QT_BEGIN_NAMESPACE

namespace Qt3DAnimation {

QClipBlendValuePrivate::QClipBlendValuePrivate()
    : QAbstractClipBlendNodePrivate()
    , m_clip(nullptr)
{
}

/*!
   \class Qt3DAnimation::QClipBlendValue
   \inherits Qt3DAnimation::QAbstractClipBlendNode
   \inmodule Qt3DAnimation
   \brief Class used for including a clip in a blend tree.
*/
/*!
   \qmltype ClipBlendValue
   \instantiates Qt3DAnimation::QClipBlendValue
   \inqmlmodule Qt3D.Animation
   \brief Type used for including a clip in a blend tree.
*/
/*!
   \property Qt3DAnimation::QClipBlendValue::clip

   The animation clip that needs to be included in the blend tree.
*/
/*!
   \qmlproperty AbstractAnimationClip ClipBlendValue::clip

   The animation clip that needs to be included in the blend tree.
*/
QClipBlendValue::QClipBlendValue(Qt3DCore::QNode *parent)
    : QAbstractClipBlendNode(*new QClipBlendValuePrivate(), parent)
{
}

QClipBlendValue::QClipBlendValue(Qt3DAnimation::QAbstractAnimationClip *clip,
                                 Qt3DCore::QNode *parent)
    : QAbstractClipBlendNode(*new QClipBlendValuePrivate(), parent)
{
    setClip(clip);
}

QClipBlendValue::QClipBlendValue(QClipBlendValuePrivate &dd, Qt3DCore::QNode *parent)
    : QAbstractClipBlendNode(dd, parent)
{
}

QClipBlendValue::~QClipBlendValue()
{
}

Qt3DAnimation::QAbstractAnimationClip *QClipBlendValue::clip() const
{
    Q_D(const QClipBlendValue);
    return d->m_clip;
}

void QClipBlendValue::setClip(Qt3DAnimation::QAbstractAnimationClip *clip)
{
    Q_D(QClipBlendValue);
    if (d->m_clip == clip)
        return;

    if (d->m_clip)
        d->unregisterDestructionHelper(d->m_clip);

    if (clip && !clip->parent())
        clip->setParent(this);
    d->m_clip = clip;

    // Ensures proper bookkeeping
    if (d->m_clip)
        d->registerDestructionHelper(d->m_clip, &QClipBlendValue::setClip, d->m_clip);
    emit clipChanged(clip);
}

} // namespace Qt3DAnimation

QT_END_NAMESPACE
