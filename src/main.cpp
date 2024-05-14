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

