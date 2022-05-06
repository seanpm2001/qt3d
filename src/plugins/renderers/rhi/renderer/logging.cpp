/****************************************************************************
**
** Copyright (C) 2020 Klaralvdalens Datakonsult AB (KDAB).
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

#include "logging_p.h"

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

namespace Render {

namespace Rhi {

Q_LOGGING_CATEGORY(Backend, "Qt3D.Renderer.RHI.Backend", QtWarningMsg)
Q_LOGGING_CATEGORY(Frontend, "Qt3D.Renderer.RHI.Frontend", QtWarningMsg)
Q_LOGGING_CATEGORY(Io, "Qt3D.Renderer.RHI.IO", QtWarningMsg)
Q_LOGGING_CATEGORY(Jobs, "Qt3D.Renderer.RHI.Jobs", QtWarningMsg)
Q_LOGGING_CATEGORY(SceneLoaders, "Qt3D.Renderer.RHI.SceneLoaders", QtWarningMsg)
Q_LOGGING_CATEGORY(Framegraph, "Qt3D.Renderer.RHI.Framegraph", QtWarningMsg)
Q_LOGGING_CATEGORY(RenderNodes, "Qt3D.Renderer.RHI.RenderNodes", QtWarningMsg)
Q_LOGGING_CATEGORY(Rendering, "Qt3D.Renderer.RHI.Rendering", QtWarningMsg)
Q_LOGGING_CATEGORY(Memory, "Qt3D.Renderer.RHI.Memory", QtWarningMsg)
Q_LOGGING_CATEGORY(Shaders, "Qt3D.Renderer.RHI.Shaders", QtWarningMsg)
Q_LOGGING_CATEGORY(RenderStates, "Qt3D.Renderer.RHI.RenderStates", QtWarningMsg)
Q_LOGGING_CATEGORY(VSyncAdvanceService, "Qt3D.Renderer.RHI.VsyncAdvanceService", QtWarningMsg)

} // namespace Rhi

} // namespace Render

} // namespace Qt3DRender

QT_END_NAMESPACE
