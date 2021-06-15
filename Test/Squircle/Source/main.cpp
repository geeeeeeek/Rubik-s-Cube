#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include "squircle.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);

    qmlRegisterType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}