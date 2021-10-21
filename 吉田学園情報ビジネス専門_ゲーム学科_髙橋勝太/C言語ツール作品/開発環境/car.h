//-----------------------------------------------------------------
//
// �v���C���[�̏��� (model.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _CAR_H_
#define _CAR_H_

#include "main.h"


typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOld;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 rotmove;		//����
	D3DXVECTOR3 rotDest;		//����
	D3DXVECTOR3 oldrotDest;		//����
	D3DXVECTOR3 MinCar;
	D3DXVECTOR3 MaxCar;
	float nSpeed;
	int nNumVtx;			//���_��
}CAR;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitCar(void);
void UninitCar(void);
void UpdateCar(void);
void DrawCar(void);
CAR *GetCar(void);

#endif

