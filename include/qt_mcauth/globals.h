#pragma once

#include <QtCore/qglobal.h>

#if defined(QT_MCAUTH_LIBRARY)
#define QT_MCAUTH_EXPORT Q_DECL_EXPORT
#elif defined(QT_MCAUTH_LIBRARY_STATIC)
#define QT_MCAUTH_EXPORT
#else
#define QT_MCAUTH_EXPORT Q_DECL_IMPORT
#endif
