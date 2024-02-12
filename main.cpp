#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<cmath>

#include"shader.h"
#include"include/array2d.h"
#include"include/ogldev_util.h"
#include"trianglelist.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

#define WIDTH 800
#define HEIGHT 800


class Terrain{
public:
  Terrain(){};
  void createWindow();
  void run();
  void handleInput(GLFWwindow* window);
  void createBox();
  void renderBox();
  void events();
  void LoadFromFile(const char* pFilename);
  void initTerrain();
  void LoadHeightMapFile(const char* pFilename);
  void createCamera();
  void mouse_callback();
  void getMousePos();
private:
  GLFWwindow* window = NULL;
  
  void initGlfw();
  void initGlew();
  unsigned int VAO,VBO,EBO;
  unsigned int ID;
  unsigned int t_ID;
  unsigned int texture,texture2;
  int width,height,nrChannels;
  glm::mat4 trans;

  int m_terrainSize = 0;
  Array2D<float> m_heightMap;
  TriangleList triangleList;
  float bx_vertices[32] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
  float box_vertices[32]{
  //pos            //colors           //texture
    -0.5f,0.5f,0.0f,  1.0f,0.0f,0.0f,   0.0f,1.0f,//tleft
      0.5f,0.5f,0.0f, 0.0f,1.0f,0.0f,     1.0f,1.0f,  //tright
      -0.5f,-0.5f,0.0f, 0.0f,0.0f,1.0f,   0.0f,0.0f, //bleft
      0.5f,-0.5f,0.0f , 0.0f,0.0f,0.0f,   1.0f,0.0f//bright
    };
  
  unsigned int indices[6] {
  0,1,2,
    1,3,2
    };
  //float basic triangle
  float basic_triangle[9]={
    0.0f,0.5f,0.0f, 
    -0.5f,0.0f,0.0f,
    0.5f,0.0f,0.0f,
  };
  unsigned int basic_indices[3]={
    0,1,2
  };
  //triangle
  float triangle[72] = {
    //first face     //color       
    0.0f,0.5f,0.0f, 0.0f,1.0f,0.0f,//top
    -0.5f,0.0f,0.0f, 1.0f,0.0f,0.0f,//left
    0.5f,0.0f,0.0f,  0.0f,0.0f,1.0f,//right
    
    //2nd face
    0.0f,0.5f,0.0f, 0.0f,1.0f,0.0f,//top
    0.5f,0.0f,0.0f,  0.0f,1.0f,0.0f,//left
    0.0f,0.0f,-0.5f,  0.0f,0.0f,1.0f,//right
    //3rd face
     0.0f,0.5f,0.0f, 1.0f,0.0f,0.0f,//top
     0.0f,0.0f,0.5f,  0.0f,1.0f,0.0f,//left
     -0.5f,0.0f,0.0f, 0.0f,0.0f,1.0f,//left
     //4th
     -0.5f,0.0f,0.0f, 1.0f,0.0f,0.0f,
     0.5f,0.0f,0.0f,  0.0f,1.0f,0.0f,
     0.0f,0.0f,-0.5f ,0.0f,0.0f,1.0f
  };
  unsigned int  triangle_indices[12]={
    0,1,2,
    0,2,5,
    0,5,1,
    1,2,5
  };
  float cube_vertices[180] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
  glm::vec3 cubepos[2]={
    glm::vec3(0.0f,0.0f,0.0f),
    glm::vec3(1.0f,1.0f,-3.0f)
  };

  //camera variables
  glm::vec3 cameraPos;
  glm::vec3 cameraFront;
  glm::vec3 cameraUp;
  float FOV;
  float zNear;
  float zFar;
  float deltaTime;
  float lastFrame;
  //for cam
  double lastX;
  double lastY;
  bool firstMouse;
  float yaw;
  float pitch;
  double xPos;
  double yPos;
  //for position
  glm::mat4 proj;
};

