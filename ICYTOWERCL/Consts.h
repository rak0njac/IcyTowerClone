#pragma once
#include <SFML/Graphics.hpp>

const int const_cam_start_step = 496;
const float const_cam_speed_delta = 0.125f;
const int const_cam_catchup_top_bound = 200;
const int const_cam_catchup_bottom_bound = 100;
const int const_cam_catchup_top_max_speed = 25;
const int const_cam_catchup_bottom_max_speed = 15;
const float const_cam_catchup_top_delta_speed = 0.066f;
const float const_cam_catchup_bottom_delta_speed = 0.1f;
const float const_cam_catchup_slowdown_delta_speed = 0.05f;

const float const_eyecandy_gravity = 0.075f;

const int const_dist_between_platforms = 80;

const float const_player_gravity = 0.225f;
const float const_player_start_pos_x = 180;
const float const_player_start_pos_y = 417;
const int const_left_bound = 87;
const int const_right_bound = 553;
const int const_chock_anim_trigger_bound = 140;
const float const_player_xspeed_max = 6;
const float const_player_yspeed_max = 6;
const float const_player_slowdown_delta = 0.75f;
const float const_player_accelerate_delta = 0.085f;
const float const_player_friction_delta = 0.14f;

const sf::Color const_color_outline(1, 26, 51, 255);
const int const_text_size_small = 20;
const int const_text_size_medium = 30;
const int const_text_size_large = 140;
const int const_text_outline_small = 1;
const int const_text_outline_medium = 2;
const int const_text_outline_large = 7;

const int const_timer_start_pos_x = 42;
const int const_timer_start_pos_y = 56;
const int const_timer_start_bound = 20;