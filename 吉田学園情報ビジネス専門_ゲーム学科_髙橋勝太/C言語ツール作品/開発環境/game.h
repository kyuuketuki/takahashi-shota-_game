#pragma once
//-----------------------------------------------------------------
//
// �Q�[�����e�̏��� (game.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

typedef struct
{
	float X;
	float Y;
	float Z;
	float Rot;
	int Type;
}FAILDATE;

//----------------------
//�v���g�^�C�v�錾
//----------------------
HRESULT InitGame();
void UninitGame(void);
void UpdatetGame(void);
void DrawGame(void);
int GetGame(void);
int GetItem(void);
bool PauseGame(void);

#endif
