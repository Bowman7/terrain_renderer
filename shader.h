#ifndef SHADER_H
#define SHADER_H

#include<string.h>
#include<fstream>
#include<sstream>
#include<iostream>


class shader{

 public:
  //program ID
  unsigned int ID;
  shader(const char* vertexPath,const char* fragmentPath);
  //use program
  void use();
  //uitlity unifomr functions
  void setBool(const std::string &name,bool value) const;
  void setInt(const std::string &name,int value) const;
  void setFloat(const std::string &name,float value) const;
  
};

shader::shader(const char* vertexPath,const char* fragmentPath) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  //handle exceptions
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try{
    //open file
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream,fShaderStream;
    //read files buffer content into stream
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    //close file handlers
    vShaderFile.close();
    fShaderFile.close();

    //convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch(std::ifstream::failure e){
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }

  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  //compile shaders

   //compile vertexshader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader,1,&vShaderCode,NULL);
  glCompileShader(vertexShader);
  //check
  int  success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success)
    {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
  //compile fragment shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader,1,&fShaderCode,NULL);
  glCompileShader(fragmentShader);
  //check
  int  success2;
  char infoLog2[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);
  if(!success2)
    {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
    }
  //shader program
  ID = glCreateProgram();
  glAttachShader(ID,vertexShader);
  glAttachShader(ID,fragmentShader);
  glLinkProgram(ID);
  //check
  int  success3;
  char infoLog3[512];
  glGetProgramiv(ID, GL_LINK_STATUS, &success3);
  if(!success3)
    {
      glGetProgramInfoLog(ID, 512, NULL, infoLog3);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog3 << std::endl;
    }
  //delete shaders after use
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  
}

void shader::use(){
  glUseProgram(ID);
}

void shader::setBool(const std::string &name,bool value) const {
  glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}

void shader::setInt(const std::string &name,int value) const {
  glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}

void shader::setFloat(const std::string &name,float value) const {
  glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}
#endif
