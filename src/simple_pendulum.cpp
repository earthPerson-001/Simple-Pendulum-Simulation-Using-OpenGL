// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <vector>
// #include <iostream>
// #include <cmath>
// #include <array>

// #include "globals.hpp"
// #include "simple_pendulum.hpp"

// // tunables
// GLfloat g_radius = 0;
// GLfloat g_mass = 1;
// GLfloat g_acceleration_due_to_gravity_g = 9.8;
// GLfloat g_damping_factor = 0.001;

// // some instance parameters
// GLfloat *g_center = nullptr;
// GLfloat g_current_angle = 0;
// GLfloat *g_bob_center = nullptr;
// GLfloat g_current_acceleration;
// GLfloat g_current_velocity;

// #if defined SHOW_TRAILING_LINE==1
// // previous points to track
// constexpr uint8_t N_PREVIOUS = 100;
// GLfloat *g_previous_points_x_y = nullptr;
// uint8_t g_current_previous_index = 0;
// uint8_t g_n_filled = 0; // keeping track of number of filled entries initially
// #endif

// /**
//  * Assuming the x and y dimension are of same scale
//  */
// static GLfloat normalize_length(GLfloat l)
// {
//     return l / SCR_WIDTH;
// }

// static std::array<GLfloat, 2> normalized_to_device_specific(GLfloat x, GLfloat y)
// {
//     return {
//         (x + 1) * SCR_WIDTH / 2,
//         (y + 1) * SCR_HEIGHT / 2};
// }

// static std::array<GLfloat, 2> device_specific_to_normalized(GLfloat x, GLfloat y)
// {
//     return {
//         2 * (x / SCR_WIDTH) - 1,
//         2 * (y / SCR_HEIGHT) - 1};
// }

// static void draw_hollow_circle_normalized(GLfloat center[2], GLfloat radius, GLfloat color[3])
// {
//     glColor3fv(color);

//     glLineWidth(5);

//     glBegin(GL_LINE_LOOP);

//     for (uint16_t i = 0; i < N_LINES_FOR_CIRCLE; i++)
//     {
//         glVertex3f(
//             center[0] + (radius * cos(2 * M_PI * i / N_LINES_FOR_CIRCLE)),
//             center[1] + (radius * sin(2 * M_PI * i / N_LINES_FOR_CIRCLE)),
//             0.0);
//     }

//     glEnd();
// }

// /**
//  * The coordinates are in window specific format
//  */
// static void draw_hollow_circle(GLfloat center[2], GLfloat radius, GLfloat color[3])
// {
//     std::array<GLfloat, 2> temp = device_specific_to_normalized(center[0], center[1]);

//     // creating copies
//     GLfloat new_center[2] = {temp[0], temp[1]};
//     GLfloat new_radius = normalize_length(radius);

//     draw_hollow_circle_normalized(new_center, new_radius, color);
// }

// /**
//  * The coordinates are in normalized format [-1,1]
//  */
// static void draw_filled_circle(GLfloat center[2], GLfloat radius, GLfloat background_color[3], GLfloat circle_color[3])
// {
//     std::array<GLfloat, 2> temp = device_specific_to_normalized(center[0], center[1]);

//     // creating copies
//     GLfloat new_center[2] = {temp[0], temp[1]};
//     GLfloat new_radius = normalize_length(radius);

//     glColor3fv(background_color);

//     // draw circle

//     glBegin(GL_TRIANGLE_FAN);
//     glVertex2f(new_center[0], new_center[1]); // the first vertex of triangle is the center of circle
//     for (uint16_t i = 0; i < N_TRIANGLES_FOR_FILLED_CIRCLE; i++)
//     {
//         glVertex2f(
//             new_center[0] + (new_radius * cos(2 * M_PI * i / N_TRIANGLES_FOR_FILLED_CIRCLE)),
//             new_center[1] + (new_radius * sin(2 * M_PI * i / N_TRIANGLES_FOR_FILLED_CIRCLE)));
//     }
//     // adding these two as the last triangle drawn was incomplete
//     glVertex2f(new_center[0], new_center[1] + new_radius);
//     glVertex2f(new_center[0], new_center[1]);
//     glEnd();

//     if (circle_color != nullptr)
//     {
//         glLineWidth(5);

//         // draw circle

//         draw_hollow_circle_normalized(new_center, new_radius, circle_color);
//     }
// }

// static void draw_line(GLfloat start_point[2], GLfloat end_point[2], GLfloat color[3], int line_width = 5)
// {

