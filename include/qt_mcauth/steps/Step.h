#pragma once

#include <QObject>
#include <qt_mcauth/auth_data.h>
#include <qt_mcauth/globals.h>

enum class QT_MCAUTH_EXPORT StepState { Succeed, Failed, Stopped, Working };

class QT_MCAUTH_EXPORT Step : public QObject {
  Q_OBJECT

public:
  Step(MCAuthData *data);
  virtual ~Step() noexcept = default;

  virtual QString describe() const = 0;

signals:
  void finished(const StepState &state, const QString &message);

public slots:
  virtual void execute() = 0;

protected:
  MCAuthData *m_data;
};
