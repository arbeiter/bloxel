#include <glad/glad.h>
#include <random>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <camera.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void sampleFromSpritesheet(int pos, float &top_left_x, float &top_left_y);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// timing
float deltaTime = 0.0f;  // time between current frame and last frame
float lastFrame = 0.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, -10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

void renderTriangle() {
  /* 
    - Triangle strip experiments
      - Color triangle strip single color
      - Color co-ordinates
      - Texture co-ordinates
      - Blend textures on two levels
  */
  /*
    std::vector<float> vertices;
    int height = 1000;
    int width = 1000;
    int NUM_VERTS_PER_STRIP = width * 2;

    int height_y = 0;
    int tileWidth = 1;
    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        // generate random
        // screenX = ( i * tileWidth / 2) + (j * tileWidth/2)
        // screenZ = ( i * tileWidth / 2) - (j * tileWidth/2)
        float x =  ( i * tileWidth / 2) + (j * tileWidth/2);
        float y = height_y;
        float z = ( i * tileWidth / 2) - (j * tileWidth/2);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
      }
    }

    int rez = 1;
    std::vector<unsigned> indices;
    for(unsigned i = 0; i < height - 1; i += rez) {
      for(unsigned j = 0; j < width; j += rez) {
        for(unsigned k = 0; k < 2; k++)
        {
          indices.push_back(j + width * (i + k*rez));
        }
      }
    }

    GLuint terrainVBO, terrainVAO, terrainEBO;
    glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);

    glGenBuffers(1, &terrainVBO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &terrainEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);
    */
}

void terrainDrawLoop(GLuint terrainVAO, int height) {
        /*
        // build and compile our shader program
        // ------------------------------------
        Shader ourShader("../shader.vert", "../shader.frag"); // you can name your shader files however you like
        ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
        unsigned int sandTexture = loadTexture("../resources/textures/sand.png");
        unsigned int rockTexture = loadTexture("../resources/textures/wall.jpg");
        ourShader.setInt("texture1", 0);
        ourShader.setInt("texture2", 1);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindVertexArray(terrainVAO);
        for(int i = 0; i < height-1; i++) {
          glDrawElements(GL_TRIANGLE_STRIP,
                         NUM_VERTS_PER_STRIP,
                         GL_UNSIGNED_INT,
                         (void *)(sizeof(unsigned int) * NUM_VERTS_PER_STRIP * i)
                         );
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sandTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, rockTexture);
        */
}

void sampleFromSpritesheet(int pos, float &top_left_x, float &top_left_y) {
  float sheet_w, sheet_h;
  int num_characters_per_row;
  float character_w, character_h;
  character_w = 0.142f;
  character_h = 0.142f;
  std::cout << (float)(1/7) << std::endl;
  sheet_w = 1;
  sheet_h = 1;
  // 896 is map total width, projected over 1
  // 896 is map total height, projected over 1
  // 128 is character total width, projected over 1
  // 128 is character total height, projected over 1

  num_characters_per_row = 7;
  std::cout << num_characters_per_row << std::endl;
  int character_row = (int)(pos / num_characters_per_row);
  int character_column = pos % num_characters_per_row;
  std::cout << character_row << " " << character_column << std::endl;
  std::cout << character_w << " " << character_h << std::endl;

  float pos_y = (float)(character_row * character_h);
  float pos_x = (float)(character_column * character_w);

  top_left_x =  pos_x;
  top_left_y = pos_y;
  std::cout << pos_x << " " << pos_y << std::endl;
}


unsigned int renderCube()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float wrap = 0.142f;
    float wrap_2 = 0.142f; 
    float wrap_3 = 0.142f;

    float top_left_x, top_left_y;
    sampleFromSpritesheet(10, top_left_x, top_left_y);
    float top_right_x = top_left_x + wrap;
    float top_right_y = top_left_y;
    float bottom_left_x = top_left_x;
    float bottom_left_y = top_left_y + wrap;
    float bottom_right_x = top_left_x + wrap;
    float bottom_right_y = top_left_y + wrap;

    // top_right -> (pos_x + character_w, pos_y)
    // bottom_left -> (pos_x, pos_y + character_h)
    // bottom_right -> (pos_x + character_w, pos_y + character_h)
    std::cout << top_left_x << top_left_y << std::endl;

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  top_left_x,  top_left_y,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  top_right_x,  top_right_y,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  bottom_left_x,  bottom_left_y,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  bottom_left_x,  bottom_left_y,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  top_right_x,  top_right_y,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  bottom_right_x,  bottom_right_y

        /*
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  wrap_2, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  wrap_2, wrap_2,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  wrap_2, wrap_2,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  wrap_2,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  wrap_3,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  wrap_3,  wrap_3,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  wrap_3,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  wrap_3,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  wrap_3,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  wrap_3,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  wrap_3,  wrap_3,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  wrap_3,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  wrap_3,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  wrap_3,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  wrap_3,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  wrap_3, wrap_3,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  wrap_3,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  wrap_3,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  wrap_3,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  wrap_2,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  wrap_2,  wrap_2,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  wrap_2,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  wrap_2,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  wrap_2
        */
    };

    glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
    };

    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    return cubeVAO;
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    glfwSetScrollCallback(window, scroll_callback);

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

    unsigned int cubeVAO = renderCube(); 
    unsigned int sandTexture = loadTexture("../resources/textures/texture_map_all.jpg");
    // render loop
    // -----------
    float asd = 10;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sandTexture);

        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection    = glm::mat4(1.0f);

        // isometric projection
        float half_height = (float)*screen_height / 2.f;
        float aspect = (float)(800)/ (600);
        float half_width = (float)*screen_width /2.f;
        projection = glm::ortho(-half_width, half_width, -half_height, half_height, -1000.0f, 1000.0f);
        
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.3f));
        model = glm::scale(model, glm::vec3(500.0f));
        glBindVertexArray(cubeVAO);

        ourShader.setMat4("projection", projection);
        ourShader.setMat4("model", model);
        ourShader.setMat4("view", view);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    /*
    glDeleteVertexArrays(1, &terrainVAO);
    glDeleteBuffers(1, &terrainVBO);
    glDeleteBuffers(1, &terrainEBO);
    */

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
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
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
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
