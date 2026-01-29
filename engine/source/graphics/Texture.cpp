#include "Texture.h"
#include <filesystem>
#include "../Engine.h"
#include "GraphicsAPI.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
namespace eng {
Texture::Texture(int width, int height, int numChannels, unsigned char* data) {
  Init(width, height, numChannels, data);
}

Texture::~Texture() {
  // Free the texture
  if (m_textureId > 0) {
    glDeleteTextures(1, &m_textureId);
  }
}

GLuint Texture::GetId() const {
  return m_textureId;
}
Texture* Texture::Load(const std::string& path) {
  int width, height, numChannels;
  auto& fs = eng::Engine::getInstance().getFileSystem();
  auto fullPath = fs.GetAssetsFolder() / path;
  if (!std::filesystem::exists(fullPath)) {
    return nullptr;
  }
  Texture* result;
  unsigned char* data =
      stbi_load(fullPath.string().c_str(), &width, &height, &numChannels, 0);
  if (data) {
    result = new Texture(width, height, numChannels, data);
    stbi_image_free(data);
  }
  return result;
}

void Texture::Init(int width,
                   int height,
                   int numChannels,
                   unsigned char* data) {
  m_width = width;
  m_height = height;
  m_numChannels = numChannels;

  glGenTextures(1, &m_textureId);
  glBindTexture(GL_TEXTURE_2D, m_textureId);

  GLint internalFormat = GL_RGB;
  GLenum format = GL_RGB;
  if (numChannels == 4) {
    internalFormat = GL_RGBA;
    format = GL_RGBA;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);

  // mip map is used for filerting for different distance
  glGenerateMipmap(GL_TEXTURE_2D);
  // s t same for u and v
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Configure filter how texture is scaled
  // Mag filter for magnification
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
}

Texture* TextureManager::GetOrLoadTexture(const std::string& path) {
  auto it = m_textures.find(path);
  if (it != m_textures.end()) {
    return it->second;
  }
  auto texture = Texture::Load(path);
  m_textures[path] = texture;
  return texture;
}
}  // namespace eng
