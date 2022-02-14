#include <qt_mcauth/steps/AuthenticateXBox.h>

AuthenticateXBoxStep::AuthenticateXBoxStep(MCAuthData *data) : Step(data) {}

AuthenticateXBoxStep::~AuthenticateXBoxStep() {}

QString AuthenticateXBoxStep::describe() const {
  return tr("Authenticating XBoxLive account.");
}

void AuthenticateXBoxStep::execute() {
  QNetworkRequest http{
      QUrl{"https://user.auth.xboxlive.com/user/authenticate"}};
  http.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  QJsonObject obj{
      {"Properties", QJsonObject{{"AuthMethod", "RPS"},
                                 {"SiteName", "user.auth.xboxlive.com"},
                                 {"RpsTicket", "d=" + m_data->accessToken}}},
      {"RelyingParty", "http://auth.xboxlive.com"},
      {"TokenType", "JWT"}};

  QJsonDocument doc{obj};

  m_reply =
      unique_qobject_ptr<QNetworkReply>(m_data->nam->post(http, doc.toJson()));

  connect(m_reply.get(), &QNetworkReply::finished, this,
          &AuthenticateXBoxStep::networkReplyFinished);
}

void AuthenticateXBoxStep::networkReplyFinished() {
  if (m_reply->error() == QNetworkReply::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(m_reply->readAll());
    QJsonArray arr = doc["DisplayClaims"]["xui"].toArray();

    if (arr.size() > 0) {
      m_data->xui_userHash = arr.first()["uhs"].toString();
      m_data->xblToken = doc["Token"].toString();
      emit finished(StepState::Succeed, tr("XBoxLive account authenticated"));
    } else {
      emit finished(StepState::Failed,
                    tr("No claims found, user not authenticated."));
    }
  } else {
    emit finished(StepState::Failed,
                  tr("Unexpected Error: %1").arg(m_reply->errorString()));
  }
}
