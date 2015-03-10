// TAGRELEASE: PUBLIC

#ifndef __render_font_hpp__
#define __render_font_hpp__

#include <vector>
#include <string>

// In order to get OpenGL API...
#include <NvFoundation.h>
#include <NV/NvPlatformGL.h>

#include <Cg/double.hpp>
#include <Cg/vector.hpp>
#include <Cg/matrix.hpp>

#include "cg4cpp_xform.hpp"

struct FontFace {
  static const int em_scale = 2048;

  const char *font_name;
  GLuint glyph_base;
  int num_chars;
  std::vector<GLfloat> horizontal_advance;
  GLfloat y_min, y_max;
  GLfloat underline_position, underline_thickness;

  FontFace(GLenum target, const char *name, int num_chars_, GLuint path_param_template);
  ~FontFace();
};

struct Message {
  std::string message;
  const FontFace *font;
  size_t message_length;
  std::vector<GLfloat> xtranslate;
  GLfloat total_advance;
  Cg::float3x3 matrix;
  bool stroking, filling;
  int underline;
  int fill_gradient;
  GLuint colorProgram;
  GLuint quadProgram;
  bool es_context;

  Message(const FontFace *font_, const char *message_, Cg::float2 to_quad[4]);

  ~Message();

  void render();
  Cg::float3x3 getMatrix();
  void multMatrix();
  void loadMatrix();

  void setFilling(bool filling_) {
    filling = filling_;
  }
  void setStroking(bool stroking_) {
    stroking = stroking_;
  }
  void setUnderline(int underline_) {
    underline = underline_;
  }
  void setEsContext(bool es_context_) {
    es_context = es_context_;
  }

  Message& operator = (const Message& val);
};

#endif // __render_font_hpp__