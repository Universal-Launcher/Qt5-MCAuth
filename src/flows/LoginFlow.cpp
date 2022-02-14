#include <qt_mcauth/flows/LoginFlow.h>

#include <qt_mcauth/steps/AuthenticateMinecraft.h>
#include <qt_mcauth/steps/AuthenticateXBox.h>
#include <qt_mcauth/steps/AuthenticateXSTS.h>
#include <qt_mcauth/steps/GetMinecraftProfile.h>
#include <qt_mcauth/steps/OpenBrowser.h>

LoginFlow::LoginFlow(MCAuthData *data) : Flow(data) {
  m_steps.append(std::make_shared<OpenBrowserStep>(data));
  m_steps.append(std::make_shared<AuthenticateXBoxStep>(data));
  m_steps.append(std::make_shared<AuthenticateXSTSStep>(data));
  m_steps.append(std::make_shared<AuthenticateMinecraftStep>(data));
  m_steps.append(std::make_shared<GetMinecraftProfileStep>(data));
}

LoginFlow::~LoginFlow() {}
