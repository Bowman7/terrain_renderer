#include<stdio.h>
#include<vector>

#include<stdio.h>
#include"trianglelist.h"
#include"math.h"
void TriangleList::createTriangleList(int width,int depth,const Terrain* pTerrain){

  m_width = width;
  m_depth = depth;

  createGLState();

  populateBuffer(pTerrain);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  
  
}

void TriangleList::createGLState(){

  glGenVertexArrays(1,&m_vao);
  glBindVertexArray(m_vao);

  glGenBuffers(1,&m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER,m_vbo);

  int POS_LOC = 0;


  printf("Size of Vertex is: %d ",sizeof(Vertex));
  size_t numFloats = 0;
  glVertexAttribPointer(POS_LOC,3,GL_FLOAT,GL_FALSE,
			3*sizeof(float),(const void*)(numFloats*sizeof(float)));
  numFloats +=3;
  glEnableVertexAttribArray(POS_LOC);
}

void TriangleList::populateBuffer(const Terrain* pTerrain){
  std::vector<Vertex> Vertices;
  Vertices.resize(m_width*m_depth);

  InitVertices(pTerrain,Vertices);

  glBufferData(GL_ARRAY_BUFFER,sizeof(Vertices[0])*Vertices.size(),&Vertices[0]
	       ,GL_STATIC_DRAW);
}

void TriangleList::Vertex::initVertex(const Terrain* pTerrain,int x,int z){
  pos = Vector3f(x,0.0f,z);
  
}
void TriangleList::InitVertices(const Terrain* pTerrain,
				std::vector<Vertex>&Vertices){
  int index =0;

  for(int x =0;x<m_depth;x++){
    for(int z=0;z<m_width;z++){
      assert(index<Vertices.size());
      Vertices[index].initVertex(pTerrain,x,z);
      index++;
    }
  }
  
}

void TriangleList::render(){

 
  glBindVertexArray(m_vao);
  glDrawArrays(GL_POINT,0,m_depth*m_width);
  glBindVertexArray(0);
}
