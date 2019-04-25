#pragma once

#define MAP_CHIP_X 30
#define MAP_CHIP_Y 20

#define MAP_CHIP_SIZE_X 32
#define MAP_CHIP_SIZE_Y 32

//�v���g�^�C�v�錾
void stageSystemInit(void);
void stageInit(void);
void stageUpdate(void);
void stageDraw(void);

XY MapPosToIndex(XY pos);
XY MapIndexToPos(XY Index);
bool IsPass(XY pos);