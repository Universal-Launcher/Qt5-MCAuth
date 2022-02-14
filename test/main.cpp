#include "secret.h"
#include <iostream>

#include <QGuiApplication>
#include <memory>
#include <qt_mcauth/qt_mcauth.h>

int main(int argc, char *argv[]) {
  Q_UNUSED(argc);
  Q_UNUSED(argv);

  QGuiApplication app(argc, argv);

  std::cout << "QtMCAuth test " << std::endl;

  auto mcAuth =
      unique_qobject_ptr<MCAuth>(new MCAuth(Secrets::getMSAClientID()));

  std::cout << "Running account login" << std::endl;

  auto flow = mcAuth->loginAccount();

  QObject::connect(flow, &LoginFlow::finished, [&](const FlowState &state) {
    if (state == FlowState::Succeed) {
      std::cout << "Show user username" << std::endl;

      auto account = mcAuth->getAccount();
      if (account.has_value()) {
        std::cout << "username: " << account->username.toStdString()
                  << std::endl;
      }
    } else {
    }
  });

  QObject::connect(flow, &LoginFlow::message,
                   [&](const FlowState &state, const QString &msg) {
                     Q_UNUSED(state);
                     std::cout
                         << "Authenticating user state: " << msg.toStdString()
                         << std::endl;
                   });

  flow->execute();

  return app.exec();
}
