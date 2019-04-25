
#include "main.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"


CHARACTER player1;
int player1Image[2];

void PlayerSystemInit(void)
{
	LoadDivGraph("image/player1.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, player1Image);
}

void PlayerInit(void)
{
	//������
	player1.pos = { 5 * MAP_CHIP_SIZE_X, 8 * MAP_CHIP_SIZE_Y };
	player1.size = { 32, 64 };
	player1.sizeOffset = { (player1.size.x / 2), (player1.size.y / 2) };
	player1.hitPosS = { 20, 16 };
	player1.hitPosE = { 20, 32 };
	player1.moveSpeed = 4;
	player1.Velocity = { 0,0 };
	player1.damageFlag = false;
	player1.jumpFlag = false;
	player1.runFlag = false;
	player1.shotFlag = false;
	player1.movedir = DIR_RIGHT;
	player1.imgLockCnt = 30;
	player1.flag = true;
}

void PlayerUpdate(void)
{
	if (player1.flag == true) {
		//XY movedOffset = { 0, player1.pos.y - player1.sizeOffset.y / 2 };

		bool playerMoved = false;

		//�E�ɑ���
		player1.runFlag = false;
		if (newkey[P1_RIGHT]) {
			playerMoved = true;
			player1.runFlag = true;
			player1.movedir = DIR_RIGHT;
			player1.Velocity.x += ACC_RUN;
			if (player1.Velocity.x > VELOCITY_X_MAX)player1.Velocity.x = VELOCITY_X_MAX;
		}
		//���ɑ���
		if (newkey[P1_LEFT]) {
			playerMoved = true;
			player1.runFlag = true;
			player1.movedir = DIR_LEFT;
			player1.Velocity.x -= ACC_RUN;
			if (player1.Velocity.x < -VELOCITY_X_MAX)player1.Velocity.x = -VELOCITY_X_MAX;
		}

		if (player1.runFlag == false) {	//�����L�[���͂��Ȃ��ꍇ�́A�~�܂낤�Ƃ���
			//�i�K�I�ɑ��x�𗎂Ƃ�
			if (player1.Velocity.x < 0) {
				player1.Velocity.x += ACC_STOP * 1;
				if (player1.Velocity.x > 0)player1.Velocity.x = 0;
			}
			else if (player1.Velocity.x > 0) {
				player1.Velocity.x -= ACC_STOP * 1;
				if (player1.Velocity.x < 0)player1.Velocity.x = 0;
			}
		}

		XY movedPos = player1.pos;
		XY movedHitCheck = movedPos;
		XY movedHitCheck2 = movedPos;
		XY movedHitCheck3 = movedPos;
		XY tmpIndex;
		XY tmpPos;

		movedPos.x += player1.Velocity.x * 1;

		if (player1.Velocity.x < 0) {
			movedHitCheck.x = movedPos.x - player1.hitPosS.x;
		}
		else if (player1.Velocity.x > 0) {
			movedHitCheck.x = movedPos.x + player1.hitPosE.x;
		}

		movedHitCheck2 = movedHitCheck;
		movedHitCheck2.y = movedPos.y + player1.hitPosS.y;

		movedHitCheck3 = movedHitCheck;
		movedHitCheck3.y = movedPos.y - player1.hitPosE.y;

		//�ʂ�邩�ǂ���
		if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
			player1.pos = movedPos;
		}
		else {
			tmpIndex = MapPosToIndex(movedHitCheck);	//�u���b�N�̏�̍��W���v�Z
			if (player1.Velocity.x < 0) {
				tmpIndex.x++;
				tmpPos = MapIndexToPos(tmpIndex);			//�����̂����W
				player1.pos.x = tmpPos.x + player1.hitPosE.x;	//�������璆�S�����߂�
			}
		}

		player1.jumpFlag = true;
		//�v���C���[1�W�����v
		if (player1.jumpFlag == true) {
			XY movedPos = player1.pos;
			XY movedHitCheck = movedPos;
			XY movedHitCheck2 = movedPos;
			XY movedHitCheck3 = movedPos;
			XY tmpIndex;
			XY tmpPos;

			movedPos.y -= player1.Velocity.y * SECOND_PER_FRAME;
			player1.Velocity.y -= ACC_G * SECOND_PER_FRAME;

			movedHitCheck.y = movedPos.y - player1.hitPosS.y;	//����̍��W�v�Z
			//����̉E��
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + player1.hitPosS.x;
			//����̍���
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - player1.hitPosS.x;
			//����Ƀu���b�N�����邩�ǂ���
			//�ʂ�邩�ǂ���
			if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
				player1.pos = movedPos;
			}
			else {
				tmpIndex = MapPosToIndex(movedHitCheck);
				//	movedHitCheck.y / 32
				tmpIndex.y++;
				tmpPos = MapIndexToPos(tmpIndex);
				//	(movedHitCheck.y / 32) * 32
				player1.pos.y = tmpPos.y + player1.hitPosS.y;	//���ォ�璆�S�����߂�
				player1.Velocity.y *= -1;

				movedPos = player1.pos;
			}

			movedHitCheck.y = movedPos.y + player1.hitPosE.y;	//�����̍��W�v�Z
			//�����E��
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + player1.hitPosE.x;
			//��������
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - player1.hitPosE.x;

			//�����Ƀu���b�N�����邩�ǂ���
			//�ʂ�邩�ǂ���
			if (player1.Velocity.y < 0) {
				if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
					player1.pos = movedPos;
				}
				else {
					tmpIndex = MapPosToIndex(movedHitCheck);	//�u���b�N�̏�̍��W���v�Z
																//	movedHitCheck.y / 32
					tmpPos = MapIndexToPos(tmpIndex);			//�����̂����W
																//	(movedHitCheck.y / 32) * 32
					player1.pos.y = tmpPos.y - player1.hitPosE.y;	//�������璆�S�����߂�
					player1.Velocity.y = 0;
					player1.jumpFlag = false;
				}
			}
		}
		if (player1.jumpFlag == false) {
			if (trgkey[P1_UP]) {
				player1.jumpFlag = true;
				player1.Velocity.y = INIT_VELOCITY;
			}
		}
	}

	//��莞�ԃC���[�W�̌Œ�
	if (player1.imgLockCnt < 0) {
		player1.shotFlag = false;
		player1.damageFlag = false;
		player1.imgLockCnt = 30;
	}

}

void PlayerDraw(void)
{
	player1.animCnt++;
	player1.pos = { SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 };
	DrawGraph(player1.pos.x, player1.pos.y, player1Image[player1.animCnt], true);
}