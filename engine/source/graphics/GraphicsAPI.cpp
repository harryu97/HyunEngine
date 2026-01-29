#include "GraphicsAPI.h"
#include <GL/gl.h>
#include <iostream>
#include "../render/Material.h"
#include "../render/Mesh.h"
#include "ShaderProgram.h"
namespace eng {
bool GraphicsAPI::Init() {
  glEnable(GL_DEPTH_TEST);
  return true;
}
ShaderProgram* GraphicsAPI::CreateShaderProgram(
    const std::string& vertexSource,
    const std::string& fragmentSource) {
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const char* vertexShaderCStr = vertexSource.c_str();
  glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
  glCompileShader(vertexShader);

  GLint success;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cerr << "ERROR VertexShader" << infoLog << std::endl;
  }

  GLint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char* fragShaderCSTR = fragmentSource.c_str();
  glShaderSource(fragShader, 1, &fragShaderCSTR, nullptr);
  glCompileShader(fragShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
    std::cerr << "ERROR fragShader" << infoLog << std::endl;
  }
  GLint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cerr << "LINK ERROR" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);
  return new ShaderProgram(shaderProgram);
}

GLuint GraphicsAPI::CreateVertexBuffer(const std::vector<float>& vertices) {
  GLuint vbo{};
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return vbo;
}

GLuint GraphicsAPI::CreateIndexBuffer(const std::vector<uint32_t>& indices) {
  GLuint ebo{};
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float),
               indices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  return ebo;
}
void GraphicsAPI::BindShaderProgram(ShaderProgram* shaderProgram) {
  if (shaderProgram) {
    shaderProgram->Bind();
  }
}

void GraphicsAPI::BindMaterial(Material* material) {
  if (material) {
    material->Bind();
  }
}
void GraphicsAPI::BindMesh(Mesh* mesh) {
  if (mesh) {
    mesh->Bind();
  }
}
void GraphicsAPI::DrawMesh(Mesh* mesh) {
  if (mesh) {
    mesh->Draw();
  }
}

void GraphicsAPI::SetClearColor(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}
void GraphicsAPI::ClearBuffers() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

ShaderProgram* GraphicsAPI::getDefaultShaderProgram() {
  std::cout << "DEFAULT" << std::endl;
  if (!m_defaultShaderProgram) {
    std::string vertexShaderSource = R"(#version 330 core 
    layout(location=0) in vec3 position;
    layout(location=1) in vec3 color;
    layout(location=2) in vec2 uv;
    layout(location=3) in vec3 normal;

    
    out vec2 vUv;
    out vec3 vNormal;
    out vec3 vFragPos;
    uniform mat4 uModel;
    uniform mat4 uView;
    uniform mat4 uProjection;

    void main(){
    gl_Position=uProjection*uView*uModel*vec4(position,1.0);
   
    vFragPos=vec3(uModel*vec4(position,1.0));
    vNormal = normalize(transpose(inverse(mat3(uModel))) * normal);
              
   
    vUv=uv;
    })";
    std::string fragShaderSource = R"(
   #version 330 core

            struct Light
            {
                vec3 color;
                vec3 direction;
            };

            uniform Light uLight;
            uniform vec3 uCameraPos;
            uniform vec3 color; 
            out vec4 FragColor;

            in vec2 vUv;
            in vec3 vNormal;
            in vec3 vFragPos;

            uniform sampler2D baseColorTexture;

            void main()
            {
                vec3 norm = normalize(vNormal);
                
                // diffuse
                vec3 lightDir = normalize(-uLight.direction);
                float diff = max(dot(norm, lightDir), 0.0);
                vec3 diffuse = diff * uLight.color;

                // specular
                vec3 viewDir = normalize(uCameraPos - vFragPos);
                vec3 redlectDir = reflect(-lightDir, norm);
                float spec = pow(max(dot(viewDir, redlectDir), 0.0), 32.0);
                float specularStrength = 0.5;
                vec3 specular = specularStrength * spec * uLight.color;
               //ambient 
                const float ambientStrength=0.4;
                vec3 ambient=ambientStrength*uLight.color;
                vec3 result=diffuse+specular+ambient;
                vec4 texColor=texture(baseColorTexture,vUv);
                FragColor =texColor* vec4(result, 1.0);
            }                            
    )";
    m_defaultShaderProgram =
        CreateShaderProgram(vertexShaderSource, fragShaderSource);
  }
  return m_defaultShaderProgram;
}
void GraphicsAPI::UnbindMesh(Mesh* mesh) {
  if (mesh) {
    mesh->UnBind();
  }
}
}  // namespace eng
