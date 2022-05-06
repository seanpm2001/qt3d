/****************************************************************************
**
** Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
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

#ifndef QT3DANIMATION_ANIMATION_FCURVE_P_H
#define QT3DANIMATION_ANIMATION_FCURVE_P_H

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

#include "keyframe_p.h"
#include "functionrangefinder_p.h"

#include <Qt3DAnimation/qchannel.h>
#include <Qt3DAnimation/qchannelcomponent.h>
#include <Qt3DAnimation/qkeyframe.h>
#include <QtCore/qlist.h>

#ifndef QT_NO_DEBUG_STREAM
#include <QtCore/qdebug.h>
#endif

QT_BEGIN_NAMESPACE

namespace Qt3DAnimation {
namespace Animation {

class Q_AUTOTEST_EXPORT FCurve
{
public:
    FCurve();

    int keyframeCount() const { return m_localTimes.size(); }
    void appendKeyframe(float localTime, const Keyframe &keyframe);
    void clearKeyframes() { m_localTimes.clear(); m_keyframes.clear(); }

    const float &localTime(int index) const { return m_localTimes[index]; }
    float &localTime(int index) { return m_localTimes[index]; }
    const Keyframe &keyframe(int index) const { return m_keyframes[index]; }
    Keyframe &keyframe(int index) { return m_keyframes[index]; }

    float startTime() const;
    float endTime() const;

    float evaluateAtTime(float localTime) const;
    float evaluateAtTime(float localTime, int lowerBound) const;
    float evaluateAtTimeAsSlerp(float localTime, int lowerBound, float halfTheta, float sinHalfTheta, float reverseQ1) const;
    int lowerKeyframeBound(float localTime) const;

    void read(const QJsonObject &json);
    void setFromQChannelComponent(const QChannelComponent &qcc);

private:
    QList<float> m_localTimes;
    QList<Keyframe> m_keyframes;

    FunctionRangeFinder m_rangeFinder;
};

#ifndef QT_NO_DEBUG_STREAM
inline QDebug operator<<(QDebug dbg, const FCurve &fcurve)
{
    QDebugStateSaver saver(dbg);
    dbg << "Keyframe Count = " << fcurve.keyframeCount() << Qt::endl;
    for (int i = 0; i < fcurve.keyframeCount(); ++i) {
        const Keyframe &kf = fcurve.keyframe(i);
        switch (kf.interpolation) {
        case QKeyFrame::BezierInterpolation: {
            dbg << "t = " << fcurve.localTime(i)
                << ", value = " << kf.value
                << ", leftHandle = " << kf.leftControlPoint
                << ", rightHandle = " << kf.rightControlPoint
                << Qt::endl;
            break;
        }
        case QKeyFrame::ConstantInterpolation:
        case QKeyFrame::LinearInterpolation: {
            dbg << "t = " << fcurve.localTime(i)
                << ", value = " << kf.value
                << Qt::endl;
            break;
        }
        }
    }
    return dbg;
}
#endif

struct ChannelComponent
{
    QString name;
    FCurve fcurve;

    void read(const QJsonObject &json);
    void setFromQChannelComponent(const QChannelComponent &qcc);
};

#ifndef QT_NO_DEBUG_STREAM
inline QDebug operator<<(QDebug dbg, const ChannelComponent &channelComponent)
{
    QDebugStateSaver saver(dbg);
    dbg << "Channel Component Name: " << channelComponent.name << Qt::endl
        << "FCurve:" << channelComponent.fcurve << Qt::endl;
    return dbg;
}
#endif

struct Channel
{
    QString name;
    int jointIndex = -1;
    QVector<ChannelComponent> channelComponents;

    void read(const QJsonObject &json);
    void setFromQChannel(const QChannel &qch);
};

#ifndef QT_NO_DEBUG_STREAM
inline QDebug operator<<(QDebug dbg, const Channel &channel)
{
    QDebugStateSaver saver(dbg);
    dbg << "Channel Name: " << channel.name << Qt::endl
        << "Channels:" << channel.channelComponents.size() << Qt::endl;

    for (const auto &channelComponent : qAsConst(channel.channelComponents)) {
        dbg << channelComponent;
    }
    return dbg;
}
#endif

} // namespace Animation
} // namespace Qt3DAnimation

QT_END_NAMESPACE

#endif // QT3DANIMATION_ANIMATION_FCURVE_P_H
