#pragma once

#include "MCAccount.h"
#include "flows/LoginFlow.h"
#include "flows/RefreshFlow.h"
#include <QObject>

namespace QtMCAuth {

class QtMCAuth : public QObject {
  Q_OBJECT

public:
  QtMCAuth(const QString &clientID);
  ~QtMCAuth();

  LoginFlow *loginAccount();
  RefreshFlow *refreshAccount();

  MCAccount *getAccount() { return nullptr; }

private:
  QString m_clientID;
};

} // namespace QtMCAuth