//     // creating copies
//     auto temp1 = device_specific_to_normalized(start_point[0], start_point[1]);
//     GLfloat new_start_point[2] = {temp1[0], temp1[1]};
//     auto temp2 = device_specific_to_normalized(end_point[0], end_point[1]);
//     GLfloat new_end_point[2] = {temp2[0], temp2[1]};

//     glBegin(GL_LINES);
//     glColor3fv(color);
//     glLineWidth(line_width);
//     glVertex2fv(new_start_point);
//     glVertex2fv(new_end_point);
//     glEnd();
// }

// static void allocate_memory_locations_in_heap()
// {
//     if (g_center == nullptr)
//     {
//         g_center = new GLfloat[2];
//     }

//     if (g_bob_center == nullptr)
//     {
//         g_bob_center = new GLfloat[2];
//     }

// #if defined SHOW_TRAILING_LINE == 1
//     if (g_previous_points_x_y == nullptr)
//     {
//         g_previous_points_x_y = new GLfloat[2 * N_PREVIOUS];
//     }
// #endif
// }

// static void deallocate_memory_locations_from_heap()
// {
//     delete[] g_center;
//     delete[] g_bob_center;
// #if defined SHOW_TRAILING_LINE == 1
//     delete[] g_previous_points_x_y;
// #endif
// }

// void initialize_simple_pendulum_simulation_with_defaults()
// {
//     allocate_memory_locations_in_heap();

//     g_center[0] = SCR_WIDTH / 2.0;
//     g_center[1] = SCR_HEIGHT;

//     g_radius = 400;

//     g_current_angle = 45;

//     g_bob_center[0] = 0;
//     g_bob_center[1] = 0;
// }

// void initialize_simple_pendulum_simulation(GLfloat center_x, GLfloat center_y, GLfloat new_radius, GLfloat initial_angle)
// {
//     allocate_memory_locations_in_heap();

//     g_center[0] = center_x;
//     g_center[1] = center_y;

//     g_radius = new_radius;

//     g_current_angle = initial_angle;

//     g_bob_center[0] = 0;
//     g_bob_center[1] = 0;
// }

// void simple_pendulum_simulation_step()
// {
//     glPointSize(5);

//     // calculating the center of the bob
//     g_bob_center[0] = g_center[0] + g_radius * cos(g_current_angle * M_PI / 180);
//     g_bob_center[1] = g_center[1] + g_radius * sin(-g_current_angle * M_PI / 180);

//     std::array<GLfloat, 2> normalized_bob_center_points = device_specific_to_normalized(g_bob_center[0], g_bob_center[1]);

// #if defined SHOW_TRAILING_LINE == 1
//     // displaying previous positions as trailing line
//     uint8_t starting_index = g_current_previous_index;
//     uint8_t ending_index = (g_current_previous_index + 2 * N_PREVIOUS - 1) % (2 * N_PREVIOUS);
//     float current_intensity = 0.01;
//     uint8_t visited = 0;
//     while (g_n_filled > 0 && visited < g_n_filled)
//     {
//         glColor3f(0.0, current_intensity, 0);
//         glBegin(GL_POINTS);
//         glVertex2f(g_previous_points_x_y[starting_index], g_previous_points_x_y[(starting_index + 1) % (N_PREVIOUS * 2)]);
//         glEnd();
//         starting_index = (starting_index + 2) % (N_PREVIOUS * 2);
//         visited = visited + 1;
//         current_intensity = 0.1 + (float)visited / (float)N_PREVIOUS;
//     }

//     g_previous_points_x_y[g_current_previous_index] = normalized_bob_center_points[0];
//     g_previous_points_x_y[(g_current_previous_index + 1) % (2 * N_PREVIOUS)] = normalized_bob_center_points[1];

//     g_n_filled = (g_n_filled + 1) > N_PREVIOUS ? N_PREVIOUS : (g_n_filled + 1);

//     g_current_previous_index = (g_current_previous_index + 2) % (N_PREVIOUS * 2);
// #endif
//     // drawing a line between center of pendulum and the center of bob
//     draw_line(g_center, g_bob_center, (GLfloat *)COLOR_BLUE);

//     // drawing a filled circle at the center of the bob
//     draw_filled_circle(g_bob_center, RADIUS_OF_BOB, (GLfloat *)COLOR_WHITE, (GLfloat *)COLOR_BLACK);

//     // plotting a point at center of the bob
//     glBegin(GL_POINTS);
//     glColor3fv(COLOR_RED);
//     glVertex2fv(normalized_bob_center_points.data());
//     glEnd();

