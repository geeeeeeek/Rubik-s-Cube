#include "OpenGLRenderer.h"

#include <QQuickWindow>
#include <QSGRendererInterface>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

OpenGLRenderer::OpenGLRenderer(QObject* parent /*= nullptr*/)
    : QObject(parent)
    , m_vao(new QOpenGLVertexArrayObject)
    , m_vbo(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
{

}

OpenGLRenderer::~OpenGLRenderer()
{
    m_vbo->destroy();
    m_vao->destroy();

    delete m_vbo;
    m_vbo = nullptr;

    delete m_vao;
    m_vao = nullptr;

    delete m_program;
    m_program = nullptr;
}

void OpenGLRenderer::setViewportSize(const QSize& size)
{
    m_viewportSize = size;
}

void OpenGLRenderer::setWindow(QQuickWindow* window)
{
    m_window = window;
}

void OpenGLRenderer::onInit()
{
    if (!m_program)
    {
        if (m_window)
        {
            auto rif = m_window->rendererInterface();
            Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL || rif->graphicsApi() == QSGRendererInterface::OpenGLRhi);
        }

        initializeOpenGLFunctions();

        initProgram();

        initData();
    }
}

void OpenGLRenderer::onPaint()
{
    m_window->beginExternalCommands();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    {
        QOpenGLVertexArrayObject::Binder vaoBind(m_vao);
        glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

        glDisable(GL_DEPTH_TEST);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    m_program->release();

    m_window->endExternalCommands();
}

void OpenGLRenderer::initProgram()
{
    m_program = new QOpenGLShaderProgram();
    m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,
                                                "#version 330 core\n"
                                                "layout (location = 0) in vec3 aPos;\n"
                                                "layout (location = 1) in vec3 aColor;\n"
                                                "out vec3 ourColor;\n"
                                                "void main()\n"
                                                "{\n"
                                                "   gl_Position = vec4(aPos, 1.0);\n"
                                                    "ourColor = aColor;\n"
                                                "}\0");
    m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
                                                "#version 330 core\n"
                                                "out vec4 FragColor;\n"
                                                "in vec3 ourColor;\n"
                                                "void main()\n"
                                                "{\n"
                                                "   FragColor = vec4(ourColor, 1.0);\n"
                                                "}\n\0");

    m_program->link();
}

void OpenGLRenderer::initData()
{
    float vertices[] = {
         0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    QOpenGLVertexArrayObject::Binder vaoBind(m_vao);

    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(vertices, sizeof(vertices));


    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 6);
    m_program->enableAttributeArray(0);

    m_program->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), 3, sizeof(GLfloat) * 6);
    m_program->enableAttributeArray(1);

    m_vbo->release();
}
