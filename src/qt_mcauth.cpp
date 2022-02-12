#include "qt_mcauth/qt_mcauth.h"

namespace QtMCAuth {

QtMCAuth::QtMCAuth(const QString &clientID) {}

QtMCAuth::~QtMCAuth() {}

LoginFlow *QtMCAuth::loginAccount() {
  auto flow = new LoginFlow();
  return flow;
}

RefreshFlow *QtMCAuth::refreshAccount() {
  auto flow = new RefreshFlow();
  return flow;
}

} // namespace QtMCAuth
