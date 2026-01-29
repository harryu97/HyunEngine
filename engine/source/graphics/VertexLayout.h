#pragma once
#include <GL/glew.h>
#include <stdint.h>
#include <vector>
namespace eng {

struct VertexElement {
  GLuint index;     // Attribute layout location
  GLuint size;      // number of components. 3 for position
  GLuint type;      // Data type (eg GL_FLOAT)
  uint32_t offset;  // Btyes offset from start of vertex

  static constexpr int PositionIndex = 0;
  static constexpr int ColorIndex = 1;
  static constexpr int UVIndex = 2;

  // Normal attribute
  // Set normal index to 3 and extend accessors to 4
  static constexpr int NormalIndex = 3;
};

// Holds the list of vertex VertexElement
struct VertexLayout {
  std::vector<VertexElement> elements;
  uint32_t stride = 0;  // Total size of a single vertex
};
}  // namespace eng
