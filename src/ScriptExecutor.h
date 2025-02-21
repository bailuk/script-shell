#ifndef SCRIPTEXECUTOR_H
#define SCRIPTEXECUTOR_H

#include <QObject>
#include <QProcess>
#include <QString>

class ScriptExecutor : public QObject {
    Q_OBJECT

public:
    explicit ScriptExecutor();
    void execute(const QString &scriptPath);

    bool isExecuting() {
        return executing;
    }

private slots:
    void onReadyRead();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus = QProcess::ExitStatus::NormalExit);


signals:
    void haveLine(const QString& line);
    void stateChanged(const QString& status);

private:
    QProcess *process;
    std::string nextLine;
    bool executing = false;

    void handleLines(const std::string& input);
    void handleLine(const std::string& line);
};

#endif // SCRIPTEXECUTOR_H
