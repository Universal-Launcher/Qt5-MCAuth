#include <qt_mcauth/flows/LoginFlow.h>

#include <qt_mcauth/steps/AuthenticateMinecraft.h>
#include <qt_mcauth/steps/AuthenticateXBox.h>
#include <qt_mcauth/steps/AuthenticateXSTS.h>
#include <qt_mcauth/steps/GetMinecraftProfile.h>
#include <qt_mcauth/steps/OpenBrowser.h>

LoginFlow::LoginFlow(MCAuthData *data) : Flow(data) {
  m_steps.append(
      shared_qobject_ptr<OpenBrowserStep>(new OpenBrowserStep(data)));
  m_steps.append(
      shared_qobject_ptr<AuthenticateXBoxStep>(new AuthenticateXBoxStep(data)));
  m_steps.append(
      shared_qobject_ptr<AuthenticateXSTSStep>(new AuthenticateXSTSStep(data)));
  m_steps.append(shared_qobject_ptr<AuthenticateMinecraftStep>(
      new AuthenticateMinecraftStep(data)));
  m_steps.append(shared_qobject_ptr<GetMinecraftProfileStep>(
      new GetMinecraftProfileStep(data)));
}

LoginFlow::~LoginFlow() {}
