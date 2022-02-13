#include "secret.h"
#include <iostream>

#include <QCoreApplication>
#include <memory>
#include <qt_mcauth/qt_mcauth.h>

int main(int argc, char *argv[]) {
  Q_UNUSED(argc);
  Q_UNUSED(argv);

  std::cout << "QtMCAuth test " << std::endl;

  auto mcAuth = std::make_unique<MCAuth>(Secrets::getMSAClientID());

  std::cout << "Running account login" << std::endl;

  auto flow = mcAuth->loginAccount();
  /*
    QObject::connect(flow, &QtMCAuth::LoginFlow::finished,
                     [&](const QtMCAuth::FlowState &state) {
                       if (state == QtMCAuth::FlowState::Succeed) {
                         std::cout << "Show user username" << std::endl;

                         auto account = mcAuth->getAccount();
                         std::cout
                             << "Username: " <<
    account->username().toStdString()
                             << std::endl;
                       } else {
                       }
                     });

    QObject::connect(flow, &QtMCAuth::LoginFlow::message,
                     [&](const QtMCAuth::FlowState &state, const QString &msg) {
                       Q_UNUSED(state);
                       std::cout
                           << "Authenticating user state: " << msg.toStdString()
                           << std::endl;
                     });
  */
  return 0;
}
