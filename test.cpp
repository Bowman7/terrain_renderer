#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<cmath>
#include"shader.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#define WIDTH 800
#define HEIGHT 800

float vertices[]{
  -0.5f,-0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    0.0f,0.5f,0.0f
    };
float box_vertices[]{
  //pos            //colors
  -0.5f,0.5f,0.0f,  1.0f,0.0f,0.0f,//tleft
    0.5f,0.5f,0.0f, 0.0f,1.0f,0.0f,//tright
    -0.5f,-0.5f,0.0f, 0.0f,0.0f,1.0f,//bleft
    0.5f,-0.5f,0.0f , 0.0f,0.0f,0.0f//bright
    };
unsigned int indices[] {
  0,1,2,
    1,3,2
    };

class Terrain{
public:
  Terrain();
  ~Terrain(){
    glfwTerminate();
  }
  void createTerrain();
  void render();
  void init(){
    createWindow();
    createTerrain();
  }
  void run(){
    //draw
    while(!glfwWindowShouldClose(window)){

      //render scene
      render();
      //input
      handleInput(window);
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }
private:
  void createWindow(){
    //intialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
 
    //initalize window
    window = glfwCreateWindow(WIDTH,HEIGHT,"window",NULL,NULL);
     if(window == NULL){
      std::cout<<"Failed to initialize window"<<std::endl;
      glfwTerminate();
    }
    
    glfwMakeContextCurrent(window);
    
    //initialize glew
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
      printf("Failed to initialize glew\n");
    }
    //setup viewport
    glViewport(0,0,WIDTH,HEIGHT);
  }
private:
  
  GLFWwindow* window =NULL;
  //shader
  shader ourShader;
  void handleInput(GLFWwindow* window);
  unsigned int VAO,VBO,EBO;
  
};

Terrain::Terrain(): ourShader("shader/shader.vert","shader/shader.frag"){
}
void Terrain::createTerrain(){
  //VAO AND VBO stuff

  //unsigned int VAO;
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);
  //unsigned int VBO;
  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(box_vertices),box_vertices,GL_STATIC_DRAW);

  //unsigned int EBO;
  glGenBuffers(1,&EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
  //link vertex attribute for pso and color
  //position attrib
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  //color
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3 *sizeof(float)));
  glEnableVertexAttribArray(1);
  
  

  //polygon mode
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;



  //Translation stuff
  glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::translate(trans,glm::vec3(1.0f,1.0f,0.0f));
  vec = trans*vec;
  std::cout<<" vec: "<<vec.x<<vec.y<<vec.z<<vec.w<<std::endl;
  
}
void Terrain::render() {
   
    //render
    glClearColor(0.1f,0.1f,0.2f,1.0f);//maroon
    glClear(GL_COLOR_BUFFER_BIT);
    //use the shader program
    //glUseProgram(shaderProgram);
    ourShader.use();
    //change color of uniform box
    float timeValue = glfwGetTime();
    float redValue = sin(timeValue)/2.0f ;
    //float greenValue = sin(timeValue)/2.0f ;
    float blueValue = sin(timeValue)/2.0f ;
    int vertexColorLocation = glGetUniformLocation(ourShader.ID,"ourColor");
    glUniform4f(vertexColorLocation,redValue,0.0f,blueValue,1.0f);
    
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES,0,3);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

void Terrain::handleInput(GLFWwindow* window){
  if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window,true);
  }
}
int main() {
  Terrain terrain;
  terrain.init();
  terrain.run();

  
 
  return 0;
}
