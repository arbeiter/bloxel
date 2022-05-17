#include <glad/glad.h>
#include <src/shader.h>
#include <src/logger.hpp>
#include <src/fastnoiselite.h>
#include <random>
#include <vector>
#include <map>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Bloxel 
{
    #define SCX 3
    #define SCY 3
    #define SCZ 3

    using VoxelFace = std::array<glm::vec3, 4>;
    typedef std::array<glm::vec2, 4> TextureArray;
    const VoxelFace FRONT_FACE = {glm::vec3{1, 1, 1}, glm::vec3{0, 1, 1}, glm::vec3{0, 0, 1}, glm::vec3{1, 0, 1}};
    const VoxelFace LEFT_FACE = {glm::vec3{0, 1, 1}, glm::vec3{0, 1, 0}, glm::vec3{0, 0, 0}, glm::vec3{0, 0, 1}};
    const VoxelFace BACK_FACE = {glm::vec3{0, 1, 0}, glm::vec3{1, 1, 0}, glm::vec3{1, 0, 0}, glm::vec3{0, 0, 0}};
    const VoxelFace RIGHT_FACE = {glm::vec3{1, 1, 0}, glm::vec3{1, 1, 1}, glm::vec3{1, 0, 1}, glm::vec3{1, 0, 0}};
    const VoxelFace TOP_FACE = {glm::vec3{1, 1, 0}, glm::vec3{0, 1, 0}, glm::vec3{0, 1, 1}, glm::vec3{1, 1, 1}};
    const VoxelFace BOTTOM_FACE = {glm::vec3{0, 0, 0}, glm::vec3{1, 0, 0}, glm::vec3{1, 0, 1}, glm::vec3{0, 0, 1}};

    struct textureCoords {
      float top_left_x;
      float top_left_y;
      float top_right_x;
      float top_right_y;
      float bottom_left_x;
      float bottom_left_y;
      float bottom_right_x;
      float bottom_right_y;
    };

    struct Position {
      int x;
      int y;
      int z;
      Position(int x, int y, int z): x(x), y(y), z(z) {}
      bool operator<(const Position &pos) const {
        return x < pos.x || ( x == pos.x && y < pos.y ) 
                         || ( x == pos.x && y == pos.y && z < pos.z);
      }
    };

    enum class texture_type {
      grass = 0, stone = 1, air = 2
    };
    enum class BlockFace {
      front= 0, back = 1, left = 2, right = 3, top = 4, bottom = 5
    };

    constexpr int CX = 2;
    constexpr int CY = 2;
    constexpr int CZ = 2;
    struct Vertex {
        glm::vec3 position{0.0f};
        glm::vec2 texture{0.0f};
    };

    struct Mesh {
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
    };

    class TextureAtlas {
      // TODO: Look up how to get image height and image width from STBI_IMAGE
      private:
      std::map<BlockFace, int> blockFaceMap = { 
          {BlockFace::front, 1}, 
          {BlockFace::back, 1}, 
          {BlockFace::left, 1}, 
          {BlockFace::right, 1}, 
          {BlockFace::top, 0}, 
          {BlockFace::bottom, 2}
      };
      std::map<texture_type, int> textureRowMap = {
          {texture_type::grass, 0}, 
          {texture_type::stone, 1}, 
      };

      int num_characters_per_row = 3;  // should be named num_rows
      int num_characters_per_col = 2;  // should be named num_cols
      float character_w = (float)(1.0f / 3.0f);
      float character_h = (float)(1.0f / 2.0f);

      public:
      TextureAtlas() {}

      int getRow(texture_type ttype) {
        return textureRowMap[ttype];
      }

      int getColumn(BlockFace face) {
        //std::cout << "FACE " << static_cast<int>(face) << std::endl;
        return blockFaceMap[face];
      }

      struct textureCoords sampleFromSpritesheet(int row, int col) {
        //row is texture_type, col indicates block fac10e
        float top_left_x = (float)(col) * character_w;
        float top_left_y = (float)(row) * character_h;

        struct textureCoords coords = coordsFromTopLeft(top_left_x, top_left_y);
        //displayTextureCoords(coords);
        return coords;
      }

      struct textureCoords sampleFromSpritesheet(int pos) {
        int character_row = pos / num_characters_per_row;
        int character_column = pos % num_characters_per_row;
        float pos_y = (float)(character_row * character_h);
        float pos_x = (float)(character_column * character_w);
        struct textureCoords coords = coordsFromTopLeft(pos_x, pos_y);
        return coords;
      }

      struct textureCoords coordsFromTopLeft(float x, float y) {
        float top_left_x = x;
        float top_left_y = y;
        float top_right_x = top_left_x + character_w;
        float top_right_y = top_left_y;
        float bottom_left_x = top_left_x;
        float bottom_left_y = top_left_y + character_h;
        float bottom_right_x = top_left_x + character_w;
        float bottom_right_y = top_left_y + character_h;
        struct textureCoords coords = {top_left_x, top_left_y, top_right_x, top_right_y, bottom_left_x, bottom_left_y, bottom_right_x, bottom_right_y };
        return coords;
      }

      void displayTextureCoords(struct textureCoords coords) {
        std::cout << "TOP LEFT X Y" << coords.top_left_x << " " << coords.top_left_y;
        std::cout << "TOP RIGHT X Y" << coords.top_right_x <<" " <<  coords.top_right_y;
        std::cout << "BOTTOM LEFT X Y" << coords.bottom_left_x << " " << coords.bottom_left_y;
        std::cout << "BOTTOM RIGHT X Y" << coords.bottom_right_x << " " << coords.bottom_right_y;
        std::cout << std::endl;
    }
    };

    class Renderable {
      int startX, startY, startZ;

      public:
      Renderable(Position pos) {
        startX = pos.x;
        startY = pos.y;
        startZ = pos.z;
      }

      bool isRenderable(int x, int y, int z, std::map<Position, int> chunkPosMap) {
        Position absPosition = {x, y, z};
        if(chunkPosMap[absPosition] == 2) {
          //printf("SKIPPED AIR\n");
          return false;
        }
        std::vector<Position> allNeighbors = getNeighbors(absPosition.x, absPosition.y, absPosition.z);

        if(allNeighbors.size() < 26) {
          return true;
        }

        // if all != air, return false
        // return true
        for(auto neighbor: allNeighbors) {
          Position pos = {neighbor.x, neighbor.y, neighbor.z};
          if(chunkPosMap[pos] == 2) {
            return true;
          }
        }
        return false;
      }

      bool validPosition(int i, int j, int k) {
        int max_i = SCX * CX - 1;
        int max_j = SCY * CY - 1;
        int max_k = SCZ * CZ - 1;

        if(i < 0 || j < 0 || k < 0)  {
          return false;
        }
        if(i > max_i ||  j > max_j || k > max_k )  {
          return false;
        }

        return true;
      }

      // Takes in absolute super chunk co-ordinates
      std::vector<Position> getNeighbors(int i, int j, int k) {
        std::vector<Position> all_elems;
        int tx = i-1;
        int ty = j-1;
        int tz = k-1;
        int curr_x, curr_y, curr_z;
        curr_x = tx;
        curr_y = ty;
        curr_z = tz;

        for(int x = 0; x < 3; x++) {
          for(int y = 0; y < 3; y++) {
            for(int z = 0; z < 3; z++) {
              curr_x = tx + x;
              curr_y = ty + y;
              curr_z = tz + z;

              if(curr_x == i && curr_y == j && curr_z == k) 
                continue;

              if(validPosition(curr_x, curr_y, curr_z))
                all_elems.push_back({curr_x, curr_y, curr_z});
            }
          }
        }

        return all_elems;
      }

      Position computeAbsolutePosition(int x, int y, int z) {
        // x = 1
        // SCX = 0 1 2
        int absX =  startX * SCX + x;
        int absY = startY * SCY + y;
        int absZ = startZ * SCZ + z;
        Position pos = { absX, absY, absZ };
        return pos;
      }
    };

    class Cube {
      texture_type blockType;
      texture_type blocks[CX][CY][CZ];
      int vertexCount = 0;
      int indices = 0;
      TextureArray textures;
      int startX;
      int startY;
      int startZ;
      GLuint VBO = 0;
      GLuint cubeVAO = 0;
      GLuint EBO = 0;
      float width;
      float height;
      int scaleFactor;
      std::map<Position, int> chunkPosMap {};
      Renderable renderable;
      TextureAtlas textureAtlas;

      public:
      Cube(Position pos, float width, float height, int scaleFactor) :renderable { Renderable(pos) }, textureAtlas { TextureAtlas() }
      {
        startX = pos.x;
        startY = pos.y;
        startZ = pos.z;
        blockType = texture_type::grass;
        memset(blocks, 0, sizeof(blocks));
      }

      TextureArray getTexture(texture_type ttype, BlockFace blockFace) {
        int row = textureAtlas.getRow(ttype);
        int column = textureAtlas.getColumn(blockFace);
        //std::cout << "Get Texture " << row << " " << column << " " << static_cast<int>(ttype) << std::endl;

        // 0 1
        struct textureCoords coords = textureAtlas.sampleFromSpritesheet(row, column);
        textures = {glm::vec2{coords.top_left_x, coords.top_left_y}, 
                    glm::vec2{coords.top_right_x, coords.top_right_y}, 
                    glm::vec2{coords.bottom_left_x, coords.bottom_left_y}, 
                    glm::vec2{coords.bottom_right_x, coords.bottom_right_y}};
        return textures;
      }

      
      int numVertices() {
        return vertexCount * 3;
      }

      void setVoxel(Position &voxelPosition, texture_type blockType) {
        blocks[voxelPosition.x][voxelPosition.y][voxelPosition.z] = blockType;
      }

      texture_type getVoxel(Position &voxelPosition) {
        return blocks[voxelPosition.x][voxelPosition.y][voxelPosition.z];
      }

      void addFace(Mesh& mesh, const VoxelFace& face, Position voxelPosition, BlockFace blockFace) {
        texture_type ttype = getVoxel(voxelPosition);
        TextureArray textures = getTexture(ttype, blockFace);

        glm::vec3 voxelPos = glm::vec3(voxelPosition.x, voxelPosition.y, voxelPosition.z);
        for(int i = 0; i < 4; i++) {
          Vertex v;
          v.position = face[i] + voxelPos;
          v.texture = textures[i];
          mesh.vertices.push_back(v.position[0]);
          mesh.vertices.push_back(v.position[1]);
          mesh.vertices.push_back(v.position[2]);

          mesh.vertices.push_back(v.texture[0]);
          mesh.vertices.push_back(v.texture[1]);
        }

        mesh.indices.push_back(indices);
        mesh.indices.push_back(indices + 1);
        mesh.indices.push_back(indices + 2);
        mesh.indices.push_back(indices + 2);
        mesh.indices.push_back(indices + 3);
        mesh.indices.push_back(indices);
        indices += 4;
      }

      int indicesCount() {
        return indices;
      }

      void setChunkPosMap(std::map<Position, int> posMap) {
        chunkPosMap = posMap;
      }

      // Important TODO: Move this to super chunk, this is not optimal
      // Roadmap: Use SSBOs to render chunks
      Mesh createChunkMesh()
      {
          //printf("Start pos %d %d %d\n", startX, startY, startZ);
          Mesh mesh;
          int endY = startY + CY;
          int endX = startX + CX;
          int endZ = startZ + CZ;
          for (int y = startY; y < endY; y++) {
              for (int z = startZ; z < endZ; z++) {
                  for (int x = startX; x < endX; x++) {
                    Position voxelPosition = {x, y, z};
                    bool toRender = renderable.isRenderable(x, y, z, chunkPosMap);
                    if(toRender) {
                      addFace(mesh, LEFT_FACE, voxelPosition, BlockFace::left);
                      addFace(mesh, RIGHT_FACE, voxelPosition, BlockFace::right);
                      addFace(mesh, TOP_FACE, voxelPosition, BlockFace::top);
                      addFace(mesh, BOTTOM_FACE, voxelPosition, BlockFace::bottom);
                      addFace(mesh, FRONT_FACE, voxelPosition, BlockFace::front);
                      addFace(mesh, BACK_FACE, voxelPosition, BlockFace::back);
                    } else {
                      //printf("%d %d %d Skipped Render\n", voxelPosition.x, voxelPosition.y, voxelPosition.z);
                    }
                  }
              }
          }
          //printf("After Creating Chunk Mesh %d\n", mesh.vertices.size());
          return mesh;
      }

      void renderCube(Shader& ourShader, glm::mat4 view, float screen_w, float screen_h) {
          glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
          model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.3f));
          model = glm::scale(model, glm::vec3((float)40));

          glm::mat4 projection    = glm::mat4(1.0f);
          screen_w = screen_w/2.0f;
          screen_h = screen_h/2.0f;

          projection = glm::ortho(-screen_w, screen_w, -screen_h, screen_h, -1000.0f, 1000.0f);
          ourShader.setMat4("projection", projection);
          ourShader.setMat4("model", model);
          ourShader.setMat4("view", view);

          glBindVertexArray(cubeVAO);
          glDrawElements(GL_TRIANGLES, 5 * indicesCount(), GL_UNSIGNED_INT, 0);
      }

      // TODO: Implement SSBOs to push to versus using multiple draw calls
      unsigned int generateCubeVAO()
      {
          auto mesh = createChunkMesh();

          glGenVertexArrays(1, &cubeVAO);
          glBindVertexArray(cubeVAO);

          glGenBuffers(1, &VBO);
          glBindBuffer(GL_ARRAY_BUFFER, VBO);
          glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

          glGenBuffers(1, &EBO);
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
          glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);

          glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
          glEnableVertexAttribArray(0);
          glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
          glEnableVertexAttribArray(1);

          vertexCount = mesh.vertices.size();
          return cubeVAO;
      }
    };

    typedef std::vector<Cube *> v1d;
    typedef std::vector<v1d> v2d;
    typedef std::vector<v2d> v3d;

    class SuperChunk {
      int rows = SCX;
      int cols = SCY;
      int breadths = SCZ;
      v3d superChunk;
      glm::mat4 view;
      float w;
      float h;
      int sFactor;
      std::map<Position, int> chunkPosMap {};

      public:
      SuperChunk(float width, float height, int scaleFactor)  {
        h = height;
        w = width;
        sFactor = scaleFactor;

        Position pos = { 0, 0, 0};
        superChunk = v3d(rows, v2d(cols, v1d(breadths, new Cube(pos, w, h, sFactor))));
        for(int i = 0; i < rows; i++) {
          for(int j = 0; j < cols; j++) {
            for(int k = 0; k < breadths; k++) {
              Position pos = {i, j, k};
              superChunk[i][j][k] = new Cube(pos, w, h, sFactor);
            }
          }
        }
      }

      Cube* get(int x, int y, int z) {
        return superChunk[x][y][z];
      }

      void generateMeshes() {
        for(int i = 0; i < rows; i++) {
          for(int j = 0; j < cols; j++) {
            for(int k = 0; k < breadths; k++) {
              Cube* cube = get(i, j, k);
              cube->setChunkPosMap(chunkPosMap);
              cube->generateCubeVAO();
            }
          }
        }
      }

      void render(Shader& ourShader, glm::mat4 view, float w, float h) {
        for(int i = 0; i < rows; i++) {
          for(int j = 0; j < cols; j++) {
            for(int k = 0; k < breadths; k++) {
              Cube* cube = get(i, j, k);
              cube->renderCube(ourShader, view, w, h);
            }
          }
        }
      }

      void flood_fill_chunk(int x, int y, int z, int abs_height) {
          Cube *chunk = get(x, y, z);

          for(int cx = 0; cx < CX; cx++){
            for(int cy = 0; cy < CY; cy++){
              for(int cz = 0; cz < CZ; cz++){
                int startPosX = x * CX;
                int startPosY = y * CY;
                int startPosZ = z * CZ;
                int absPosY = startPosY + cy;
                Position relativePos = { cx, cy, cz };
                Position absolutePos = { startPosX + cx, absPosY, startPosZ + cz };
                texture_type ttype = getTextureFromHeight(absPosY);
                if(absPosY > abs_height) {
                  ttype = texture_type::air;
                }
                chunkPosMap[absolutePos] = static_cast<int>(ttype); 
                chunk->setVoxel(relativePos, ttype);
              }
            }
          }
      }

      void addWall() {
        breadths+=1;
        for(int i = 0; i < rows; i++) {
          for(int j = 0; j < cols; j++) {
            Position pos = {i*CX, j*CY, breadths*CZ};
            superChunk[i][j].push_back(new Cube(pos, w, h, sFactor));
          }
        }
      }

      texture_type getTextureFromHeight(int h) {
        //std::cout << "Get Texture From Height" << h << std::endl;
        if(h < 20) {
          //std::cout << "Texture type stone";
          return texture_type::stone;
        }
        if(h < 60 && h >= 20) {
          //std::cout << "Texture type grass";
          return texture_type::grass;
        }
        return texture_type::air;
      }


      void displayChunkMap() {
        for(const auto& elem: chunkPosMap) {
          Position pos = elem.first;
          std::cout << "POS " << pos.x << " " << pos.y << " " << pos.z << std::endl;
          std::cout << "VAL " << elem.second << std::endl;
        }
      }
    };

    using namespace bloxel::logger;

    class TerrainGen {
      SuperChunk sc;
      int heightmap[SCX*CX][SCZ*CZ];

      public:
      TerrainGen(float width, float height, int scaleFactor): sc { SuperChunk(width, height, scaleFactor) } {
      }

      SuperChunk getSuperChunk() {
        return sc;
      }

      void generateMeshes() {
        sc.generateMeshes();
      }

      void render(Shader& shader, glm::mat4 view, float w, float h) {
        sc.render(shader, view, w, h);
      }

      void crudeHeightGen() {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(0, SCY*CY);

        for(int x = 0; x < SCX; x++) {
         for(int z = 0; z < SCZ; z++) {
           for(int y = 0; y < SCY; y++) {
              int k = int(dist(mt));
              sc.flood_fill_chunk(x, y, z, k);
           }
          }
        }
      }

      void noiseHeightGen() {
        FastNoiseLite* noise = new FastNoiseLite();
        noise -> SetNoiseType(noise->NoiseType::NoiseType_Perlin);
        noise -> SetFrequency(0.01f);
        noise -> SetFractalLacunarity(2.0f);
        noise -> SetFractalGain(0.5f);
        noise -> SetFractalType(noise->FractalType::FractalType_FBm);

        // Generate heightmap
        int xmax = SCX*CX;
        int zmax = SCZ*CZ;
        for(int i = 0; i < xmax; i++) {
          for(int j = 0; j < zmax; j++) {
            // generate random
            float x = -xmax/2.0f + xmax*i/(float)xmax;
            float z = -zmax/2.0f + zmax*j/(float)zmax;
            float y_noise = noise -> GetNoise((float)x, (float)z);
            float y = std::abs(y_noise * 400);
            heightmap[i][j] = std::min(y, (float)SCY*CY);
          }
        }

        //Use heightmap to generate data
        /*
          SuperChunk.renderHeightMap(heightMap) {
            for i = 0 to xmax
              for j = 0 to zmax
                curr_height = heightmap[i][j]
                Cube* cube = get(i, j, k);
                cube->setChunkPosMap(chunkPosMap);
                cube->generateCubeVAO();
          }
          // Create a super mesh to reduce draw calls
          SuperChunk.render(mesh) {
          for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
              for(int k = 0; k < breadths; k++) {
                tempMesh
                Cube* cube = get(i, j, k);
                cube->setChunkPosMap(chunkPosMap);
                cube->addToMesh();
            }
          }
        }
        */
        logHeightMapToFile();
      }

      void logHeightMapToFile() {
        Log log = Log();
        std::string log_string = log.construct_log_from_height_map((int *)heightmap, SCX*CX, SCZ*CZ);
        log.log_message(log_string);
      }

      void display() {
        sc.displayChunkMap();
      }
    };
}
