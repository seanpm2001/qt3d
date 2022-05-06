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

#include <QtCore/QMetaProperty>

#include <Qt3DQuickRender/private/quick3dshaderdataarray_p.h>
#include <Qt3DQuickRender/private/quick3dshaderdata_p.h>
#include <Qt3DRender/private/qshaderdata_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
namespace Render {
namespace Quick {

namespace {

const int qjsValueTypeId = qMetaTypeId<QJSValue>();
const int quick3DShaderDataArrayTypeId = qMetaTypeId<Quick3DShaderDataArray*>();
Q_DECL_UNUSED const int quick3DShaderDataTypeId = qMetaTypeId<Quick3DShaderData*>();

}

class Quick3DShaderDataPropertyReader : public PropertyReaderInterface
{
public:
    Quick3DShaderDataPropertyReader()
    {
    }

    QVariant readProperty(const QVariant &v) override
    {
        // qjsValueTypeId are not compile time constant (no switch)
        if (v.userType() == qjsValueTypeId) {
            QJSValue jsValue = v.value<QJSValue>();
            if (jsValue.isArray())
                return v.value<QVariantList>();
            else if (jsValue.isVariant())
                return jsValue.toVariant();
        } else if (v.userType() == quick3DShaderDataArrayTypeId) {
            Quick3DShaderDataArray *array = v.value<Quick3DShaderDataArray *>();
            QVariantList innerValues;
            if (array) {
                const auto values = array->values();
                for (QShaderData *d : values) {
                    if (d)
                        innerValues.append(QVariant::fromValue(d->id()));
                }
            }
            return innerValues;
        } else if (v.canConvert<Qt3DCore::QNode*>()) {
            const auto node = v.value<Qt3DCore::QNode *>();
            const auto id = Qt3DCore::qIdForNode(node);
            return QVariant::fromValue(id);
        }
        return v;
    }
};

Quick3DShaderData::Quick3DShaderData(QNode *parent)
    : QShaderData(*new QShaderDataPrivate(PropertyReaderInterfacePtr(new Quick3DShaderDataPropertyReader()))
                  , parent)
{
}

} // namespace Quick
} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE
