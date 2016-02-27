#ifndef __KON_DEFINITIONS_H__
#define __KON_DEFINITIONS_H__

#define WINDOW_TITLE "Break Out Lite"

#define SPRITE_PATH_DEFAULT "test/tile_test01_16x16.png"
#define SPRITE_PATH_BALL "ball.png"
#define SPRITE_PATH_PADDLE "paddle.png"
#define SPRITE_PATH_BRICK_1 "brick01.png"
#define SPRITE_PATH_BRICK_2 "brick02.png"
#define SPRITE_PATH_BRICK_3 "brick03.png"
#define SPRITE_PATH_BRICK_4 "brick04.png"

#define TAG_EDGE 0
#define TAG_BALL 1
#define TAG_PADDLE 2
#define TAG_BRICK 3

#define SCALE_BALL 1.0f
#define SCALE_PADDLE 1.0f
#define SCALE_PADDLE_WIDTH 2
#define SCALE_BRICK 1.0f

#define SPEED_PADDLE 8
#define SPEED_PADDLE_MULTIPLIER 1.5f
#define SPEED_BALL_DEFAULT 1010000.0f
#define SPEED_BALL_MULTIPLIER 1
#define SPEED_BALL_X 110000.0f
#define SPEED_BALL_Y 110000.0f

#define TILE_SIZE 32
#define TILE_HEIGHT 16
#define TILE_WIDTH 64

#define COLLISION_BITMASK_NONE 0x000000
#define COLLISION_BITMASK_EDGE 0x000001
#define COLLISION_BITMASK_BALL 0x000001
#define COLLISION_BITMASK_PADDLE 0x000001
#define COLLISION_BITMASK_BRICK 0x000001

#define TRANSITION_TIME 0.5
#define TRANSITION_TIME_WIN 5
#define TRANSITION_TIME_LOSE 5

#define ZONE_NOSPAWN_HEIGHT 190

#define FONT_SIZE_1 24
#define FONT_SIZE_2 72
#define FONT_SIZE_3 42
#define FONT_SIZE_4 144

#endif