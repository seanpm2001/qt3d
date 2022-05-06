/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

#ifndef QT3DRENDER_RENDER_OPENGL_GRAPHICSHELPERES3_2_H
#define QT3DRENDER_RENDER_OPENGL_GRAPHICSHELPERES3_2_H

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

#include <graphicshelperes3_1_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
namespace Render {
namespace OpenGL {

class GraphicsHelperES3_2 : public GraphicsHelperES3_1
{
public:
    GraphicsHelperES3_2();
    ~GraphicsHelperES3_2();

    bool supportsFeature(Feature feature) const override;

    // QGraphicHelperInterface interface
    void bindFrameBufferAttachment(QOpenGLTexture *texture, const Attachment &attachment) override;
    bool frameBufferNeedsRenderBuffer(const Attachment &attachment) override;
    void setVerticesPerPatch(GLint verticesPerPatch) override;
    void drawElementsInstancedBaseVertexBaseInstance(GLenum primitiveType, GLsizei primitiveCount, GLint indexType, void *indices, GLsizei instances, GLint baseVertex = 0,  GLint baseInstance = 0) override;
    UniformType uniformTypeFromGLType(GLenum glType) override;
    uint uniformByteSize(const ShaderUniform &description) override;

};

} // namespace OpenGL
} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_OPENGL_GRAPHICSHELPERES3_2_H
