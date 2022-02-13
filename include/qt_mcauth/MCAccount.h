#pragma once

#include <QString>

struct MCAccount {
  QString id() const { return m_id; }
  QString username() const { return m_username; }

private:
  QString m_id;
  QString m_username;
};
