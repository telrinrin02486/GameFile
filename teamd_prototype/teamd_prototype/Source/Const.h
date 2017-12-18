#pragma once

#include "Vector2.h"
#include "Rect2.h"

constexpr unsigned int WINDOW_WIDTH = 640;
constexpr unsigned int WINDOW_HEIGHT = 480;

const Vector2 PLAYER_SIZE(200, 200);
const Vector2 CB1_SIZE(50,50);

const Vector2 PLAYER_POS(WINDOW_WIDTH / 2 - PLAYER_SIZE.x *0.5f + 30.0f, 0);
const Vector2 CB1_POS(WINDOW_WIDTH / 2 - CB1_SIZE.x *0.5f, WINDOW_HEIGHT - CB1_SIZE.y);

const Rect2 PLAYER_RECT(PLAYER_POS, PLAYER_SIZE);
const Rect2 CB1_RECT(CB1_POS, CB1_SIZE);