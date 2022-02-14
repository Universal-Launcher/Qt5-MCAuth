#include <qt_mcauth/steps/GetMinecraftProfile.h>

GetMinecraftProfileStep::GetMinecraftProfileStep(MCAuthData *data)
    : Step(data) {}

GetMinecraftProfileStep::~GetMinecraftProfileStep() {}

QString GetMinecraftProfileStep::describe() const {
  return tr("GetMinecraftProfile account.");
}

void GetMinecraftProfileStep::execute() {
  QNetworkRequest http{
      QUrl{"https://api.minecraftservices.com/authentication/login_with_xbox"}};
  http.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  http.setRawHeader(QByteArray("Authorization"),
                    "Bearer " + m_data->mcAccessToken.toUtf8());

  m_reply = std::unique_ptr<QNetworkReply>(m_data->nam->get(http));

  connect(m_reply.get(), &QNetworkReply::finished, this,
          &GetMinecraftProfileStep::networkReplyFinished);
}

void GetMinecraftProfileStep::networkReplyFinished() {
  if (m_reply->error() == QNetworkReply::NoError) {
    auto doc = QJsonDocument::fromJson(m_reply->readAll());

    populateMCAccount(doc);

    emit finished(StepState::Succeed, tr("Minecraft profile fetched"));
  } else {
    emit finished(StepState::Failed,
                  tr("Unexpected Error: %1").arg(m_reply->errorString()));
  }
}

void GetMinecraftProfileStep::populateMCAccount(const QJsonDocument &doc) {
  m_data->mcAccount = MCAccount{};
  m_data->mcAccount->id = doc["id"].toString();
  m_data->mcAccount->username = doc["name"].toString();

  for (const QJsonValue &value : doc["skins"].toArray()) {
    MinecraftSkin skin{};
    skin.id = value["id"].toString();
    skin.state = value["state"].toString();
    skin.url = value["url"].toString();
    skin.variant = value["variant"].toString();
    skin.alias = value["alias"].toString();
    m_data->mcAccount->skins.append(skin);
  }

  for (const QJsonValue &value : doc["capes"].toArray()) {
    MinecraftCapes cape{};
    cape.id = value["id"].toString();
    cape.state = value["state"].toString();
    cape.url = value["url"].toString();
    cape.alias = value["alias"].toString();
    m_data->mcAccount->capes.append(cape);
  }
}
