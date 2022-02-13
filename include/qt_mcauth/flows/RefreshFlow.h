#pragma once

#include "Flow.h"
#include <qt_mcauth/globals.h>

class QT_MCAUTH_EXPORT RefreshFlow : public Flow {
  Q_OBJECT

public:
  RefreshFlow() : Flow() {}
  virtual ~RefreshFlow() {}
};
