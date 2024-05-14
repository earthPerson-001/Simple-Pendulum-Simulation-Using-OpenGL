
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// #include <vector>
// #include <iostream>
// #include <cmath>
// #include <fstream>
// #include "globals.hpp"

// #include "simple_pendulum.hpp"



// void processInput(GLFWwindow *window);
// void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// void openTerminal();
// void reinitializeSimulation();

// void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// int main(int argc, char **argv)
// {
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif

//     GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simple Pendulum Simulation", NULL, NULL);
//     if (window == NULL)
//     {
//         std::cout << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//     glfwSetMouseButtonCallback(window, mouse_button_callback);
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cout << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }

//     glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

//     initialize_simple_pendulum_simulation_with_defaults();

//     while (!glfwWindowShouldClose(window))
//     {
//         // input
//         processInput(window);

//         // sleep_ms(1);

//         // rendering commands here
//         glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], BACKGROUND_COLOR[3]);
//         glClear(GL_COLOR_BUFFER_BIT);
//        glLineWidth(10);                  // Set the width of the lines
// glBegin(GL_QUADS);                // Begin drawing lines
// glColor3f(1, 1, 1);               // Set the color of the lines to black
// glVertex2f(0.7, -1.0);             // Specify the first vertex
// glVertex2f(0.7, -0.7);             // Specify the second vertex to connect to the first
// glVertex2f(1.0,-0.7);
// glVertex2f(1.0,-1.0);
// glEnd(); 

//        glLineWidth(20);                  // Set the width of the lines
// glBegin(GL_LINES);                // Begin drawing lines
// glColor3f(0, 0, 0);               // Set the color of the lines to black
// glVertex2f(0.9, -1.0);             // Specify the first vertex
// glVertex2f(0.9, -0.8);             // Specify the second vertex to connect to the first
// glEnd();                          // End drawing lines


// glLineWidth(20);                  // Set the width of the lines
// glBegin(GL_LINES);                // Begin drawing lines
// glColor3f(0, 0, 0);               // Set the color of the lines to black
// glVertex2f(0.8, -1.0);             // Specify the first vertex
// glVertex2f(0.8, -0.8);             // Specify the second vertex to connect to the first
// glEnd();  
//         simple_pendulum_simulation_step();

//         // check and call events and swap the buffers
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     terminate_simple_pendulum_simulation();

//     glfwTerminate();
//     return 0;
// }

// void processInput(GLFWwindow *window)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

// void framebuffer_size_callback(GLFWwindow *window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }



// void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
//     if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
//         double xpos, ypos;
//         glfwGetCursorPos(window, &xpos, &ypos);
//         int width, height;
//         glfwGetFramebufferSize(window, &width, &height);

//         // Convert screen coordinates to normalized device coordinates
//         float nx = (2.0f * xpos) / width - 1.0f;
//         float ny = 1.0f - (2.0f * ypos) / height;

//         // Check if the click is within the rectangle bounds
//         if (nx >= 0.7f && nx <= 1.0f && ny >= -1.0f && ny <= -0.7f) {
//             system("cmd /c start /wait get_dimensions.bat");
//         openTerminal();
//         glfwPostEmptyEvent(); 
//         }
//     }
// }

// // Function to get the full path to the dimensions file using the TEMP environment variable
// std::string getTempPath() {
//     const char* tempPath = std::getenv("TEMP");
//     if (!tempPath) {
//         std::cerr << "TEMP environment variable not found." << std::endl;
//         return "";
//     }
//     return std::string(tempPath) + "\\dimensions.txt";
// }

// // Function to update dimensions from a file
// void openTerminal() {
//     std::string filePath = getTempPath();
//     std::ifstream file(filePath);
//     if (file.is_open()) {
//         file >> g_mass >>g_acceleration_due_to_gravity_g >> g_damping_factor;
//         file.close();
//          reinitializeSimulation();
//     } else {
//         std::cerr << "Failed to open file at: " << filePath << std::endl;
//     }
// }

// void reinitializeSimulation() {
//     // Terminate the current simulation
//    // terminate_simple_pendulum_simulation();
    
//     // Initialize the simulation with updated values
//     initialize_simple_pendulum_simulation_with_defaults();
// }














// // #include <glad/glad.h>
// // #include <GLFW/glfw3.h>
// // #include <iostream>
// // #include <fstream>
// // #include <cstdlib>

// // // Global variables for rectangle dimensions
// // GLfloat rectWidth = 0.5f;
// // GLfloat rectHeight = 0.5f;

// // // Function to get the full path to the dimensions file using the TEMP environment variable
// // std::string getTempPath() {
// //     const char* tempPath = std::getenv("TEMP");
// //     if (!tempPath) {
// //         std::cerr << "TEMP environment variable not found." << std::endl;
// //         return "";
// //     }
// //     return std::string(tempPath) + "\\dimensions.txt";
// // }

