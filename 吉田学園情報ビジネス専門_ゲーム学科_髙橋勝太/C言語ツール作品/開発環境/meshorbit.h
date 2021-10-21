//==============================================================================
//
// ���b�V���t�B�[���h�̕`��kmeshfield.h�l
// AUTHOR : shouta takahashi
//
//==============================================================================
#pragma once
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_
#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define ORBIT_MAX	(1)			// �t�B�[���h�̍ő吔
#define COLLISION_PARTS_MESH	(4 * ORBIT_MAX)			// �����蔻��̖ʂ̐�

// ���b�V���t�B�[���h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;									// �ʒu
	D3DXVECTOR3 pos2;									// �ړ�
	D3DXVECTOR3 rot;									// �p�x
	D3DXMATRIX mtxWorld;								// ���[���h�}�g���b�N�X
	D3DXVECTOR3 g_posMeshOrbit;							// �ʒu
	D3DXVECTOR3 g_rotMeshOrbit;							// ����
	D3DXVECTOR3 aPos[COLLISION_PARTS_MESH];				// �����蔻�蒸�_���
	D3DXVECTOR3 aVec[COLLISION_PARTS_MESH];				// �����蔻��x�N�g��
	D3DXVECTOR3 vec;
	D3DXVECTOR3 vecA;
	D3DXVECTOR3 vecB;
	D3DXVECTOR3 vec2;
	D3DXVECTOR3 vec2A;
	D3DXVECTOR3 vec2B;
	D3DXVECTOR3 vec3;
	D3DXVECTOR3 vtx;
	D3DXVECTOR3 posM;
	bool bUse;											// �g�p���Ă��邩
	int nAllPoint;										// �����_��
	int nPolygon;										// �|���S����
	int nIdxPoint;										// �C���f�b�N�X�o�b�t�@�̕K�v�Ȋm�ې�
	float fWidth;										// �|���S���������̕�
	float fDepth;										// �|���S���������̉��s
	int nWidth;											// �����̒��_��
	int nDepth;											// ���s�̒��_��
	float fWidthMax;									// �����̍ő�
	float fDepthMax;									// ���s�̍ő�
	float X;
	float Z;
	float nDate;
	float nDate2;
	int nType;

	D3DXMATRIX pMtxParent;
	D3DXVECTOR3 aOffice[2];							
	D3DXMATRIX aMtxWorldPoint[2];
	D3DXVECTOR3 aPospoint[2];

}MeshOrbit;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitMeshOrbit(void);					// 3D�|���S���̏���������
void UninitMeshOrbit(void);						// 3D�|���S���̏I������
void UpdateMeshOrbit(void);						// 3D�|���S���̍X�V����
void DrawMeshOrbit(void);						// 3D�|���S���̕`�揈��
MeshOrbit *GetOrbit(void);						// �v���C���[�̎擾
void SetOrbit(D3DXVECTOR3 pos, D3DXVECTOR3 pos2);
void CollisionVecMesh(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);

#endif
