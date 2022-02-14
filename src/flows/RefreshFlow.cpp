#include <qt_mcauth/flows/RefreshFlow.h>

#include <qt_mcauth/steps/AuthenticateMinecraft.h>
#include <qt_mcauth/steps/AuthenticateXBox.h>
#include <qt_mcauth/steps/AuthenticateXSTS.h>
#include <qt_mcauth/steps/GetMinecraftProfile.h>

RefreshFlow::RefreshFlow(MCAuthData *data) : Flow(data) {
  m_steps.append(std::make_shared<AuthenticateXBoxStep>(data));
  m_steps.append(std::make_shared<AuthenticateXSTSStep>(data));
  m_steps.append(std::make_shared<AuthenticateMinecraftStep>(data));
  m_steps.append(std::make_shared<GetMinecraftProfileStep>(data));
}

RefreshFlow::~RefreshFlow() {}
