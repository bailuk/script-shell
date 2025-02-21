#include "Script.h"


Script::Script(const QString &name, const QString &path)
: name(name)
, path(path) {

    connect(executor, SIGNAL(haveLine(QString)), this, SLOT(onHaveLine(QString)));
    connect(executor, SIGNAL(stateChanged(QString)), this, SLOT(onStateChanged(QString)));
 }

void Script::onHaveLine(const QString& line) {
    if (line1.isEmpty()) {
        line1 = line;
    } else if (line2.isEmpty()) {
        line2 = line;
    } else {
        line1 = line2;
        line2 = line;
    }
    emit modelUpdated();
}

void Script::onStateChanged(const QString& s) {
    state = s;
    emit modelUpdated();
}
