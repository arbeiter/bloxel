## Phase 1:

Implement loadTexture

- Triangle strip experiments
  - Color triangle strip single color
  - Color co-ordinates
  - Texture co-ordinates
  - Blend textures on two levels

## Glescraft

class Chunk {
  vector<vector<vector> blk;
  GLuint vbo;
  bool changed;

  Chunk() {
    memset(blk, 0, sizeof(blk));
    glGenBuffers(1, &vbo);
  }
  ~Chunk() {
    glDeleteBuffers(1, &vbo);
  }

  uint8_t get(int x, int y, int z) {
    return blk[x][y][z];
  }

  uint8_t set(int x, int y, int z, uint8_t type) {
    blk[x][y][z] = type;
    changed = true;
  }

  void update() {
    changed = false;
    byte4 vertex[CX * CX * CZ * 6 * 6];
    for(int x = 0; x < CZ; x++) {
      for(int x = 0; x < CZ; x++) {
        for(int x = 0; x < CZ; x++) {
          vertex[i++] ---> byte....
        }
      }
    }

    CubeFace stuff
    elements = i;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, elements * sizeof *vertex, vertex, GL_STATIC_DRAW);
  }

  void draw(va, ib) {
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
  } 

  void render() {
    if(changed) {
      update();
    }

    if(!elements) {
      return;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attribute_coord, 4, GL_BYTE, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, elements);
  }
}

TryAddBlock(x, y, z) {
  block = GetBlock(x, y, z)
  frontFace -> Arr[12]
  TryAddFace(frontFace, texCoords.front, position, Adjacent block: {x, y, z-1})
}
### SolvingGame

Mesh {
  GetVBO();
  GetIBO();
  GetVAO();
  GetLayout();
  AddFace(blockFace, texCoords, position, light) {
    countVertices = m_vertices/nbElementPerLayout
    mVertices.push((float)position.x + blockFace[i]);
    mVertices.push((float)position.y + blockFace[i+1]);
    mVertices.push((float)position.z + blockFace[i+2]);
    mVertices.push_back(texCoords[i/3].x);
    mVertices.push_back(texCoords[i/3].y);
  }
  m_Indices.push_back(countVertices);
  m_Indices.push_back(countVertices);
  m_Indices.push_back(countVertices);
  m_Indices.push_back(countVertices);
  m_Indices.push_back(countVertices);
}

Chunk {
  TryAddBlock
  TryAddFace(blockFace, texCoords, position, light)
}

Block {
  TexCoords left, front, right, bottom, top
}