//     // update for next cycle
//     g_current_acceleration = g_mass * g_acceleration_due_to_gravity_g / g_radius * cos(g_current_angle * M_PI / 180);
//     g_current_velocity += g_current_acceleration; // for large angles
//     g_current_velocity -= g_current_velocity * g_damping_factor;
//     g_current_angle += g_current_velocity;
// }

// void terminate_simple_pendulum_simulation()
// {
//     deallocate_memory_locations_from_heap();
// }





#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <array>

#include "globals.hpp"

// tunables
GLfloat g_radius = 0;
GLfloat g_mass = 1;
GLfloat g_acceleration_due_to_gravity_g = 9.8;
GLfloat g_damping_factor = 0.001;

// some instance parameters
GLfloat *g_center = nullptr;
GLfloat g_current_angle = 0;
GLfloat *g_bob_center = nullptr;
GLfloat g_current_acceleration;
GLfloat g_current_velocity;

#if defined SHOW_TRAILING_LINE==1
// previous points to track
constexpr uint8_t N_PREVIOUS = 100;
GLfloat *g_previous_points_x_y = nullptr;
uint8_t g_current_previous_index = 0;
uint8_t g_n_filled = 0; // keeping track of number of filled entries initially
#endif

/**
 * Assuming the x and y dimension are of same scale
 */
static GLfloat normalize_length(GLfloat l)
{
    return l / SCR_WIDTH;
}

static std::array<GLfloat, 2> normalized_to_device_specific(GLfloat x, GLfloat y)
{
    return {
        (x + 1) * SCR_WIDTH / 2,
        (y + 1) * SCR_HEIGHT / 2};
}

static std::array<GLfloat, 2> device_specific_to_normalized(GLfloat x, GLfloat y)
{
    return {
        2 * (x / SCR_WIDTH) - 1,
        2 * (y / SCR_HEIGHT) - 1};
}

static void draw_hollow_circle_normalized(GLfloat center[2], GLfloat radius, GLfloat color[3])
{
    glColor3fv(color);

    glLineWidth(5);

    glBegin(GL_LINE_LOOP);

    for (uint16_t i = 0; i < N_LINES_FOR_CIRCLE; i++)
    {
        glVertex3f(
            center[0] + (radius * cos(2 * M_PI * i / N_LINES_FOR_CIRCLE)),
            center[1] + (radius * sin(2 * M_PI * i / N_LINES_FOR_CIRCLE)),
            0.0);
    }

    glEnd();
}

/**
 * The coordinates are in window specific format
 */
static void draw_hollow_circle(GLfloat center[2], GLfloat radius, GLfloat color[3])
{
    std::array<GLfloat, 2> temp = device_specific_to_normalized(center[0], center[1]);

    // creating copies
    GLfloat new_center[2] = {temp[0], temp[1]};
    GLfloat new_radius = normalize_length(radius);

    draw_hollow_circle_normalized(new_center, new_radius, color);
}

/**
 * The coordinates are in normalized format [-1,1]
 */
static void draw_filled_circle(GLfloat center[2], GLfloat radius, GLfloat background_color[3], GLfloat circle_color[3])
{
    std::array<GLfloat, 2> temp = device_specific_to_normalized(center[0], center[1]);

    // creating copies
    GLfloat new_center[2] = {temp[0], temp[1]};
    GLfloat new_radius = normalize_length(radius);

    glColor3fv(background_color);

    // draw circle

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(new_center[0], new_center[1]); // the first vertex of triangle is the center of circle
    for (uint16_t i = 0; i < N_TRIANGLES_FOR_FILLED_CIRCLE; i++)
    {
        glVertex2f(
            new_center[0] + (new_radius * cos(2 * M_PI * i / N_TRIANGLES_FOR_FILLED_CIRCLE)),
            new_center[1] + (new_radius * sin(2 * M_PI * i / N_TRIANGLES_FOR_FILLED_CIRCLE)));
    }
    // adding these two as the last triangle drawn was incomplete
    glVertex2f(new_center[0], new_center[1] + new_radius);
    glVertex2f(new_center[0], new_center[1]);
    glEnd();

    if (circle_color != nullptr)
    {
        glLineWidth(5);

        // draw circle

        draw_hollow_circle_normalized(new_center, new_radius, circle_color);
    }
}

static void draw_line(GLfloat start_point[2], GLfloat end_point[2], GLfloat color[3], int line_width = 5)
{
    // creating copies
    auto temp1 = device_specific_to_normalized(start_point[0], start_point[1]);
    GLfloat new_start_point[2] = {temp1[0], temp1[1]};
    auto temp2 = device_specific_to_normalized(end_point[0], end_point[1]);
    GLfloat new_end_point[2] = {temp2[0], temp2[1]};

    glBegin(GL_LINES);
    glColor3fv(color);
    glLineWidth(line_width);
    glVertex2fv(new_start_point);
    glVertex2fv(new_end_point);
    glEnd();
}

