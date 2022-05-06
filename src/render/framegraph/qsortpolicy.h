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

#ifndef QT3DRENDER_QSORTPOLICY_H
#define QT3DRENDER_QSORTPOLICY_H

#include <Qt3DRender/qframegraphnode.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

class QSortPolicyPrivate;

class Q_3DRENDERSHARED_EXPORT QSortPolicy : public QFrameGraphNode
{
    Q_OBJECT
    Q_PROPERTY(QList<int> sortTypes READ sortTypesInt WRITE setSortTypes NOTIFY sortTypesChanged)
public:
    explicit QSortPolicy(Qt3DCore::QNode *parent = nullptr);
    ~QSortPolicy();

    enum SortType {
        StateChangeCost = (1 << 0),
        BackToFront = (1 << 1),
        Material = (1 << 2),
        FrontToBack = (1 << 3),
        Texture = (1 << 4),
        Uniform = (1 << 5)
    };
    Q_ENUM(SortType) // LCOV_EXCL_LINE

    QList<SortType> sortTypes() const;
    QList<int> sortTypesInt() const;

public Q_SLOTS:
    void setSortTypes(const QList<SortType> &sortTypes);
    void setSortTypes(const QList<int> &sortTypesInt);

Q_SIGNALS:
    void sortTypesChanged(const QList<SortType> &sortTypes);
    void sortTypesChanged(const QList<int> &sortTypes);

protected:
    explicit QSortPolicy(QSortPolicyPrivate &dd, Qt3DCore::QNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QSortPolicy)
};

} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_QSORTPOLICY_H
