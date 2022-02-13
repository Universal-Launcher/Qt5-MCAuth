#pragma once

#include <qt_mcauth/flows/Flow.h>

#include <qt_mcauth/globals.h>

class QT_MCAUTH_EXPORT LoginFlow : public Flow {
  Q_OBJECT
public:
  LoginFlow(MCAuthData *data);
  ~LoginFlow();
};
