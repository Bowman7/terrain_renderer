#ifndef TRIANGLELIST_H
#define TRIANGLELIST_H

#include<GL/glew.h>
#include<vector>

#include<cassert>
#include"math.h"

class Terrain;//forward declaration

class TriangleList {

 public:
  TriangleList(){};
  void createTriangleList(int width,int depth,const Terrain* pTerrain);
  void render();
 private:

  struct Vertex{
    Vector3f pos;

    void initVertex(const Terrain* pTerrain,int x,int z);
  };

  void createGLState();

  void populateBuffer(const Terrain* pTerrain);

  void InitVertices(const Terrain* pTerrain,std::vector<Vertex>& Vertices);
  void initVertex(const Terrain* pterrain,int x,int z);
  
  int m_width =0;
  int m_depth= 0;
  GLuint m_vao;
  GLuint m_vbo;
  GLuint m_ib;
};
#endif
