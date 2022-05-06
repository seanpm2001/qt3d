/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Copyright (C) 2022 The Qt Company Ltd and/or its subsidiary(-ies).
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

/*!
 * \class Qt3DRender::QBlendEquation
 * \inheaderfile Qt3DRender/QBlendEquation
 * \brief The QBlendEquation class specifies the equation used for both the RGB
 *  blend equation and the Alpha blend equation.
 * \inmodule Qt3DRender
 * \since 5.7
 * \ingroup renderstates
 *
 * The blend equation is used to determine how a new pixel is combined with a pixel
 * already in the framebuffer.
 */

/*!
    \qmltype BlendEquation
    \instantiates Qt3DRender::QBlendEquation
    \inherits RenderState
    \inqmlmodule Qt3D.Render
    \since 5.5
    \brief The BlendEquation class specifies the equation used for both the RGB
     blend equation and the Alpha blend equation.

    The blend equation is used to determine how a new pixel is combined with a pixel
    already in the framebuffer.
*/

#include "qblendequation.h"
#include "qblendequation_p.h"

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

/*!
 * The constructor creates a new blend state object with the specified \a parent.
 */
QBlendEquation::QBlendEquation(QNode *parent)
    : QRenderState(*new QBlendEquationPrivate, parent)
{
}

/*! \internal */
QBlendEquation::~QBlendEquation()
{
}

/*!
  \enum Qt3DRender::QBlendEquation::BlendFunction

  \value Add GL_FUNC_ADD
  \value Subtract GL_FUNC_SUBTRACT
  \value ReverseSubtract GL_FUNC_REVERSE_SUBTRACT
  \value Min GL_MIN
  \value Max GL_MAX
*/

/*!
    \qmlproperty enumeration BlendEquation::blendFunction

    Holds the blend function, which determines how source and destination colors are combined.
 */

/*!
    \property QBlendEquation::blendFunction

    Holds the blend function, which determines how source and destination colors are combined.
 */

QBlendEquation::BlendFunction QBlendEquation::blendFunction() const
{
    Q_D(const QBlendEquation);
    return d->m_blendFunction;
}

void QBlendEquation::setBlendFunction(QBlendEquation::BlendFunction blendFunction)
{
    Q_D(QBlendEquation);
    if (d->m_blendFunction != blendFunction) {
        d->m_blendFunction = blendFunction;
        emit blendFunctionChanged(blendFunction);
    }
}

} // namespace Qt3DRender

QT_END_NAMESPACE
