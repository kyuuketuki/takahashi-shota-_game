#pragma once
//-----------------------------------------------------------------
//
// ���U���g��� (result.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "input.h"

//-----------------------------------------------------------------------------
// ���U���g��ʂ̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	int nType;		//���
	int nData;
}RESULT;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetVertexTextureResult(int nType);
int GetResultclear(void);
#endif
