#include <GLFW/glfw3.h>
#include <iostream>
#include "./ButtonsCallback.hpp"
#include "./PngLoader.hpp"
#include <cstring>

using namespace std;


static void glfw_error_callback(int error, const char* desc) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, desc);
}

int main(void)
{
    GLFWwindow* window;
    double xpos, ypos;

    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "SPMC-game", NULL, NULL);

    glfwSetErrorCallback(glfw_error_callback);
    glfwSetKeyCallback(window, buttons_callback);
    
    
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glClearColor( 0.4f, 0.3f, 0.4f, 0.0f );

        
    /* Load custom cursor */
    GLFWimage cursor_image = load_png("./data/Assets/UI/cursor.png");
    GLFWcursor* cursor = glfwCreateCursor(&cursor_image, 0, 0);
    glfwSetCursor(window, cursor);
    /* ----------------------------- */
        
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
    
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    // Deallocate memory
    deallocate_pixels(cursor_image.pixels);
    
    glfwTerminate();
    return 0;
}
