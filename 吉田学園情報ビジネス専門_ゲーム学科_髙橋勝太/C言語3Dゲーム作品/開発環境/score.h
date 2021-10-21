
//-----------------------------------------------------------------
//
// �X�R�A�̏��� (score.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "game.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_SCORE	(3)			// ���̍ő吔
#define  SCORE_SIZE (35)

//-----------------------------------------------------------------------------
// �\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;
	int nType;
	bool bUse;
}SCORE;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nValue);
void SetScore(D3DXVECTOR3 pos, int nType);
void SetVertexScore(int nIdx);

SCORE*GetScore(void);

#endif
