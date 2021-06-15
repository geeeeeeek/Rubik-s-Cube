#pragma once

#include <QQuickItem>
#include <QRunnable>
#include "OpenGLRenderer.h"


class CleanupJob : public QRunnable
{
public:
    CleanupJob(OpenGLRenderer *renderer) : m_renderer(renderer) {}
    virtual void run() override { delete m_renderer; }
private:
    OpenGLRenderer* m_renderer{nullptr};
};


class OpenGLWindow : public QQuickItem
{
    Q_OBJECT
public:
    explicit OpenGLWindow(QQuickItem* parent = nullptr);
    ~OpenGLWindow();
private:
    void initConnect();

    virtual void releaseResources() override;
private slots:
    void onWindowChanged(QQuickWindow* window);
    void onSync();
    void onCleanup();
private:
    OpenGLRenderer *m_renderer{nullptr};
};