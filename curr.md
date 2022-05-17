std::vector<float> vertices;
float yScale = 64.0f / 256.0f;
float yShift = 16.0f;
int height = 800;
int width = 600;
int NUM_VERTS_PER_STRIP = width * 2;
int NUM_STRIPS = height - 1;

for(int i = 0; i < height; i++) {
  for(int j = 0; j < width; j++) {
    // generate random
    // float random = random numnber in range 0, MAX
    vertices.push_back( -height/2.0f + height*i/(float)height );
    vertices.push_back( (int) random * yScale - yShift );
    vertices.push_back( -width/2.0f + width*j/(float)width );
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

GLUint terrainVBO, terrainVAO, terrainEBO;
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

glBindVertexArray(terrainVAO);
for(unsigned int strip = 0; strip < NUM_STRIPS; ++strip)
{
  glDrawElements(GL_TRIANGLE_STRIP,
                 NUM_VERTS_PER_STRIP,
                 GL_UNSIGNED_INT,
                 (void *)(sizeof(unsigned int) * NUM_VERTS_PER_STRIP * strip)
                 );

}

```
#version 330 core
layout (location = 0) in vec3 aPos;

out float Height;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
niform mat4 projection;

void main()
{
    Height = aPos.y;
    Position = (view * model * vec4(aPos, 1.0)).xyz;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#version 330 core

out vec4 FragColor;

in float Height;

void main()
{
    float h = (Height + 16)/32.0f;	// shift and scale the height in to a grayscale value
    FragColor = vec4(h, h, h, 1.0);
}

#include <random>
```

### Links

https://gamedev.stackexchange.com/questions/74044/how-to-efficiently-render-a-large-terrain-mesh
https://gamedev.stackexchange.com/questions/71760/terrain-multi-texturing
http://www.lighthouse3d.com/opengl/terrain/
https://blog.runevision.com/2016/03/note-on-creating-natural-paths-in.html
