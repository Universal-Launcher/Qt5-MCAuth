#include <qt_mcauth/flows/LoginFlow.h>

#include <qt_mcauth/steps/AuthenticateXBox.h>
#include <qt_mcauth/steps/OpenBrowserStep.h>

LoginFlow::LoginFlow(MCAuthData *data) : Flow(data) {
  m_steps.append(std::make_shared<OpenBrowserStep>(data));
  m_steps.append(std::make_shared<AuthenticateXBoxStep>(data));
}

LoginFlow::~LoginFlow() {}
