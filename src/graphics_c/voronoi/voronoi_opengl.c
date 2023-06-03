#include <stdio.h>
#include <stdlib.h>

#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

int main(void)
{
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not initialize GLFW\n");
    exit(1);
  }

  printf("Howdy, neighbour!\n");

  return 0;
}
