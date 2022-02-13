#pragma once

#include <qt_mcauth/globals.h>
#include <qt_mcauth/steps/Step.h>

class QT_MCAUTH_EXPORT AuthenticateXBoxStep : public Step {
  Q_OBJECT

public:
  AuthenticateXBoxStep(MCAuthData *data);
  ~AuthenticateXBoxStep();

  QString describe() const;

public slots:
  void execute();

private slots:
  void networkReplyFinished();

private:
  std::unique_ptr<QNetworkReply> m_reply;
};
