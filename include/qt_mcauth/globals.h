#pragma once

#include <QObject>
#include <QtCore/qglobal.h>
#include <memory>

#if defined(QT_MCAUTH_LIBRARY)
#define QT_MCAUTH_EXPORT Q_DECL_EXPORT
#elif defined(QT_MCAUTH_LIBRARY_STATIC)
#define QT_MCAUTH_EXPORT
#else
#define QT_MCAUTH_EXPORT Q_DECL_IMPORT
#endif

/*
 * All the following code come from here and is under MultiMC licence:
 * https://github.com/MultiMC/Launcher/blob/3ca661127f2982666b962f3e345049175985efe3/launcher/QObjectPtr.h
 */

namespace details {
struct DeleteQObjectLater {
  void operator()(QObject *obj) const { obj->deleteLater(); }
};
} // namespace details

template <typename T>
using unique_qobject_ptr = std::unique_ptr<T, details::DeleteQObjectLater>;

template <typename T> class shared_qobject_ptr {
public:
  shared_qobject_ptr() {}
  shared_qobject_ptr(T *wrap) { reset(wrap); }
  shared_qobject_ptr(const shared_qobject_ptr<T> &other) {
    m_ptr = other.m_ptr;
  }
  template <typename Derived>
  shared_qobject_ptr(const shared_qobject_ptr<Derived> &other) {
    m_ptr = other.unwrap();
  }

public:
  void reset(T *wrap) {
    using namespace std::placeholders;
    m_ptr.reset(wrap, std::bind(&QObject::deleteLater, _1));
  }
  void reset(const shared_qobject_ptr<T> &other) { m_ptr = other.m_ptr; }
  void reset() { m_ptr.reset(); }
  T *get() const { return m_ptr.get(); }
  T *operator->() const { return m_ptr.get(); }
  T &operator*() const { return *m_ptr.get(); }
  operator bool() const { return m_ptr.get() != nullptr; }
  const std::shared_ptr<T> unwrap() const { return m_ptr; }
  bool operator==(const shared_qobject_ptr<T> &other) {
    return m_ptr == other.m_ptr;
  }
  bool operator!=(const shared_qobject_ptr<T> &other) {
    return m_ptr != other.m_ptr;
  }

private:
  std::shared_ptr<T> m_ptr;
};
