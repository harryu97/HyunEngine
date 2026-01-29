#pragma once
#include <GL/glew.h>
#include <string>
#include <unordered_map>
namespace eng {
class Texture {
 public:
  Texture(int width, int height, int numChannels, unsigned char* data);
  ~Texture();

  GLuint GetId() const;
  void Init(int width, int height, int numChannels, unsigned char* data);
  static Texture* Load(const std::string& path);

 private:
  int m_width = 0;
  int m_height = 0;
  int m_numChannels = 0;

  GLuint m_textureId = 0;
};
class TextureManager {
 public:
  Texture* GetOrLoadTexture(const std::string& path);

 private:
  std::unordered_map<std::string, Texture*> m_textures;
};
}  // namespace eng
//
