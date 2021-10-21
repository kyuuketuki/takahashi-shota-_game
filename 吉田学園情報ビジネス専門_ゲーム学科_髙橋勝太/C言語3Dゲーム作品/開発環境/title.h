#pragma once
//-----------------------------------------------------------------
//
// �^�C�g���̏��� (title.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "input.h"


typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	int nType;//���
	bool bUse;
	int nCounterAnim;						//�A�j���[�V�����J�E���^�[
	int nPatternAnim;						//�A�j���[�V�����p�^�[��No.
	int nseetAni;
}TITLE;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetVertexTexture(int nType);
#endif
