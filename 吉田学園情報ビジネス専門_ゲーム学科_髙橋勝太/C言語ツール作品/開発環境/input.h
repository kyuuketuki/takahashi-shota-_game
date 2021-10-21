//-----------------------------------------------------------------
//
// �{�^���̏��� (input.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//==============================================================================
// �L�[����
//==============================================================================
typedef enum
{
	RETURN,
	X,
	W,
	S,
	A,
	D,
	SPACE,
	BACKSPACE,
	F,
	T,
	B,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	P,
	KEYINFO_MAX
} KEYINFO;

//----------------------
//�v���g�^�C�v�錾
//----------------------
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
int GetPress(int nKey);
//bool GetKeyboardRepeat(int nKey);

#endif