void Terrain::createCamera() {

  
  //define perspective projection
  proj = glm::perspective(glm::radians(FOV),
				    (float)WIDTH/(float)HEIGHT,zNear,zFar);
  
  int projectionLoc = glGetUniformLocation(ID,"projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(proj));

}

void Terrain::LoadFromFile(const char* pFilename){
  
  shader terrainShader("shader/tshader.vert","shader/tshader.frag");
  t_ID = terrainShader.ID;
  
  LoadHeightMapFile(pFilename);
  triangleList.createTriangleList(m_terrainSize,m_terrainSize,this);
  


  glm::mat4 t_proj = glm::perspective(glm::radians(FOV),
				    (float)WIDTH/(float)HEIGHT,zNear,zFar);
  int mat = glGetUniformLocation(t_ID,"gVP");
  glUniformMatrix4fv(mat, 1, GL_FALSE, glm::value_ptr(t_proj));

  
}
void Terrain::LoadHeightMapFile(const char* pFilename){
  int FileSize = 0;
  unsigned char* p = (unsigned char*)ReadBinaryFile(pFilename,FileSize);
  //check filesize for floating points
  //assert(FileSize % sizeof(float)==0);

  m_terrainSize = sqrt(FileSize/sizeof(float));
  std::cout<<"Terrain size: "<<m_terrainSize<<std::endl;

  m_heightMap.InitArray2D(m_terrainSize,m_terrainSize,p);//takes a pre allocated buffer
  
  //m_heightMap.printFloat();
}
//render box
void Terrain::renderBox(){

  glClearColor(0.1f,0.1f,0.2f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glActiveTexture(GL_TEXTURE0);//activate texture
  glBindTexture(GL_TEXTURE_2D,texture);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D,texture2);

  glUseProgram(ID);

  glm::mat4 view = glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
  
  int viewLoc = glGetUniformLocation(ID,"view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
  
  glBindVertexArray(VAO);
  glm::mat4 model = glm::translate(model,glm::vec3(0.0f,0.0f,0.0f));
  int modelLoc = glGetUniformLocation(ID,"model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
  glDrawArrays(GL_TRIANGLES,0,36);
  
 
  glBindVertexArray(0);
}
void Terrain::events(){
  
  //createBox();

  
  LoadFromFile("heightmap.save");
  //render
  //shader terrainShader("shader/tshader.vert","shader/tshader.frag");
  
}
//create box
void Terrain::createBox(){
  //compiel shader
  shader ourShader("shader/shader.vert","shader/shader.frag");
  ID = ourShader.ID;
  
  //gen vao
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(cube_vertices),cube_vertices,GL_STATIC_DRAW);

  glGenBuffers(1,&EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,
	       GL_STATIC_DRAW);

  //load image
  
  
  //texture
  stbi_set_flip_vertically_on_load(true);  
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  //wrap and file

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  unsigned  char* data = stbi_load("container.jpg",&width,&height,&nrChannels,0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else{
    std::cout<<"Failed to load texture"<<std::endl;
  }
  stbi_image_free(data);

  //texture 2
  glGenTextures(1,&texture2);
  glBindTexture(GL_TEXTURE_2D,texture2);
  //wrap and file

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  data = stbi_load("awesomeface.png",&width,&height,&nrChannels,0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else{
    std::cout<<"Failed to load texture"<<std::endl;
  }
  stbi_image_free(data);
  //link attrib
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(2);

  //set activation
  glUseProgram(ID);
  glUniform1i(glGetUniformLocation(ID, "texture1"), 0);
  glUniform1i(glGetUniformLocation(ID, "texture2"), 1);
  

  //translate
  trans = glm::mat4(1.0f);
  trans = glm::rotate(trans,glm::radians(45.0f),glm::vec3(0.0f,0.0f,1.0f));
  trans = glm::scale(trans,glm::vec3(0.5f,0.5f,0.5f));

  
  //upade in shader
  unsigned int transformLoc = glGetUniformLocation(ID,"transform");
  glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(trans));

  //model ,view,proj
  
  //glm::mat4 model = glm::mat4(1.0f);
  //model = glm::rotate(model,glm::radians(-55.0f),glm::vec3(0.0f,0.0f,1.0f));
  /*
  float radius = 5.0f;
  float camx = sin(glfwGetTime())*radius;
  float camz = cos(glfwGetTime())*radius; 
  glm::mat4 view;
  view = glm::lookAt(glm::vec3(camx,0.0f,camz),
		     glm::vec3(0.0f,0.0f,0.0f),
		     glm::vec3(0.0f,1.0f,0.0f));//position ,target ,up vector
  */
  

  
  //int modelLoc = glGetUniformLocation(ID,"model");
  //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

  /*int viewLoc = glGetUniformLocation(ID,"view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));*/

  //createCamera()
  createCamera();
  
}

//mouse pos callback


void Terrain::createWindow(){
  initGlfw();
  window = glfwCreateWindow(WIDTH,HEIGHT,"window",NULL,NULL);
  if(window == NULL){
    std::cout<<"Failed to initialize window"<<std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  initGlew();

  deltaTime =0.0f;
  lastFrame = 0.0f;

  lastX = 400.0f;
  lastY = 400.0f;
  firstMouse = true;
  //camera fov
  cameraPos = glm::vec3(0.0f,0.0f,3.0f);
  cameraFront = glm::vec3(0.0f,0.0f,-1.0f);
  cameraUp = glm::vec3(0.0f,1.0f,0.0f);
  FOV = 45.0f;
  zNear = 0.1f;
  zFar = 100.0f;
  yaw =-90.0f;
  pitch = 0.0f;
  xPos = 0.0f;
  yPos = 0.0f;
  //position init
  proj = glm::mat4(1.0f);
  
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
  

}
//get mouse pos
void Terrain::getMousePos(){
  glfwGetCursorPos(window,&xPos,&yPos);
  mouse_callback();
}
//callback
void Terrain::mouse_callback(){
  //set to float
  float xpos = static_cast<float>(xPos);
  float ypos = static_cast<float>(yPos);
  if(firstMouse){
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }
  float xOffset = xpos - lastX;
  float yOffset = ypos - lastY;
  lastX = xpos;
  lastY = ypos;

  const float sensitivity= 0.1f;
  xOffset *=sensitivity;
  yOffset *=sensitivity;

  yaw   += xOffset;
  pitch += yOffset;
  //maintain pitch
  if(pitch >89.0f){
    pitch = 89.0f;
  }
  if(pitch <-89.0f){
    pitch = -89.0f;
  }

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));

  cameraFront = glm::normalize(direction);
  
}


void Terrain::initGlfw(){
  //intialize glfw
  if(!glfwInit()){
    printf("GLFW failed to initialize\n");
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  //init callbacks

  
}
void Terrain::initGlew(){
  //initialize glew
  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK){
    printf("Failed to initialize glew\n");
  }

}

void Terrain::handleInput(GLFWwindow* window){

  const float cameraSpeed = 2.5f * deltaTime;
  if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window,true);
  }
  if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
    cameraPos += cameraSpeed*cameraFront;
  }
  if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
    cameraPos -= cameraSpeed*cameraFront;
  }
  if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
    cameraPos -= glm::normalize(glm::cross(cameraFront,cameraUp))*cameraSpeed;
  }
  if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
    cameraPos += glm::normalize(glm::cross(cameraFront,cameraUp))*cameraSpeed;
  }
  
  
}

void Terrain::run(){
  //draw
  while(!glfwWindowShouldClose(window)){
    
    //set delta time
    float currentFrame  =glfwGetTime();
    deltaTime = currentFrame-lastFrame;
    lastFrame = currentFrame;
    
    //input
    
    handleInput(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(t_ID);
    triangleList.render();
    //renderBox();
    
    //input
    
    glfwSwapBuffers(window);
    glfwPollEvents();

    //get mosue pos
    getMousePos();
    
  }
  glfwTerminate();
}
  
int main(){
  Terrain terrain;
  terrain.createWindow();
  terrain.events();
  terrain.run();

  return 0;
}
