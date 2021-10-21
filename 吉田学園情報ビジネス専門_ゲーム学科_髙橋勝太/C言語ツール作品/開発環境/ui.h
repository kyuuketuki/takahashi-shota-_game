#ifndef _UI_H_
#define _UI_H_

#include "main.h"

//-----------------------------------------------------------------------------
//�\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 move;						//�ړ���
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	int nLife;
	int nType;
	float fWidth;
	float fHeigth;
	int nLifeBullet;
	bool bUse;
}UI;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitUi(void);//����������
void UninitUi(void);//�I������
void UpdateUi(void);//�X�V����
void DrawUi(void);//�`�揈��
//void SetUi(D3DXVECTOR3 pos, int nType);
void SetFire(D3DXVECTOR3 pos);
void SetWater(D3DXVECTOR3 pos);
void SetVertexUi(int nIdx);
#endif
