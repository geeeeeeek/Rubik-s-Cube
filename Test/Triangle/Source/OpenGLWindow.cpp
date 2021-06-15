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
    // note: item ������Ƴ�������ʱ�򴥷�
    if (window)
    {
        // note: ������OpenGL context�ڴ�ʱ�󶨣�����ʹ��Qt::DirectConnection����ֹ�ڲ�����
        // OpenGL context�Ĵ����߳��ϴ�����Ⱦ��
        connect(window, &QQuickWindow::beforeSynchronizing, this, &OpenGLWindow::onSync,
                static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));
        // note: ������OpenGL context�ڴ�ʱ�Ѿ�ʧЧ
        connect(window, &QQuickWindow::sceneGraphInvalidated, this, &OpenGLWindow::onCleanup,
                static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));

        window->setColor(Qt::black);

    }
}

void OpenGLWindow::onSync()
{
    // note: ������Ⱦ��������״̬ͬ��
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

