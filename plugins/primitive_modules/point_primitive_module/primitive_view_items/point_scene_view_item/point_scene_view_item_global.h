#ifndef POINT_SCENE_VIEW_ITEM_GLOBAL_H
#define POINT_SCENE_VIEW_ITEM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(POINT_SCENE_VIEW_ITEM_LIBRARY)
#  define POINT_SCENE_VIEW_ITEM_EXPORT Q_DECL_EXPORT
#else
#  define POINT_SCENE_VIEW_ITEM_EXPORT Q_DECL_IMPORT
#endif

#endif // POINT_SCENE_VIEW_ITEM_GLOBAL_H
