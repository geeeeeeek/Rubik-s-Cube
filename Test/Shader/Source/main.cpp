#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include "OpenGLWindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);

    qmlRegisterType<OpenGLWindow>("OpenGLUnderQML", 1, 0, "OpenGLWindow");

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