// // // Function to update dimensions from a file
// // void updateDimensions() {
// //     std::string filePath = getTempPath();
// //     std::ifstream file(filePath);
// //     if (file.is_open()) {
// //         file >> rectWidth >> rectHeight;
// //         file.close();
// //     } else {
// //         std::cerr << "Failed to open file at: " << filePath << std::endl;
// //     }
// // }
// // // GLFW callback for mouse button events
// // void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
// //     if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
// //         // Run the batch script and wait for the user to input new dimensions
// //         system("cmd /c start /wait get_dimensions.bat");
// //         updateDimensions();
// //         glfwPostEmptyEvent(); // Post an empty event to trigger redrawing
// //     }
// // }
// // void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
// //     glViewport(0, 0, width, height);
// // }

// // void processInput(GLFWwindow* window) {
// //     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
// //         glfwSetWindowShouldClose(window, true);
// // }

// // int main() {
// //     // Initialize GLFW
// //     if (!glfwInit()) {
// //         std::cerr << "Failed to initialize GLFW" << std::endl;
// //         return -1;
// //     }

// //     // Create GLFW window
// //     GLFWwindow* window = glfwCreateWindow(720, 600, "Lab 1", nullptr, nullptr);
// //     if (!window) {
// //         std::cout << "Failed to create GLFW window" << std::endl;
// //         glfwTerminate();
// //         return -1;
// //     }
// //     glfwMakeContextCurrent(window);

// //     // Initialize GLAD
// //     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
// //         std::cout << "Failed to initialize GLAD" << std::endl;
// //         return -1;
// //     }

// //     // Set viewport and callbacks
// //     glViewport(0, 0, 720, 600);
// //     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
// //     glfwSetMouseButtonCallback(window, mouse_button_callback);

// //     while (!glfwWindowShouldClose(window)) {
// //         // Input handling
// //         processInput(window);

// //         // Clear the screen
// //         glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
// //         glClear(GL_COLOR_BUFFER_BIT);

// //         // Draw rectangle with dynamic dimensions
// //         glLineWidth(20);
// //         glBegin(GL_QUADS);
// //         glColor3f(1.0f, 0.0f, 0.0f); // Red color
// //         glVertex2f(-rectWidth / 2, -rectHeight / 2);
// //         glVertex2f(rectWidth / 2, -rectHeight / 2);
// //         glVertex2f(rectWidth / 2, rectHeight / 2);
// //         glVertex2f(-rectWidth / 2, rectHeight / 2);
// //         glEnd();

// //         glfwSwapBuffers(window);
// //         glfwPollEvents();
// //     }

// //     glfwTerminate();
// //     return 0;
// // }





#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "globals.hpp"
#include "simple_pendulum.hpp"

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void openTerminal();
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void resetSimulation();

bool resetFlag = false;

int main(int argc, char **argv)
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simple Pendulum Simulation", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    initialize_simple_pendulum_simulation_with_defaults();

    while (!glfwWindowShouldClose(window))
    {
        if (resetFlag)
        {
            resetSimulation();
            resetFlag = false;
        }

        processInput(window);

        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], BACKGROUND_COLOR[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw rectangle
        glLineWidth(10);
        glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glVertex2f(0.7, -1.0);
        glVertex2f(0.7, -0.7);
        glVertex2f(1.0, -0.7);
        glVertex2f(1.0, -1.0);
        glEnd();

        // Draw lines
        glLineWidth(20);
        glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        glVertex2f(0.9, -1.0);
        glVertex2f(0.9, -0.8);
        glEnd();

        glLineWidth(20);
        glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        glVertex2f(0.8, -1.0);
        glVertex2f(0.8, -0.8);
        glEnd();

        simple_pendulum_simulation_step();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    terminate_simple_pendulum_simulation();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        float nx = (2.0f * xpos) / width - 1.0f;
        float ny = 1.0f - (2.0f * ypos) / height;

        if (nx >= 0.7f && nx <= 1.0f && ny >= -1.0f && ny <= -0.7f) {
            system("cmd /c start /wait get_dimensions.bat");
            openTerminal();
            resetFlag = true; // Set the reset flag to true
        }
    }
}

std::string getTempPath() {
    const char* tempPath = std::getenv("TEMP");
    if (!tempPath) {
        std::cerr << "TEMP environment variable not found." << std::endl;
        return "";
    }
    return std::string(tempPath) + "\\dimensions.txt";
}

void openTerminal() {
    std::string filePath = getTempPath();
    std::ifstream file(filePath);
    if (file.is_open()) {
        file >> g_mass >> g_acceleration_due_to_gravity_g >> g_damping_factor;
        file.close();

    } else {
        std::cerr << "Failed to open file at: " << filePath << std::endl;
    }
}

void resetSimulation() {
    initialize_simple_pendulum_simulation_with_defaults();
}

