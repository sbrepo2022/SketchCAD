#ifndef POINT_PRIMITIVE_LIB_GLOBAL_H
#define POINT_PRIMITIVE_LIB_GLOBAL_H

#include <QtCore/qglobal.h>
#include <memory>

#if defined(POINT_PRIMITIVE_LIB_LIBRARY)
#  define POINT_PRIMITIVE_LIB_EXPORT Q_DECL_EXPORT
#else
#  define POINT_PRIMITIVE_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // POINT_PRIMITIVE_LIB_GLOBAL_H
