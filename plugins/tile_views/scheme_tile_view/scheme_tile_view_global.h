#ifndef SCHEME_TILE_VIEW_GLOBAL_H
#define SCHEME_TILE_VIEW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SCHEMETILEVIEW_LIBRARY)
#  define SCHEMETILEVIEW_EXPORT Q_DECL_EXPORT
#else
#  define SCHEMETILEVIEW_EXPORT Q_DECL_IMPORT
#endif

#endif // SCHEME_TILE_VIEW_GLOBAL_H
