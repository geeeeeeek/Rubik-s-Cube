#pragma once

#include <QOpenGLFunctions>
#include <QObject>
#include <QSize>

class QOpenGLShaderProgram;
class QQuickWindow;
class QOpenGLBuffer;
class QOpenGLVertexArrayObject;

class OpenGLRenderer : public QObject, public QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLRenderer(QObject* parent = nullptr);
    ~OpenGLRenderer();

    void setViewportSize(const QSize& size);
    void setWindow(QQuickWindow* window);
public slots:
    void onInit();
    void onPaint();
private:
    void initProgram();
    void initData();
private:
    QSize m_viewportSize;
    QOpenGLShaderProgram* m_program{nullptr};
    QQuickWindow* m_window{nullptr};
    QOpenGLVertexArrayObject* m_vao{nullptr};
    QOpenGLBuffer* m_vbo{nullptr};
    QOpenGLBuffer* m_ebo{nullptr};
};
