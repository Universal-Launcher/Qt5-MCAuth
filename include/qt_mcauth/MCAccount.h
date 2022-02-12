#pragma once

#include <QString>

namespace QtMCAuth {

struct MCAccount {
  QString username() const { return m_username; }

private:
  QString m_username;
};

}; // namespace QtMCAuth
