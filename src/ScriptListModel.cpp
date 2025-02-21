#include "ScriptListModel.h"


ScriptListModel::ScriptListModel(QObject *parent) 
    : QAbstractListModel(parent) {}

void ScriptListModel::addScript(Script *script) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    scripts.append(script);
    endInsertRows();
}

int ScriptListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return scripts.count();
}

QVariant ScriptListModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role == NameRole) {
        return scripts[index.row()]->getName();
    }
    return QVariant();
}

QHash<int, QByteArray> ScriptListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

Script* ScriptListModel::getScript(int i) {
    return scripts[i];
}