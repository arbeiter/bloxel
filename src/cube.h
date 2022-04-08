#include <glad/glad.h>
#include <random>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr int CHUNK_SIZE = 1;
struct Chunk {
    std::array<uint16_t, CHUNK_SIZE*CHUNK_SIZE> voxels;
};
struct Vertex {
    glm::vec3 position{0.0f};
    glm::vec2 texture{0.0f};
};
using VoxelFace = std::array<glm::vec3, 4>;
struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};

class Cube {

  int vertexCount = 0;
  int indices = 0;
  // unsigned int renderCube();
  // Mesh createChunkMesh(const Chunk& chunk);
  // void addFace(Mesh& mesh, const VoxelFace& face, glm::vec3 voxelPosition);
  const VoxelFace FRONT_FACE = {glm::vec3{1, 1, 1}, glm::vec3{0, 1, 1}, glm::vec3{0, 0, 1}, glm::vec3{1, 0, 1}};
  const VoxelFace LEFT_FACE = {glm::vec3{0, 1, 1}, {0, 1, 0}, {0, 0, 0}, {0, 0, 1}};
  const VoxelFace BACK_FACE = {glm::vec3{0, 1, 0}, {1, 1, 0}, {1, 0, 0}, {0, 0, 0}};
  const VoxelFace RIGHT_FACE = {glm::vec3{1, 1, 0}, {1, 1, 1}, {1, 0, 1}, {1, 0, 0}};
  const VoxelFace TOP_FACE = {glm::vec3{1, 1, 0}, {0, 1, 0}, {0, 1, 1}, {1, 1, 1}};
  const VoxelFace BOTTOM_FACE = {glm::vec3{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 0, 1}};
  std::array<glm::vec2, 4> textures = {glm::vec2{0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}};

  public:
  Cube() {}
  
  int numVertices() {
    return vertexCount * 3;
  }

  void addFace(Mesh& mesh, const VoxelFace& face, glm::vec3 voxelPosition) {
    for(int i = 0; i < 4; i++) {
      Vertex v;
      v.position = face[i] + voxelPosition;
      v.texture = textures[i];
      mesh.vertices.push_back(v);
    }
    mesh.indices.push_back(indices);
    mesh.indices.push_back(indices + 1);
    mesh.indices.push_back(indices + 2);
    mesh.indices.push_back(indices + 2);
    mesh.indices.push_back(indices + 3);
    mesh.indices.push_back(indices);
    indices += 4;
  }

  void printMesh(Mesh& mesh) {
    std::cout << "FACE" << std::endl;
    for(int i = 0; i < mesh.vertices.size(); i++) {
      glm::vec3 v = mesh.vertices[i].position;
      std::cout << "VERTICES " << " " << v[0] << v[1] << v[2] << std::endl;
    }
  }

  int indicesCount() {
    return indices;
  }

  Mesh createChunkMesh(const Chunk& chunk)
  {
      Mesh mesh;
      glm::vec3 voxelPosition = {0, 0,0};
      //addFace(mesh, LEFT_FACE, voxelPosition);
      //addFace(mesh, RIGHT_FACE, voxelPosition);
      //addFace(mesh, TOP_FACE, voxelPosition);
      //addFace(mesh, BOTTOM_FACE, voxelPosition);
      //addFace(mesh, BACK_FACE, voxelPosition);
      addFace(mesh, FRONT_FACE, voxelPosition);
      /*
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
      std::cout << indices << std::endl;
      */
      return mesh;
  }

  unsigned int renderCube()
  {
      Chunk chunk;
      chunk.voxels.fill(1);

      auto mesh = createChunkMesh(chunk);
      GLuint VBO = 0;
      GLuint cubeVAO = 0;
      GLuint EBO = 0;

      glGenVertexArrays(1, &cubeVAO);
      glBindVertexArray(cubeVAO);

      glGenBuffers(1, &VBO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

      glGenBuffers(1, &EBO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);

      // Experimental
      glVertexArrayVertexBuffer(cubeVAO, 0, VBO, 0, sizeof(Vertex));

      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, mesh.vertices.size() * sizeof(float), (void*)0);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, mesh.vertices.size() * sizeof(float), (void*)(3 * sizeof(float)));

      // Experimental
      glVertexArrayAttribBinding(cubeVAO, 0, 0);
      glVertexArrayAttribBinding(cubeVAO, 1, 0);
      glVertexArrayElementBuffer(cubeVAO, EBO);

      printMesh(mesh);
      vertexCount = mesh.vertices.size();
      return cubeVAO;
  }
};
