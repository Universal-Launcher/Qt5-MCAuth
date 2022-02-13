#pragma once

#include <QObject>
#include <qt_mcauth/MCAccount.h>
#include <qt_mcauth/flows/LoginFlow.h>
#include <qt_mcauth/flows/RefreshFlow.h>
#include <qt_mcauth/globals.h>

class QT_MCAUTH_EXPORT MCAuth : public QObject {
  Q_OBJECT

public:
  MCAuth(const QString &clientID);
  virtual ~MCAuth() {}

  Flow *loginAccount();
  Flow *refreshAccount();

  MCAccount *getAccount() { return nullptr; }

private:
  QString m_clientID;
};
