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

unsigned int renderCube();

unsigned int renderCube()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float wrap = 0.142f;

    float top_left_x, top_left_y;
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

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  wrap, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  wrap, wrap,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  wrap, wrap,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  wrap,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  wrap,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  wrap,  wrap,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  wrap,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  wrap,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  wrap,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  wrap,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  wrap,  wrap,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  wrap,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  wrap,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  wrap,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  wrap,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  wrap, wrap,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  wrap,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  wrap,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  wrap,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  wrap,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  wrap,  wrap,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  wrap,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  wrap,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  wrap
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
