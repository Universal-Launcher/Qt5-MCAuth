#include <qt_mcauth/steps/AuthenticateXSTS.h>

AuthenticateXSTSStep::AuthenticateXSTSStep(MCAuthData *data) : Step(data) {}

AuthenticateXSTSStep::~AuthenticateXSTSStep() {}

QString AuthenticateXSTSStep::describe() const {
  return tr("Authenticating XSTS account.");
}

void AuthenticateXSTSStep::execute() {
  QNetworkRequest http{QUrl{"https://xsts.auth.xboxlive.com/xsts/authorize"}};
  http.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  QJsonObject obj{
      {"Properties", QJsonObject{{"SandboxId", "RETAIL"},
                                 {"UserTokens", QJsonArray{m_data->xblToken}}}},
      {"RelyingParty", "rp://api.minecraftservices.com/"},
      {"TokenType", "JWT"}};

  QJsonDocument doc{obj};

  m_reply =
      unique_qobject_ptr<QNetworkReply>(m_data->nam->post(http, doc.toJson()));

  connect(m_reply.get(), &QNetworkReply::finished, this,
          &AuthenticateXSTSStep::networkReplyFinished);
}

void AuthenticateXSTSStep::networkReplyFinished() {
  if (m_reply->error() == QNetworkReply::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(m_reply->readAll());
    QJsonArray arr = doc["DisplayClaims"]["xui"].toArray();

    if (doc["DisplayClaims"]["xui"][0]["uhs"].toString() ==
        m_data->xui_userHash) {
      m_data->xstsToken = doc["Token"].toString();

      emit finished(StepState::Succeed, tr("XSTS account authenticated"));
    } else {
      emit finished(StepState::Failed, tr("XUI token doesn't match."));
    }
  } else {
    QVariant statusCode =
        m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (statusCode.isValid() && statusCode.toInt() == 401) {
      QJsonDocument doc = QJsonDocument::fromJson(m_reply->readAll());
      emit finished(
          StepState::Failed,
          tr("Account authentication failed: %1").arg(doc["XErr"].toString()));
    } else {
      emit finished(StepState::Failed,
                    tr("Unexpected Error: %1").arg(m_reply->errorString()));
    }
  }
}
