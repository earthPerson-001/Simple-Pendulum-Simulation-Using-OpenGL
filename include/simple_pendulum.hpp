#pragma once

// #define SHOW_TRAILING_LINE 0

constexpr int RADIUS_OF_BOB = 50;

void initialize_simple_pendulum_simulation_with_defaults();
void initialize_simple_pendulum_simulation(GLfloat center_x, GLfloat center_y, GLfloat new_radius, GLfloat initial_angle);
void simple_pendulum_simulation_step();
void terminate_simple_pendulum_simulation();
