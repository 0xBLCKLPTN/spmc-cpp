#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "./ButtonsCallback.hpp"
#include "./PngLoader.hpp"
#include <cstring>

using namespace std;
using namespace glm;

static void glfw_error_callback(int error, const char* desc) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, desc);
}

class Window
{
    public:
        GLFWwindow *window;
        GLFWimage cursor_image;
        double xpos, ypos;

        void initGLSettings()
        {
            glfwSetErrorCallback(glfw_error_callback);
            glfwSetKeyCallback(window, buttons_callback);
            glEnable(GL_DEPTH_TEST);
	        glfwWindowHint(GLFW_SAMPLES, 4);
	        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make macOS happy; should not be needed
	        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Мы не хотим старый OpenGL
            glewExperimental=true; // Флаг необходим в Core-режиме OpenGL
        }

        void initCursor()
        {
            cursor_image = load_png("./data/Assets/UI/cursor.png");
            GLFWcursor* cursor = glfwCreateCursor(&cursor_image, 0, 0);
            glfwSetCursor(window, cursor);
        }

        void render()
        {
            while (!glfwWindowShouldClose(window))
            {
                /* Render here */
                glClear(GL_COLOR_BUFFER_BIT);
            
                /* Swap front and back buffers */
                glfwSwapBuffers(window);
                
                /* Poll for and process events */
                glfwPollEvents();
            }
        }

        Window()
        {
            if (!glfwInit())
                return;
            
            
            window = glfwCreateWindow(1920, 1080, "spmc", nullptr, nullptr);
            this->initGLSettings();
            this->initCursor();
            if (!window) {
                glfwTerminate();
                return;
            }
            glfwMakeContextCurrent(window);
            glClearColor( 0.4f, 0.3f, 0.4f, 0.0f );
            this->render();
            deallocate_pixels(cursor_image.pixels);
            glfwTerminate();
        }
};

int main(void)
{
    Window w;
    return 0;
}
