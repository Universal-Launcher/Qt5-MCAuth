#pragma once

#include <qt_mcauth/globals.h>
#include <qt_mcauth/steps/Step.h>

#include <QOAuth2AuthorizationCodeFlow>
#include <QtNetwork>
#include <QtNetworkAuth>

class QT_MCAUTH_EXPORT OpenBrowserStep : public Step {
  Q_OBJECT

public:
  OpenBrowserStep(MCAuthData *data);
  ~OpenBrowserStep();

  QString describe() const;

public slots:
  void execute();

private:
  unique_qobject_ptr<QOAuth2AuthorizationCodeFlow> m_oauth2;
  unique_qobject_ptr<QOAuthHttpServerReplyHandler> m_reply_handler;
};
