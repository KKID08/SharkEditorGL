#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Callback function for handling key events
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void initializeGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
}

GLFWwindow* createWindow(int width, int height, const char* title) {
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    return window;
}

void render(GLFWwindow* window, float r, float g, float b) {
    glfwMakeContextCurrent(window);
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW to use OpenGL 3.3 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the first GLFW window (green)
    GLFWwindow* window1 = createWindow(800, 600, "Green Window");
    glfwMakeContextCurrent(window1);
    initializeGLEW();
    glfwSetKeyCallback(window1, key_callback);

    // Create the second GLFW window (red)
    GLFWwindow* window2 = createWindow(800, 600, "Red Window");
    glfwMakeContextCurrent(window2);
    initializeGLEW();
    glfwSetKeyCallback(window2, key_callback);

    // Main loop
    while (!glfwWindowShouldClose(window1) && !glfwWindowShouldClose(window2)) {
        // Render to the first window (green)
        render(window1, 0.0f, 1.0f, 0.0f);

        // Render to the second window (red)
        render(window2, 1.0f, 0.0f, 0.0f);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up and exit
    glfwDestroyWindow(window1);
    glfwDestroyWindow(window2);
    glfwTerminate();
    return 0;
}
