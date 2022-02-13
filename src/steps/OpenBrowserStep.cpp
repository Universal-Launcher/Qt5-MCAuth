#include <qt_mcauth/steps/OpenBrowserStep.h>

#include <QtGui>

OpenBrowserStep::OpenBrowserStep(MCAuthData *data) : Step(data) {
  m_oauth2 = std::make_unique<QOAuth2AuthorizationCodeFlow>();
  m_reply_handler = std::make_unique<QOAuthHttpServerReplyHandler>(25560, this);

  m_oauth2->setClientIdentifier(data->clientID);

  m_oauth2->setReplyHandler(m_reply_handler.get());

  auto authorizeUrl = QUrl{"https://login.live.com/oauth20_authorize.srf"};
  QUrlQuery queries{};
  queries.addQueryItem("client_id", data->clientID);
  queries.addQueryItem("response_type", "code");
  authorizeUrl.setQuery(queries);

  m_oauth2->setScope("XboxLive.signin offline_access");
  m_oauth2->setAuthorizationUrl(authorizeUrl);
  m_oauth2->setAccessTokenUrl(QUrl{"https://login.live.com/oauth20_token.srf"});

  m_oauth2->setModifyParametersFunction(
      [&](QAbstractOAuth::Stage stage, QVariantMap *parameters) {
        if (parameters->contains("redirect_uri")) {
          parameters->remove("redirect_uri");
        }
        parameters->insert("redirect_uri", "http://localhost:25560");
      });

  connect(m_oauth2.get(), &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
          &QDesktopServices::openUrl);
  connect(m_oauth2.get(), &QOAuth2AuthorizationCodeFlow::statusChanged,
          [=](QAbstractOAuth::Status status) {
            if (status == QAbstractOAuth::Status::Granted) {
              m_data->accessToken = m_oauth2->token();
              m_data->refreshToken = m_oauth2->refreshToken();
              emit finished(StepState::Succeed,
                            tr("Microsoft account authenticated."));
            } else if (status == QAbstractOAuth::Status::NotAuthenticated) {
              emit finished(StepState::Stopped,
                            tr("Microsoft account authentication denied."));
            }
          });
}

OpenBrowserStep::~OpenBrowserStep() {}

QString OpenBrowserStep::describe() const {
  return tr("Opening Microsoft authentication page on web browser.");
}

void OpenBrowserStep::execute() { m_oauth2->grant(); }
