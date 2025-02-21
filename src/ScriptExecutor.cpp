#include <QCoreApplication>
#include <QProcess>
#include <QTextStream>
#include <iostream>
#include <regex>

#include "ScriptExecutor.h"


const std::regex pattern(R"(^->(.*)$)");

ScriptExecutor::ScriptExecutor() {
    process = new QProcess(this);
    nextLine = "";

    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onProcessFinished(int, QProcess::ExitStatus)));
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadyRead()));
}

void ScriptExecutor::execute(const QString &scriptPath) {
    if (executing == false) {
        executing = true;
        emit stateChanged("...");

        nextLine = "";
        const QStringList arguments = {};
        process->start(scriptPath, arguments);
    }
}

void ScriptExecutor::onReadyRead() {
    QByteArray output = process->readAllStandardOutput();
    handleLines(output.toStdString());
}

void ScriptExecutor::handleLines(const std::string& input) {
    if (!input.empty()) {
        std::stringstream stream(input);
        std::string currentLine;

        while (std::getline(stream, currentLine)) {
            handleLine(nextLine);
            nextLine = currentLine;
        }

        if (input.back() == '\n') {
            handleLine(nextLine);
            nextLine = "";
        } else {
            nextLine = currentLine;
        }
    }
}

void ScriptExecutor::handleLine(const std::string& line) {
    std::smatch match;

    if (std::regex_match(line, match, pattern)) {
        std::string result = match[1].str();
        emit haveLine(QString::fromStdString(result).trimmed());
    }
}

void ScriptExecutor::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    if (exitStatus == QProcess::NormalExit && exitCode == 0) {
        emit stateChanged("OK");
    } else {
        emit stateChanged("ERR");
    }
    handleLine(nextLine);
    executing = false;
}
