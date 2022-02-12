#pragma once

#include <QList>
#include <QObject>
#include <memory>

namespace QtMCAuth {
enum class FlowState { Succeed, Failed, Stopped, Working };

class Flow : public QObject {
  Q_OBJECT

public:
  void execute();
  void stop();
  QObject *getAccount();

signals:
  void message(const FlowState &state, const QString &message);
  void finished(const FlowState &state);

protected:
  void nextStep();
  void succeed();

  QList<std::shared_ptr<QObject>> m_steps;
  std::shared_ptr<QObject *> m_currentStep;
};

} // namespace QtMCAuth
