//=============================================================================
//
// ���C�g���� [light.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"
#include "manager.h"

#define MAX_LIGHT (3)

//=============================================================================
// �e�N���X�̒�`
//=============================================================================

//�p����`��N���X
class CLight
{
public:
	CLight();								//�R���X�g���N�^
	virtual ~CLight();						//�f�X�g���N�^

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

private:					
	D3DLIGHT9 m_light[3];	//���C�g���
};							

#endif