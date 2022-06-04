#include "main.h"


static int  gl_create_window(GLFWwindow* *window, const char *title, bool fullscreen)
{
    GLFWmonitor         *monitor;
    const GLFWvidmode   *mode;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    if (fullscreen)
    {
        monitor = glfwGetPrimaryMonitor();
        mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
 
        *window = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
    }
    else
        *window = glfwCreateWindow(_WIDTH, _HEIGHT, title, NULL, NULL);
    if (!*window)
    {
        glfwTerminate();
        return (-1);
    }
    return(0);
}

static void gl_load(t_env *env)
{
    glfwMakeContextCurrent(env->window);
    gladLoadGL();
    glfwSwapInterval(1);
}

static void gl_init_callback(GLFWwindow* window)
{
    glfwSetKeyCallback(window, cb_key);
    // glfwSetCursorPosCallback(window, cb_cursor_position);
    // glfwSetWindowMaximizeCallback(window, cb_window_maximize);
    // glfwSetWindowFocusCallback(window, cb_window_focus);
    // glfwSetScrollCallback(window, cb_scroll);
}

static void gl_vobjects(t_env *env)
{
    GLuint  elements[] = {
        0, 1, 3,
        0, 2, 3
    };

    // Create Vertex Array Object
    glGenVertexArrays(1, &env->vao);
    glBindVertexArray(env->vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &env->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
    glBufferData(GL_ARRAY_BUFFER,
        env->vertices.nb_cells * sizeof(t_vertices),
        env->vertices.arr, GL_STATIC_DRAW);

    // Create an Elements Buffer Object
    glGenBuffers(1, &env->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

int         gl_init(t_env *env)
{
    glfwSetErrorCallback(cb_error);
    if (!glfwInit() || gl_create_window(&env->window, "scop", false) < 0)
        return (-1);
    gl_load(env);
    gl_init_callback(env->window);
    gl_vobjects(env);
    gl_shaders(env);
    gl_textures(env);
    return (0);
}