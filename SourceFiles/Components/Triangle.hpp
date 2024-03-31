#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP


#include "Triangle.hpp"
#include <GL/glew.h>
#include "../Core/common/ShaderLoader.hpp"

class Triangle {
    private:
        GLuint VertexArrayID;
        GLuint programID;
        GLuint vertexbuffer;
    
    public:
        void Init()
        {
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

        void Draw()
        {
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
        }

        void Destroy()
        {
            // Cleanup VBO
            glDeleteBuffers(1, &vertexbuffer);
            glDeleteVertexArrays(1, &VertexArrayID);
            glDeleteProgram(programID);
        }
};

#endif