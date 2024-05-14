#pragma once

// settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 800;

constexpr float BACKGROUND_COLOR[4] = {0.1, 0.2, 0.3, 1.0}; 
// constexpr float BACKGROUND_COLOR[4] = {1.0, 1.0, 1.0, 1.0}; 
constexpr float COLOR_YELLOW[3] = {244 / 255.0, 232 / 255.0, 112 / 255.0};
constexpr float COLOR_BLACK[3] = {0.0, 0.0, 0.0};
constexpr float COLOR_WHITE[3] = {1.0, 1.0, 1.0};
constexpr float COLOR_RED[3] = {1.0, 0.0, 0.0};
constexpr float COLOR_GREEN[3] = {0.0, 1.0, 0.0};
constexpr float COLOR_BLUE[3] = {0.0, 0.0, 1.0};

constexpr uint16_t N_LINES_FOR_CIRCLE = 200;

constexpr uint16_t N_TRIANGLES_FOR_FILLED_CIRCLE = 200;

extern GLfloat g_radius;
extern GLfloat g_mass;
extern GLfloat g_acceleration_due_to_gravity_g;
extern GLfloat g_damping_factor;

// Define other global variables here
extern GLfloat *g_center;
extern GLfloat g_current_angle;
extern GLfloat *g_bob_center;
extern GLfloat g_current_acceleration;
extern GLfloat g_current_velocity;

extern uint8_t g_current_previous_index;
extern uint8_t g_n_filled; // keeping track of number of filled entries initially
