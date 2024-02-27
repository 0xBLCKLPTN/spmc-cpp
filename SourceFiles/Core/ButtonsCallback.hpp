#define BUTTONSCALLBACK_HPP
#ifndef BUTTONSCALLBCK_HPP

#include <GLFW/glfw3.h>

static void cursor_position_callback(
  GLFWwindow* window,
  double xpos,
  double ypos
) {
  printf("Cursor position: %f-%f\n", xpos, ypos);
}

void buttons_callback(
  GLFWwindow* window,
  int key,
  int scancode,
  int action,
  int mode
) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  if (key == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
    printf("Mouse button 1 pressed.");
  if (key == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS)
    printf("Mouse button 2 pressed.");
}

#endif
