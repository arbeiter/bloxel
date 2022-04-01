#include <glad/glad.h>
#include <random>
#include <GLFW/glfw3.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <array>
#include <stb_image.h>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

unsigned int renderCube();

constexpr int CHUNK_SIZE = 128;
int indices = 0;

struct Vertex {
    glm::vec3 position{0.0f};
    glm::vec2 texture{0.0f};
};

struct Mesh {
    std::vector<Vertex> vertices;
};

struct Chunk {
    std::array<uint16_t, CHUNK_SIZE*CHUNK_SIZE> voxels;
};

Mesh createChunkMesh(const Chunk& chunk);

using VoxelFace = std::array<glm::vec3, 4>;
const VoxelFace FRONT_FACE = {glm::vec3{1, 1, 1}, {0, 1, 1}, {0, 0, 1}, {1, 0, 1}};
const VoxelFace LEFT_FACE = {glm::vec3{0, 1, 1}, {0, 1, 0}, {0, 0, 0}, {0, 0, 1}};
const VoxelFace BACK_FACE = {glm::vec3{0, 1, 0}, {1, 1, 0}, {1, 0, 0}, {0, 0, 0}};
const VoxelFace RIGHT_FACE = {glm::vec3{1, 1, 0}, {1, 1, 1}, {1, 0, 1}, {1, 0, 0}};
const VoxelFace TOP_FACE = {glm::vec3{1, 1, 0}, {0, 1, 0}, {0, 1, 1}, {1, 1, 1}};
const VoxelFace BOTTOM_FACE = {glm::vec3{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 0, 1}};
std::array<glm::vec2, 4> textures = {glm::vec2{0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}};

void addFace(Mesh& mesh, const VoxelFace& face, glm::vec3 voxelPosition);
void addFace(Mesh& mesh, const VoxelFace& face, glm::vec3 voxelPosition) {
  for(int i = 0; i < 4; i++) {
    Vertex v;
    v.position = face[i] + voxelPosition;
    v.texture = textures[i];
    mesh.vertices.push_back(v);
  }
  indices += 4;
}

int indicesCount() {
  return indices;
}

Mesh createChunkMesh(const Chunk& chunk)
{
    Mesh mesh;
    for (int y = 0; y < CHUNK_SIZE; y++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            for (int x = 0; x < CHUNK_SIZE; x++) {
              glm::vec3 voxelPosition = {x, y, z};
              addFace(mesh, LEFT_FACE, voxelPosition);
              addFace(mesh, RIGHT_FACE, voxelPosition);
              addFace(mesh, TOP_FACE, voxelPosition);
              addFace(mesh, BOTTOM_FACE, voxelPosition);
              addFace(mesh, BACK_FACE, voxelPosition);
              addFace(mesh, FRONT_FACE, voxelPosition);
            }
        }
    }
    return mesh;
}

unsigned int renderCube(Mesh &mesh)
{
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.vertices), mesh.vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return cubeVAO;
}
