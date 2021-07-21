#pragma once
#define VECTOR_SLIDE 0.86602540378

int Input_PlayerMoveDir();

void P_input_move();
void P_move();

void Sph_Gravity();

enum Dir { Left, Right, Down, Up };
