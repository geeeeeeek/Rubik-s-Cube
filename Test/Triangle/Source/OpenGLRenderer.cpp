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
    , m_ebo(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer))
{

}

OpenGLRenderer::~OpenGLRenderer()
{
    m_ebo->destroy();
    m_vbo->destroy();
    m_vao->destroy();

    delete m_ebo;
    m_ebo = nullptr;

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
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
                                                "void main()\n"
                                                "{\n"
                                                "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                                "}\0");
    m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
                                                "#version 330 core\n"
                                                "out vec4 FragColor;\n"
                                                "void main()\n"
                                                "{\n"
                                                "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                                "}\n\0");

    m_program->link();
}

void OpenGLRenderer::initData()
{
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    QOpenGLVertexArrayObject::Binder vaoBind(m_vao);

    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(vertices, sizeof(vertices));

    m_ebo->create();
    m_ebo->bind();
    m_ebo->allocate(indices, sizeof(indices));

    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
    m_program->enableAttributeArray(0);

    m_vbo->release();
}
