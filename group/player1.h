#pragma once

#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 32

#define ACC_RUN 0.15	//��������x
#define ACC_STOP 0.10	//��܂�����x
#define VELOCITY_X_MAX 5//X�����̑��x�ő�

void PlayerSystemInit(void);
void PlayerInit(void);
void PlayerUpdate(void);
void PlayerDraw(void);

bool Player1HitCheck(XY sPos, XY sSize);
CHARACTER GetPlayerPos(void);

bool Player1GameOver(void);