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

#ifndef BEZIEREVALUATOR_P_H
#define BEZIEREVALUATOR_P_H

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

#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE

namespace Qt3DAnimation {
namespace Animation {

struct Keyframe;

class Q_AUTOTEST_EXPORT BezierEvaluator
{
public:
    explicit BezierEvaluator(float time0, const Keyframe &keyframe0,
                             float time1, const Keyframe &keyframe1)
        : m_time0(time0)
        , m_time1(time1)
        , m_keyframe0(keyframe0)
        , m_keyframe1(keyframe1)
    {
    }

    float valueForTime(float time) const;
    float parameterForTime(float time) const;

    static int findCubicRoots(const float coefficients[], float roots[3]);

private:
    float m_time0;
    float m_time1;
    const Keyframe &m_keyframe0;
    const Keyframe &m_keyframe1;
};

} // namespace Animation
} // namespace Qt3DAnimation

QT_END_NAMESPACE

#endif // BEZIEREVALUATOR_P_H
