#pragma once

#include <GameDev2D.h>

//I chose to make everything static so that it is created before everything else, i'm not sure if this is better but i'm just assuming it is

//Ship stuff
static const float ANGULAR_CHANGE = 200.0f; //In radians (~60 degrees)
static const float MAX_SPEED = 350.0f;
static const float RATE_OF_ACCELERATION = 125.0f;
static const float RADIANS = 0.4014f;
static const float THICKNESS = 4.0f;
static const float SHIP_SIZE = 30;

//Asteroid stuff
static const float RADIUS = 40.0f;
static const int NUM_ASTEROIDS = 20;

//Laser Stuff
static const float LASER_SPEED = 1200.0f;