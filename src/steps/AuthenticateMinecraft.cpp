#include <qt_mcauth/steps/AuthenticateMinecraft.h>

AuthenticateMinecraftStep::AuthenticateMinecraftStep(MCAuthData *data)
    : Step(data) {}

AuthenticateMinecraftStep::~AuthenticateMinecraftStep() {}

QString AuthenticateMinecraftStep::describe() const {
  return tr("Authenticating Minecraft account.");
}

void AuthenticateMinecraftStep::execute() {
  QNetworkRequest http{
      QUrl{"https://api.minecraftservices.com/authentication/login_with_xbox"}};
  http.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  QJsonObject obj{
      {"identityToken",
       QString{"XBL3.0 x=%1;%2"}.arg(m_data->xui_userHash, m_data->xstsToken)}};

  QJsonDocument doc{obj};

  m_reply =
      std::unique_ptr<QNetworkReply>(m_data->nam->post(http, doc.toJson()));

  connect(m_reply.get(), &QNetworkReply::finished, this,
          &AuthenticateMinecraftStep::networkReplyFinished);
}

void AuthenticateMinecraftStep::networkReplyFinished() {
  if (m_reply->error() == QNetworkReply::NoError) {
    auto doc = QJsonDocument::fromJson(m_reply->readAll());

    m_data->mcAccessToken = doc["access_token"].toString();

    emit finished(StepState::Succeed, tr("Authenticated Minecraft account"));
  } else {
    emit finished(StepState::Failed,
                  tr("Unexpected Error: %1").arg(m_reply->errorString()));
  }
}
