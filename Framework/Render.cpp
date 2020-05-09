#include "Renderer.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


     static float attributes[] = {
    0.0f,
    0.5f,
    1.0f,
    0.0f,
    0.0f,

    0.5f,
    -0.5f,
    0.0f,
    1.0f,
    0.0f,

    -0.5f,
    -0.5f,
    0.0f,
    0.0f,
    1.0f
};

Renderer::Renderer(/* args */)
{


    rotation_angle = -0.01;
    length_of_attributes = sizeof(attributes) / sizeof(attributes[0]);

    vertexSource = R"glsl(
#version 100
attribute vec2 position;
attribute vec3 color;
varying vec3 vColor;
void main()
{
  vColor = color;
  gl_Position = vec4(position, 0.0, 1.0);
}
)glsl";

    fragmentSource = R"glsl(
#version 100
precision mediump float;
varying vec3 vColor;
void main()
{
    gl_FragColor = vec4(vColor, 1.0);
}
)glsl";
}

Renderer::~Renderer()
{
    SDL_GL_DeleteContext(context);
    SDL_Quit();
}



void Renderer::makeShader()
{
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertexSource, NULL);
    glCompileShader(vertex_shader);
    GLint vertex_shader_status;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_shader_status);

    char vertexLogBuffer[512];
    glGetShaderInfoLog(vertex_shader, 512, NULL, vertexLogBuffer);
    std::cout << "vertex_shader_status: " << vertex_shader_status << " " << vertexLogBuffer << std::endl;

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragmentSource, NULL);
    glCompileShader(fragment_shader);
    GLint fragment_shader_status;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_shader_status);

    char fragmentLogBuffer[512];
    glGetShaderInfoLog(fragment_shader, 512, NULL, fragmentLogBuffer);
    std::cout << "fragment_shader_status: " << fragment_shader_status << " " << fragmentLogBuffer << std::endl;

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glUseProgram(shader_program);

    //bind shader data

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(attributes), attributes, GL_DYNAMIC_DRAW);

    GLint pos_attrib = glGetAttribLocation(shader_program, "position");
    GLint color_attrib = glGetAttribLocation(shader_program, "color");

    glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(pos_attrib);

    glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid *)(2 * sizeof(float)));
    glEnableVertexAttribArray(color_attrib);
}

void Renderer::Init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    #if __EMSCRIPTEN__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    #else
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    #endif

    window = SDL_CreateWindow("Lavumi", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte *version;
    version = glGetString(GL_VERSION);
    std::cout << "version: " << version << std::endl;

    InputHandler::getInstance()->myfxClickLeft = [&]{
        background_is_black = !background_is_black;
        std::cout << "clickTest" << std::endl;
    };

    makeShader();
}

void Renderer::Update()
{
    for (GLuint i = 0; i < length_of_attributes; i = i + 5)
    {
        float x = attributes[i];
        float y = attributes[i + 1];

        attributes[i] = x * cos(rotation_angle) - y * sin(rotation_angle);
        attributes[i + 1] = y * cos(rotation_angle) + x * sin(rotation_angle);
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(attributes), attributes, GL_DYNAMIC_DRAW);
}

void Renderer::Render()
{
    // Clear the screen
    if (background_is_black)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    else
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    SDL_GL_SwapWindow(window);
}

