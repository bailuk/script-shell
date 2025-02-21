/*
 * Copyright (C) 2025 - Lukas Bai <bailu@bailu.ch>
 * Copyright (C) 2019 - Florent Revest <revestflo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

 #include <QGuiApplication>
 #include <QQuickView>
 #include <QScreen>
 #include <QtQml>
 
 #include <asteroidapp.h>
 
 #include "ScriptListModel.h"
 #include "Controller.h"
 
 int main(int argc, char* argv[])
 {
     ScriptListModel model;
     Controller controller(&model);
 
     QScopedPointer<QGuiApplication> app(AsteroidApp::application(argc, argv));
     QScopedPointer<QQuickView> view(AsteroidApp::createView());
     view->rootContext()->setContextProperty("scriptListModel",  &model);
     view->rootContext()->setContextProperty("controller", &controller);
     view->setSource(QUrl("qrc:/main.qml"));
     view->resize(app->primaryScreen()->size());
     view->show();
 
     return app->exec();
 }
 