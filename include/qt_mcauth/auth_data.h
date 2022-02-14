#pragma once

#include <QString>
#include <QtNetwork>
#include <memory>

struct MCAuthData {
  // App information
  QString clientID;
  // Used for requests
  std::unique_ptr<QNetworkAccessManager> nam;

  // Auth tokens
  QString accessToken;
  QString refreshToken;

  QString xui_userHash;
  QString xblToken;
  QString xstsToken;
};
