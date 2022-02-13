#include "qt_mcauth/qt_mcauth.h"

#include <QDebug>

MCAuth::MCAuth(const QString &clientID) : QObject() {
  qDebug() << "Client ID: " << clientID;
}

Flow *MCAuth::loginAccount() {
  auto flow = new Flow();
  return flow;
}

Flow *MCAuth::refreshAccount() {
  auto flow = new Flow();
  return flow;
}
