#ifndef SCRIPT_MODEL_H
#define SCRIPT_MODEL_H

#include <QObject>
#include <QString>
#include "ScriptExecutor.h"

class Script : public QObject {
    Q_OBJECT

    public:
        Script(const QString &name, const QString &path);

        QString getName()  { return name; }
        QString getLine1() { return line1; }
        QString getLine2() { return line2; }
        QString getState() { return state; }

        void execute() {
            if (executor->isExecuting() == false) {
                line1 = "";
                line2 = "";
                executor->execute(path);
            }
        }

    public slots:
        void onHaveLine(const QString& line);
        void onStateChanged(const QString& state);

    signals:
        void modelUpdated();

    private:
        const QString name;
        const QString path;
        QString line1 = "";
        QString line2 = "";
        QString state = "";
        ScriptExecutor* executor = new ScriptExecutor();
};

#endif // SCRIPT_MODEL_H
