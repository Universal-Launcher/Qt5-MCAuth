#include <QDebug>
#include <qt_mcauth/flows/Flow.h>

Flow::Flow(MCAuthData *data) : QObject(), m_data{data} {}

Flow::~Flow() {}

void Flow::execute() {
  if (m_currentStep)
    return;

  changeStep(StepState::Working, tr("Initializing"));
  nextStep();
}

void Flow::stop() {
  m_currentStep.reset();
  m_steps.clear();
  emit finished(FlowState::Stopped);
}

void Flow::nextStep() {
  if (m_steps.size() == 0) {
    m_currentStep.reset();
    emit finished(FlowState::Succeed);
    return;
  }

  m_currentStep = m_steps.front();
  qDebug() << "Flow step: " << m_currentStep->describe();
  m_steps.pop_front();

  connect(m_currentStep.get(), &Step::finished, this, &Flow::stepFinished);

  m_currentStep->execute();
}

void Flow::succeed() {}

void Flow::stepFinished(const StepState &state, const QString &message) {
  if (changeStep(state, message)) {
    nextStep();
  }
}

bool Flow::changeStep(const StepState &state, const QString &msg) {
  switch (state) {
  case StepState::Failed:
    emit message(FlowState::Failed, msg);
    return false;
  case StepState::Stopped:
    emit message(FlowState::Stopped, msg);
    return false;
  case StepState::Succeed:
    emit message(FlowState::Succeed, msg);
    return true;
  case StepState::Working:
    emit message(FlowState::Working, msg);
    return true;
  default:
    emit message(FlowState::Working, tr("Unknown state"));
    return false;
  }
}
