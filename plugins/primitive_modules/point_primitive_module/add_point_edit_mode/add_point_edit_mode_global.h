#ifndef ADD_POINT_EDIT_MODE_GLOBAL_H
#define ADD_POINT_EDIT_MODE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ADD_POINT_EDIT_MODE_LIBRARY)
#  define ADD_POINT_EDIT_MODE_EXPORT Q_DECL_EXPORT
#else
#  define ADD_POINT_EDIT_MODE_EXPORT Q_DECL_IMPORT
#endif

#endif // ADD_POINT_EDIT_MODE_GLOBAL_H
