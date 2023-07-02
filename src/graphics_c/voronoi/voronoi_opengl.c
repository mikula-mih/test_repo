#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

#include "glextloader.c"

#define DEFAULT_SCREEN_WIDTH 1600
#define DEFAULT_SCREEN_HEIGHT 900

void MessageCallback(GLenum source,
                     GLenum type,
                     GLuint id,
                     GLenum severity,
                     GLsizei length,
                     const GLchar* message,
                     const void* userParam)
{
  (void) source;
  (void) id;
  (void) length;
  (void) userParam;
  fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
          type, severity, message);
}

char *slurp_file_into_malloced_cstr(const char *file_path)
{
  FILE *f = NULL;
  char *buffer = NULL;

  f = fopen(file_path, "r");
  if (f == NULL) goto fail;
  if (fseek(f, 0, SEEK_END) < 0) goto fail;

  long size = ftell(f);
  if (size < 0) goto fail;

  buffer = malloc(size + 1);
  if (buffer == NULL) goto fail;

  if (fseek(f, 0, SEEK_SET) < 0) goto fail;

  fread(buffer, 1, size, f);
  if (ferror(f)) goto fail;

  buffer[size] = '\0';

  if (f) {
    fclose(f);
    errno = 0;
  }
  return buffer;
fail:
  if (f) {
    int saved_errno = errno;
    fclose(f);
    errno = saved_errno;
  }
  if (buffer) {
    free(buffer);
  }
  return NULL;
}

const char *shader_type_as_cstr(GLuint shader)
{
  switch (shader) {
    case GL_VERTEX_SHADER:
      return "GL_VERTEX_SHADER";
    case GL_FRAGMENT_SHADER:
      return "GL_FRAGMENT_SHADER";
    default:
      return "(Unknown)";
  }
}

bool compile_shader_source(const GLchar *source, GLenum shader_type, GLuint *shader)
{
  *shader = glCreateShader(shader_type);
  glShaderSource(*shader, 1, &source, NULL);
  glCompileShader(*shader);

  GLint compiled = 0;
  glGetShaderiv(*shader, GL_COMPILE_STATUS, &compiled);

  if (!compiled) {
    GLchar message[1024];
    GLsizei message_size = 0;
    glGetShaderInfoLog(*shader, sizeof(message), &message_size, message);
    fprintf(stderr, "ERROR: could not compile %s\n", shader_type_as_cstr(shader_type));
    fprintf(stderr, "%.*s\n", message_size, message);
    return false;
  }

  return true;
}

bool compile_shader_file(const char *file_path, GLenum shader_type, GLuint *shader)
{
  char *source = slurp_file_into_malloced_cstr(file_path);
  if (source == NULL) {
    fprintf(stderr, "ERROR: failed to read file `%s`: %s\n", file_path, strerror(errno));
    errno = 0;
    return false;
  }
  bool ok = compile_shader_source(source, shader_type, shader);
  if (!ok) {
    fprintf(stderr, "ERROR: failed to compile `%s` shader file\n", file_path);
  }
  free(source);
  return ok;
}

bool link_program(GLuint vert_shader, GLuint frag_shader, GLuint *program)
{
  *program = glCreateProgram();

  glAttachShader(*program, vert_shader);
  glAttachShader(*program, frag_shader);
  glLinkProgram(*program);

  GLint linked = 0;
  glGetProgramiv(*program, GL_LINK_STATUS, &linked);
  if (!linked) {
    GLsizei message_size = 0;
    GLchar message[1024];

    glGetProgramInfoLog(*program, sizeof(message), &message_size, message);
    fprintf(stderr, "Program Linked: %.*s\n", message_size, message);
  }

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

  return program;
}

bool load_shader_program(const char *vertex_file_path,
                         const char *fragment_file_path,
                         GLuint *program)
{
  GLuint vert = 0;
  if (!compile_shader_file(vertex_file_path, GL_VERTEX_SHADER, &vert)) {
    return false;
  }

  GLuint frag = 0;
  if (!compile_shader_file(fragment_file_path, GL_FRAGMENT_SHADER, &frag)) {
    return false;
  }

  if (!link_program(vert, frag, program)) {
    return false;
  }

  return true;
}

int main(void)
{
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not initialize GLFW\n");
    exit(1);
  }

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  GLFWwindow * const window = glfwCreateWindow(
                                  DEFAULT_SCREEN_WIDTH,
                                  DEFAULT_SCREEN_HEIGHT,
                                  "OpenGL Template",
                                  NULL,
                                  NULL);

  if (window == NULL) {
    fprintf(stderr, "ERROR: could not create a window.\n");
    glfwTerminate();
    exit(1);
  }

  int gl_ver_major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
  int gl_ver_minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
  printf("OpenGL %d.%d\n", gl_ver_major, gl_ver_minor);

  glfwMakeContextCurrent(window);

  load_gl_extensions();

  if (glDebugMessageCallback != NULL) {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
  }

  //glfwSetKeyCallback(window, key_callback);
  //glfwSetFramebufferSizeCallback(window, window_size_callback);
  
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  const char *vertex_file_path = "shaders/quad.vert";
  const char *fragment_file_path = "shaders/color.frag";
  GLuint program;
  if (!load_shader_program(vertex_file_path, fragment_file_path, &program)) {
    exit(1);
  }

  glUseProgram(program);

  double prev_time = glfwGetTime();
  double delta_time = 0.0;

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    xpos = xpos - width * 0.5f;
    ypos = (height - ypos) - height * 0.5f;

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    double cur_time = glfwGetTime();
    delta_time = cur_time - prev_time;
    prev_time = cur_time;
  }


  printf("Howdy, neighbour!\n");

  return 0;
}
