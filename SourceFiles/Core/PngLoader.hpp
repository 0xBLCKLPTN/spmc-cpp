#ifndef PNGLOADER_HPP
#define PNGLOADER_HPP

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"
#include <GLFW/glfw3.h>

void deallocate_pixels(unsigned char* pixels) {
  stbi_image_free(pixels);
}

GLFWimage load_png(char *path_to_image)
{
  int width, height, channels;
  unsigned char *pixels = stbi_load(path_to_image, &width, &height, &channels, 0);

  if ( pixels == NULL ) {
    printf("Could't load texture.\n");
    exit(1);
  }

  GLFWimage image;
  image.width = width;
  image.height = height;
  image.pixels = pixels;
  
  return image;
}

#endif
