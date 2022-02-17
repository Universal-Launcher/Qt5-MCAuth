#include <qt_mcauth/steps/RefreshMSToken.h>

RefreshMSTokenStep::RefreshMSTokenStep(MCAuthData *data) : Step(data) {}

RefreshMSTokenStep::~RefreshMSTokenStep() {}

QString RefreshMSTokenStep::describe() const {
  return tr("Refreshing Microsoft account tokens");
}

void RefreshMSTokenStep::execute() {
  QUrl url{"https://login.live.com/oauth20_token.srf"};
  QUrlQuery queries{};
  queries.addQueryItem("client_id", m_data->clientID);
  queries.addQueryItem("refresh_token", m_data->refreshToken);
  queries.addQueryItem("grant_type", "refresh_token");

  QNetworkRequest http{url};
  http.setHeader(QNetworkRequest::ContentTypeHeader,
                 "application/x-www-form-urlencoded");

  m_reply = unique_qobject_ptr<QNetworkReply>(
      m_data->nam->post(http, queries.toString(QUrl::FullyEncoded).toUtf8()));

  connect(m_reply.get(), &QNetworkReply::finished, this,
          &RefreshMSTokenStep::networkReplyFinished);
}

void RefreshMSTokenStep::networkReplyFinished() {
  if (m_reply->error() == QNetworkReply::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(m_reply->readAll());

    if (doc["access_token"].isString() && doc["refresh_token"].isString()) {

      m_data->accessToken = doc["access_token"].toString();
      m_data->refreshToken = doc["refresh_token"].toString();

      emit finished(StepState::Succeed,
                    tr("Microsoft account tokens refreshed"));
    } else {
      emit finished(StepState::Failed, tr("Invalid data output"));
    }
  } else {
    emit finished(StepState::Failed,
                  tr("Unexpected Error: %1").arg(m_reply->errorString()));
  }
}
