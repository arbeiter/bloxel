#include <glad/glad.h>
#include <random>
#include <GLFW/glfw3.h>
#include <src/shader.h>
#include <src/arcball.h>
#include <src/cube.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 eye(0, 0, 5);
glm::vec3 center(0);
glm::vec3 up(0, 1, 0);
glm::vec2 prev_mouse(-2.f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void sampleFromSpritesheet(int pos, float &top_left_x, float &top_left_y);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// timing
double lastTime = glfwGetTime();
float deltaTime = 0.0f;  // time between current frame and last frame
float lastFrame = 0.0f;
int nbFrames = 0;

// camera
ArcballCamera camera(eye, center, up);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

static void GLAPIENTRY glDebugCallback(GLenum source, GLenum type, GLuint, GLenum severity, GLsizei,
                                       const GLchar* message, const void*)
{
    // clang-format off
    const char* severityString = "?";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:            severityString = "high";    break;
        case GL_DEBUG_SEVERITY_MEDIUM:          severityString = "medium";  break;
        case GL_DEBUG_SEVERITY_LOW:             severityString = "low";     break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:                                return;
    }

    const char* sourceString = "?";
    switch (source) {
        case GL_DEBUG_SOURCE_API:               sourceString = "API";               break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     sourceString = "window system";     break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:   sourceString = "shader compiler";   break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:       sourceString = "third party";       break;
        case GL_DEBUG_SOURCE_APPLICATION:       sourceString = "app";               break;
        case GL_DEBUG_SOURCE_OTHER:             sourceString = "other";             break;
    }

    const char* typeString = "?";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:                   typeString = "error";               break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:     typeString = "deprecated behavior"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:      typeString = "undefined behavior";  break;
        case GL_DEBUG_TYPE_PORTABILITY:             typeString = "portability";         break;
        case GL_DEBUG_TYPE_MARKER:                  typeString = "marker";              break;
        case GL_DEBUG_TYPE_PUSH_GROUP:              typeString = "push group";          break;
        case GL_DEBUG_TYPE_POP_GROUP:               typeString = "pop group";           break;
        case GL_DEBUG_TYPE_OTHER:                   typeString = "other";               break;
    }
    // clang-format on

    fprintf(stderr, "OpenGL Message.\n Type: %s\nSeverity: %s\nSource: %s\nMessage: %s\n\n", typeString, severityString,
            sourceString, message);

    if (severity == GL_DEBUG_SEVERITY_HIGH)
        throw(std::runtime_error("GL Error"));
}

static void initGLDebug() {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugCallback, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}

int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    GLFWvidmode return_struct;
    int* screen_width = new int(0);
    int* screen_height = new int(0);
    glfwGetWindowSize( window, screen_width, screen_height );

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("../shader.vert", "../shader.frag"); // you can name your shader files however you like
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if(flags & GL_CONTEXT_FLAG_DEBUG_BIT ) {
      std::cout << "Debug flags set" << std::endl;
      initGLDebug();
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    std::cout << "Time before" << glfwGetTime() << std::endl;

    glm::mat4 view = camera.transform();
    float height = (float)*screen_height / 2.f;
    float width = (float)*screen_width /2.f;

    Bloxel::TerrainGen t(width, height, 1);
    t.noiseHeightGen();
    std::cout << "Generating mesh"<< std::endl;
    t.generateMeshes();
    unsigned int blockTexture = loadTexture("../resources/textures/out.png");

    // create transformations
    // render loop
    // -----------
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize( window, screen_width, screen_height );
        view = camera.transform();

        //Timing code
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        nbFrames++;
        if(currentFrame - lastTime >= 1.0) {
          printf("%f ms/frame\n", 1000.0/double(nbFrames));
          nbFrames = 0;
          lastTime += 1.0;
        }

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, blockTexture);

        height = (float)*screen_height;
        width = (float)*screen_width;

        ourShader.use();
        view = camera.transform();
        t.render(ourShader, view, height, width);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    glm::vec2 p_mouse(-2.f);
    glm::vec2 c_mouse(2.f);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      camera.pan(p_mouse);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      camera.pan(c_mouse);
}

//convert to NDC
glm::vec2 transform_mouse(int h, int w, glm::vec2 in)
{
    return glm::vec2(in.x * 2.f / w - 1.f, 1.f - 2.f * in.y / h );
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    int* screen_width = new int(0);
    int* screen_height = new int(0);
    glfwGetWindowSize( window, screen_width, screen_height );

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    const glm::vec2 cur_mouse = transform_mouse(*screen_height, *screen_width, glm::vec2(xpos, ypos));
    if(prev_mouse != glm::vec2(-2.f)) {
      camera.rotate(prev_mouse, cur_mouse);
    }
    prev_mouse = cur_mouse;
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
