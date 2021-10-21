//==============================================================================
//
// ���b�V���t�B�[���h�̕`��kmeshfield.h�l
// AUTHOR : shouta takahashi
//
//==============================================================================
#pragma once
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define FIELD_MAX	(1)			// �t�B�[���h�̍ő吔
#define COLLISION_PARTS_MESH	(4 * FIELD_MAX)			// �����蔻��̖ʂ̐�

// ���b�V���t�B�[���h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;									// �ʒu
	D3DXVECTOR3 rot;									// �p�x
	D3DXMATRIX mtxWorld;								// ���[���h�}�g���b�N�X
	D3DXVECTOR3 g_posMeshfield;							// �ʒu
	D3DXVECTOR3 g_rotMeshfield;							// ����
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
}MeshField;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitMeshfield(void);					// 3D�|���S���̏���������
void UninitMeshfield(void);						// 3D�|���S���̏I������
void UpdateMeshfield(void);						// 3D�|���S���̍X�V����
void DrawMeshfield(void);						// 3D�|���S���̕`�揈��
MeshField *GetMesh(void);						// �v���C���[�̎擾
void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float X, float Z);
#endif
