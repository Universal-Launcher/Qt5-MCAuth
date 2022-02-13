#include <qt_mcauth/qt_mcauth.h>

#include <QDebug>

MCAuth::MCAuth(const QString &clientID) : QObject(), m_clientID{clientID} {
  m_data = std::make_unique<MCAuthData>();
  m_data->clientID = clientID;
}

LoginFlow *MCAuth::loginAccount() {
  auto flow = new LoginFlow(m_data.get());
  return flow;
}

RefreshFlow *MCAuth::refreshAccount() {
  auto flow = new RefreshFlow(m_data.get());
  return flow;
}
