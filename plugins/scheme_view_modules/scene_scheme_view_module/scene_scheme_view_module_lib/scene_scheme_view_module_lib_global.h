#ifndef SCENE_SCHEME_VIEW_MODULE_LIB_GLOBAL_H
#define SCENE_SCHEME_VIEW_MODULE_LIB_GLOBAL_H

#include <QtCore/qglobal.h>
#include <memory>

#if defined(SCENE_SCHEME_VIEW_MODULE_LIB_LIBRARY)
#  define SCENE_SCHEME_VIEW_MODULE_LIB_EXPORT Q_DECL_EXPORT
#else
#  define SCENE_SCHEME_VIEW_MODULE_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // SCENE_SCHEME_VIEW_MODULE_LIB_GLOBAL_H