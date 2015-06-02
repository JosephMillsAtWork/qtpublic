#ifndef MLITE_GLOBAL_H
#define MLITE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MLITE_LIBRARY)
#  define MLITESHARED_EXPORT Q_DECL_EXPORT
#else
#  define MLITESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MLITE_GLOBAL_H
