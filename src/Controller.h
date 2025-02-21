#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <filesystem>
#include "ScriptListModel.h"

class Controller : public QObject {
    Q_OBJECT

public:
    explicit Controller(ScriptListModel *model);

    Q_INVOKABLE void selectScript(int index) {
        selected = index;
    }

    Q_INVOKABLE void executeSelected() {
        model->getScript(selected)->execute();
    }

    Q_INVOKABLE QString selectedScriptName() {
        return model->getScript(selected)->getName();
    }

    Q_INVOKABLE QString selectedScriptState() {
        return model->getScript(selected)->getState();
    }

    Q_INVOKABLE QString selectedScriptLine1() {
        return model->getScript(selected)->getLine1();
    }

    Q_INVOKABLE QString selectedScriptLine2() {
        return model->getScript(selected)->getLine2();
    }

signals:
    void modelUpdated();

public slots:
    void onModelUpdated();

private:
    void addEntryToModel(const std::filesystem::directory_entry& entry);

    ScriptListModel *model;
    int selected = 0;
};

#endif // CONTROLLER_H
