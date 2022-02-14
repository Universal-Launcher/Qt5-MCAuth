#pragma once

#include <QList>
#include <QObject>
#include <memory>

#include <qt_mcauth/auth_data.h>
#include <qt_mcauth/globals.h>
#include <qt_mcauth/steps/Step.h>

enum class QT_MCAUTH_EXPORT FlowState { Succeed, Failed, Stopped, Working };

class QT_MCAUTH_EXPORT Flow : public QObject {
  Q_OBJECT

public:
  Flow(MCAuthData *data);
  virtual ~Flow();
  virtual void execute();
  virtual void stop();

private:
  bool changeStep(const StepState &state, const QString &message);

signals:
  void message(const FlowState &state, const QString &message);
  void finished(const FlowState &state);

private slots:
  void stepFinished(const StepState &state, const QString &message);

protected:
  void nextStep();
  void succeed();

  QList<shared_qobject_ptr<Step>> m_steps;
  shared_qobject_ptr<Step> m_currentStep;
  MCAuthData *m_data;
};