static void allocate_memory_locations_in_heap()
{
    if (g_center == nullptr)
    {
        g_center = new GLfloat[2];
    }

    if (g_bob_center == nullptr)
    {
        g_bob_center = new GLfloat[2];
    }

#if defined SHOW_TRAILING_LINE == 1
    if (g_previous_points_x_y == nullptr)
    {
        g_previous_points_x_y = new GLfloat[2 * N_PREVIOUS];
    }
#endif
}

static void deallocate_memory_locations_from_heap()
{
    delete[] g_center;
    delete[] g_bob_center;
#if defined SHOW_TRAILING_LINE == 1
    delete[] g_previous_points_x_y;
#endif
}

void initialize_simple_pendulum_simulation_with_defaults()
{
    allocate_memory_locations_in_heap();

    g_center[0] = SCR_WIDTH / 2.0;
    g_center[1] = SCR_HEIGHT;

    g_radius = 400;

    g_current_angle = 45;

    g_bob_center[0] = 0;
    g_bob_center[1] = 0;

    g_current_velocity = 0; // Reset velocity
    g_current_acceleration = 0; // Reset acceleration
}

void initialize_simple_pendulum_simulation(GLfloat center_x, GLfloat center_y, GLfloat new_radius, GLfloat initial_angle)
{
    allocate_memory_locations_in_heap();

    g_center[0] = center_x;
    g_center[1] = center_y;

    g_radius = new_radius;

    g_current_angle = initial_angle;

    g_bob_center[0] = 0;
    g_bob_center[1] = 0;

    // g_current_velocity = 0; // Reset velocity
    // g_current_acceleration = 0; // Reset acceleration
}

void simple_pendulum_simulation_step()
{
    glPointSize(5);

    // calculating the center of the bob
    g_bob_center[0] = g_center[0] + g_radius * cos(g_current_angle * M_PI / 180);
    g_bob_center[1] = g_center[1] + g_radius * sin(-g_current_angle * M_PI / 180);

    std::array<GLfloat, 2> normalized_bob_center_points = device_specific_to_normalized(g_bob_center[0], g_bob_center[1]);

#if defined SHOW_TRAILING_LINE == 1
    // displaying previous positions as trailing line
    uint8_t starting_index = g_current_previous_index;
    uint8_t ending_index = (g_current_previous_index + 2 * N_PREVIOUS - 1) % (2 * N_PREVIOUS);
    float current_intensity = 0.01;
    uint8_t visited = 0;
    while (g_n_filled > 0 && visited < g_n_filled)
    {
        glColor3f(0.0, current_intensity, 0);
        glBegin(GL_POINTS);
        glVertex2f(g_previous_points_x_y[starting_index], g_previous_points_x_y[(starting_index + 1) % (N_PREVIOUS * 2)]);
        glEnd();
        starting_index = (starting_index + 2) % (N_PREVIOUS * 2);
        visited = visited + 1;
        current_intensity = 0.1 + (float)visited / (float)N_PREVIOUS;
    }

    g_previous_points_x_y[g_current_previous_index] = normalized_bob_center_points[0];
    g_previous_points_x_y[(g_current_previous_index + 1) % (2 * N_PREVIOUS)] = normalized_bob_center_points[1];

    g_n_filled = (g_n_filled + 1) > N_PREVIOUS ? N_PREVIOUS : (g_n_filled + 1);

    g_current_previous_index = (g_current_previous_index + 2) % (N_PREVIOUS * 2);
#endif
    // drawing a line between center of pendulum and the center of bob
    draw_line(g_center, g_bob_center, (GLfloat *)COLOR_BLUE);

    // drawing a filled circle at the center of the bob
    draw_filled_circle(g_bob_center, 50, (GLfloat *)COLOR_WHITE, (GLfloat *)COLOR_BLACK);

    // plotting a point at center of the bob
    glBegin(GL_POINTS);
    glColor3fv(COLOR_RED);
    glVertex2fv(normalized_bob_center_points.data());
    glEnd();

    // update for next cycle
    g_current_acceleration = g_mass * g_acceleration_due_to_gravity_g / g_radius * cos(g_current_angle * M_PI / 180);
    g_current_velocity += g_current_acceleration; // for large angles
    g_current_velocity -= g_current_velocity * g_damping_factor;
    g_current_angle += g_current_velocity;
}

void terminate_simple_pendulum_simulation()
{
    deallocate_memory_locations_from_heap();
}
