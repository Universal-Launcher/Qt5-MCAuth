#pragma once

#include <qt_mcauth/globals.h>
#include <qt_mcauth/steps/Step.h>

class QT_MCAUTH_EXPORT AuthenticateXSTSStep : public Step {
  Q_OBJECT

public:
  AuthenticateXSTSStep(MCAuthData *data);
  ~AuthenticateXSTSStep();

  QString describe() const;

public slots:
  void execute();

private slots:
  void networkReplyFinished();

private:
  unique_qobject_ptr<QNetworkReply> m_reply;
};
