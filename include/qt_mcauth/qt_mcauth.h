#pragma once

#include <QObject>
#include <qt_mcauth/MCAccount.h>
#include <qt_mcauth/auth_data.h>
#include <qt_mcauth/flows/LoginFlow.h>
#include <qt_mcauth/flows/RefreshFlow.h>
#include <qt_mcauth/globals.h>

class QT_MCAUTH_EXPORT MCAuth : public QObject {
  Q_OBJECT

public:
  MCAuth(const QString &clientID);
  virtual ~MCAuth() {}

  LoginFlow *loginAccount();
  RefreshFlow *refreshAccount();

  std::optional<MCAccount> &getAccount() { return m_data->mcAccount; }

private:
  QString m_clientID;
  std::unique_ptr<MCAuthData> m_data;
};
