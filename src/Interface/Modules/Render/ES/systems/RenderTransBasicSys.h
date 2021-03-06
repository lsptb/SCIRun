#ifndef INTERFACE_MODULES_RENDER_ES_SYSTEMS_RENDER_BASIC_SYS_TRANS_H
#define INTERFACE_MODULES_RENDER_ES_SYSTEMS_RENDER_BASIC_SYS_TRANS_H

#include <es-acorn/Acorn.hpp>

namespace SCIRun {
namespace Render {

void        registerSystem_RenderBasicTransGeom(CPM_ES_ACORN_NS::Acorn& core);
const char* getSystemName_RenderBasicTransGeom();

} // namespace Render
} // namespace SCIRun

#endif
