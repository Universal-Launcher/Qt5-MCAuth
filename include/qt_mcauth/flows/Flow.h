#pragma once

#include <QList>
#include <QObject>
#include <memory>

#include <qt_mcauth/globals.h>

enum class QT_MCAUTH_EXPORT FlowState { Succeed, Failed, Stopped, Working };

class QT_MCAUTH_EXPORT Flow : public QObject {
  Q_OBJECT

public:
  Flow() : QObject() {}
  virtual ~Flow() {}
  virtual void execute();
  virtual void stop();

signals:
  void message(const FlowState &state, const QString &message);
  void finished(const FlowState &state);

protected:
  void nextStep();
  void succeed();

  QList<std::shared_ptr<QObject>> m_steps;
  std::shared_ptr<QObject *> m_currentStep;
};
