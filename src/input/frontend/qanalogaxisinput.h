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

#ifndef QT3DINPUT_QANALOGAXISINPUT_H
#define QT3DINPUT_QANALOGAXISINPUT_H

#include <Qt3DInput/qt3dinput_global.h>
#include <Qt3DInput/QAbstractAxisInput>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {

class QAnalogAxisInputPrivate;

class Q_3DINPUTSHARED_EXPORT QAnalogAxisInput : public QAbstractAxisInput
{
    Q_OBJECT
    Q_PROPERTY(int axis READ axis WRITE setAxis NOTIFY axisChanged)

public:
    explicit QAnalogAxisInput(Qt3DCore::QNode *parent = nullptr);
    ~QAnalogAxisInput();

    int axis() const;

public Q_SLOTS:
    void setAxis(int axis);

Q_SIGNALS:
    void axisChanged(int axis);

private:
    Q_DECLARE_PRIVATE(QAnalogAxisInput)
};

} // Qt3DInput

QT_END_NAMESPACE

#endif // QT3DINPUT_QANALOGAXISINPUT_H
