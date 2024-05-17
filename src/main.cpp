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
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void resetSimulation();

bool resetFlag = false;
bool paused = false;

#if defined _WIN32
#define seperator "\\"
#else
#define seperator "/"
#endif

int main(int argc, char **argv)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simple Pendulum Simulation", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
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

        if (paused) // display the pendulum at the same position if paused
        {
            display_pendulum();
        }
        else // display the pendulum at the updated position if not paused
        {
            simple_pendulum_simulation_step();
        }
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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        paused = !paused;
        printf("Changed paused to %i", paused);
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        float nx = (2.0f * xpos) / width - 1.0f;
        float ny = 1.0f - (2.0f * ypos) / height;

        if (nx >= 0.7f && nx <= 1.0f && ny >= -1.0f && ny <= -0.7f)
        {
#if defined _WIN32
            system("cmd /c start /wait get_dimensions.bat");
#else
            system("sh get_dimensions.sh");
#endif

            openTerminal();
            resetFlag = true; // Set the reset flag to true
        }
    }
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    // last mouse button for mouse button left state
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    double xpos_prime = xpos;
    double ypos_prime = SCR_HEIGHT - ypos;

    // if left button is being pressed and the cursor is within the bob
    if (GLFW_PRESS == state 
        && ((g_bob_center[0] - RADIUS_OF_BOB) < xpos_prime < (g_bob_center[0] + RADIUS_OF_BOB)) 
        && ((g_bob_center[1] - RADIUS_OF_BOB) < ypos_prime < (g_bob_center[1] + RADIUS_OF_BOB)))
    {
        paused = true;
        // printf("Time %0.3f: Cursor position: %f %f\n",
        //        glfwGetTime(), xpos_prime, ypos_prime);

        // printf("Current bob position %0.3f, %0.3f\n", g_bob_center[0], g_bob_center[1]);

        g_bob_center[0] = xpos_prime;
        g_bob_center[1] = ypos_prime;

        // updating the current angle based on the position
        g_current_angle = atan(xpos_prime / ypos_prime) * 180.0 / M_PI;

        // updating the length based on the current position
        g_radius = sqrt(pow(xpos_prime - g_center[0], 2) + pow(ypos_prime - g_center[1], 2));
    }
    else if (GLFW_RELEASE == state)
    {
        paused = false;
    }
}

std::string getTempPath()
{
#if defined _WIN32
    const char *tempPath = std::getenv("TEMP");
#else
    const char *tempPath = "/tmp";
#endif
    if (!tempPath)
    {
        std::cerr << "TEMP environment variable not found." << std::endl;
        return "";
    }
    return (std::string(tempPath) + seperator) + "dimensions.txt";
}

void openTerminal()
{
    std::string filePath = getTempPath();
    std::fstream file;

    file.open(filePath, std::fstream::in | std::fstream::out | std::fstream::app);

    if (!file.is_open())
    {
        std::cout << "Cannot open file, the file: " << filePath << " does not exist. Creating new file..";

        file.open(filePath, std::fstream::in | std::fstream::out | std::fstream::trunc);
    }

    if (file.is_open())
    {
        file >> g_mass >> g_acceleration_due_to_gravity_g >> g_damping_factor >> g_radius >> g_current_angle;
        std::cout << "Got the values: \n Mass(M): " << g_mass << "\n Acceleration Due to Gravity(g): " << g_acceleration_due_to_gravity_g
                  << "\n Damping Factor: " << g_damping_factor << "\n Length of string: " << g_radius << "\n Starting Angle: " << g_current_angle << std::endl;
        file.close();
    }
    else
    {
        std::cerr << "Couldn't open or create file " << filePath << " . So, the parameters couldn't be updated.";
    }
}

void resetSimulation()
{
    initialize_simple_pendulum_simulation_with_defaults(g_radius, g_current_angle);
    g_n_filled = 0;
    g_current_previous_index = 0;
}
