#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "./ButtonsCallback.hpp"
#include "./PngLoader.hpp"
#include <cstring>
#include "../Components/Triangle.hpp"

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
        Triangle tr;
        GLuint VertexArrayID;
        GLuint programID;
        GLuint vertexbuffer;

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


            programID = LoadShaders("./data/Assets/Shaders/Triangle.vertexshader", "./data/Assets/Shaders/Triangle.fragmentshader");
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            static const GLfloat g_vertex_buffer_data[] = { 
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f,  1.0f, 0.0f,
            };

            
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
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
                
                glUseProgram(programID);
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                );
                glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
                glDisableVertexAttribArray(0);

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
            glDeleteBuffers(1, &vertexbuffer);
            glDeleteVertexArrays(1, &VertexArrayID);
            glDeleteProgram(programID);
            glfwTerminate();
        }
};

int main(void)
{
    Window w;
    return 0;
}
