#include "OpenGLWindow.h"
#include "OpenGLRenderer.h"

#include <QQuickWindow>

OpenGLWindow::OpenGLWindow(QQuickItem* parent /*= nullptr*/)
    : QQuickItem(parent)
{
    initConnect();
}

OpenGLWindow::~OpenGLWindow()
{

}

void OpenGLWindow::initConnect()
{
    connect(this, &QQuickItem::windowChanged, this, &OpenGLWindow::onWindowChanged);
}

void OpenGLWindow::releaseResources()
{
    window()->scheduleRenderJob(new CleanupJob(m_renderer), QQuickWindow::BeforeSynchronizingStage);
    m_renderer = nullptr;
}

void OpenGLWindow::onWindowChanged(QQuickWindow* window)
{
    // note: item 加入和移除场景的时候触发
    if (window)
    {
        // note: 场景的OpenGL context在此时绑定，必须使用Qt::DirectConnection，防止在不存在
        // OpenGL context的错误线程上创建渲染器
        connect(window, &QQuickWindow::beforeSynchronizing, this, &OpenGLWindow::onSync,
                static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));
        // note: 场景的OpenGL context在此时已经失效
        connect(window, &QQuickWindow::sceneGraphInvalidated, this, &OpenGLWindow::onCleanup,
                static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));

        window->setColor(Qt::black);

    }
}

void OpenGLWindow::onSync()
{
    // note: 创建渲染器，并将状态同步
    if (!m_renderer)
    {
        m_renderer = new OpenGLRenderer;
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &OpenGLRenderer::onInit, Qt::DirectConnection);
        connect(window(), &QQuickWindow::beforeRenderPassRecording, m_renderer, &OpenGLRenderer::onPaint, Qt::DirectConnection);
    }

    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setWindow(window());
}

void OpenGLWindow::onCleanup()
{
    delete m_renderer;
    m_renderer = nullptr;
}

