#ifndef SCRIPTLISTMODEL_H
#define SCRIPTLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "Script.h"

class ScriptListModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum ScriptRoles {
        NameRole = Qt::UserRole + 1
    };

    ScriptListModel(QObject *parent = nullptr);

    void addScript(Script *script);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Script* getScript(int i);
protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Script*> scripts;
};

#endif // SCRIPTLISTMODEL_H
