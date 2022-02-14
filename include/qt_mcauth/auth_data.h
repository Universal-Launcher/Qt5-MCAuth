#pragma once

#include <QString>
#include <QtNetwork>
#include <memory>
#include <optional>
#include <qt_mcauth/MCAccount.h>
#include <qt_mcauth/globals.h>

struct MCAuthData {
  // App information
  QString clientID;
  // Used for requests
  unique_qobject_ptr<QNetworkAccessManager> nam;

  // Auth tokens
  QString accessToken;
  QString refreshToken;

  QString xui_userHash;
  QString xblToken;
  QString xstsToken;

  QString mcAccessToken;

  std::optional<MCAccount> mcAccount;
};
