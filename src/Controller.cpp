#include "Controller.h"
#include <iostream>
#include <sys/stat.h>
#include <regex>

namespace fs = std::filesystem;

bool is_executable(const fs::path& p) {
    struct stat buffer;
    if (stat(p.c_str(), &buffer) == 0) {
        return buffer.st_mode & S_IXUSR || buffer.st_mode & S_IXGRP || buffer.st_mode & S_IXOTH;
    }
    return false;
}

std::regex pattern1(R"(^(\d*)_(.*)\..*$)");
std::regex pattern2(R"(^(.*)\..*$)");
std::string path = "/home/ceres/script-shell";

std::string extractScriptName(const std::string filename) {
    std::smatch match;
    std::string result;

    if (std::regex_match(filename, match, pattern1)) {
        result = match[2].str();
    } else if (std::regex_match(filename, match, pattern2)) {
        result = match[1].str();
    } else {
        result = filename;
    }
    return result;
}

Controller::Controller(ScriptListModel* model)
        : QObject(nullptr), model(model) {
    try {
        std::vector<fs::directory_entry> entries;

        for (const auto &entry : fs::directory_iterator(path)) {
            if (fs::is_regular_file(entry) && is_executable(entry.path())) {
                entries.push_back(entry);
            }
        }

        std::sort(entries.begin(), entries.end(), [](const fs::directory_entry &a, const fs::directory_entry &b) {
            return a.path().filename() < b.path().filename();
        });

        for (const auto &entry : entries) {
            addEntryToModel(entry);
        }

    } catch (const fs::filesystem_error& err) {
        std::cerr << "Error: " << err.what() << std::endl;
    }
}

void Controller::addEntryToModel(const std::filesystem::directory_entry& entry) {
    std::string name = extractScriptName(entry.path().filename().string());
    std::replace(name.begin(), name.end(), '-', ' ');
    std::replace(name.begin(), name.end(), '_', ' ');

    QString qname = QString::fromStdString(name).trimmed();
    QString qpath = QString::fromStdString(entry.path().string());

    if (!qname.isEmpty()) {
        Script* script = new Script(qname, qpath);
        connect(script, SIGNAL(modelUpdated()), this, SLOT(onModelUpdated()));
        model->addScript(script);
    }
}

void Controller::onModelUpdated() {
    emit modelUpdated();
}
