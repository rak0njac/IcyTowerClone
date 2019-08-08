#pragma once

const int const_cam_start_step = 496;
const float const_cam_speed_delta = 0.125f;
const int const_cam_catchup_top_bound = 200;
const int const_cam_catchup_bottom_bound = 100;
const int const_cam_catchup_top_max_speed = 20;
const int const_cam_catchup_bottom_max_speed = 12;
const float const_cam_catchup_top_delta_speed = 0.066f;
const float const_cam_catchup_bottom_delta_speed = 0.1f;
const float const_cam_catchup_slowdown_delta_speed = 0.05f;

class Camera
{
private:
	static int camLevel;
	static float camSpeed;
public:
	static int& getCamLevel();
	static float& getCamSpeed();
	static void setCamLevel(int value);
	static void setCamSpeed(float value);
};