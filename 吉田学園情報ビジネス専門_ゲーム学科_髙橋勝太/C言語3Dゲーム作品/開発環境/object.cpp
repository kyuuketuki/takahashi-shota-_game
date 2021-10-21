//==============================================================================
//
// 3D���f���̕`��kobject.cpp�l
// AUTHOR : TAKAHASHI SHOTA
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "object.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "math.h"
#include "game.h"
#include "effect.h"
#include "fade.h"
#include "score.h"
#include "sound.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_OBJECT_TYPE		(19)		// �^�C�v��
#define TEXT_LENGTH			(128)		// �e�L�X�g�ǂݍ��݂̍ő吔
#define DATA_LENGTH			(64)		// �f�[�^�ǂݍ��݂̍ő吔

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPD3DXMESH g_pMeshObject[MAX_OBJECT_TYPE] = {};				// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObject[MAX_OBJECT_TYPE] = {};		// �}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatObject = 0;									// �}�e���A���̐�
OBJECT object[MAX_OBJECT];
int g_nCnyDateObject;
int g_nDateObjectNumber = 0;
int g_nDateObjectNumber2 = 0;
int MaxOject = 0;
int MaxOjectType = 0;
int g_FailCntDateObject = 0;
int nItemScoe = 0;										//�A�C�e����
int g_Clear = 0;										//�N���A����
int LoadData = 0;										//��񂾂��ǂݍ���

//==============================================================================
// ����������
//==============================================================================
HRESULT InitObject(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	//�O���[�o���ϐ��ɋL��������
	MaxOject = MAX_OBJECT;
	MaxOjectType = MAX_OBJECT_TYPE;

	//����������
	nItemScoe = 0;									//�A�C�e�����萔
	g_Clear = 0;									//�N���A����

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/wilderness cactus.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[18], NULL, &g_nNumMatObject, &g_pMeshObject[18]);
	D3DXLoadMeshFromX("data/MODEL/wilderness grass.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[17], NULL, &g_nNumMatObject, &g_pMeshObject[17]);
	D3DXLoadMeshFromX("data/MODEL/wilderness stone.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[16], NULL, &g_nNumMatObject, &g_pMeshObject[16]);
	D3DXLoadMeshFromX("data/MODEL/wilderness stone2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[15], NULL, &g_nNumMatObject, &g_pMeshObject[15]);
	D3DXLoadMeshFromX("data/MODEL/wilderness tree.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[14], NULL, &g_nNumMatObject, &g_pMeshObject[14]);
	D3DXLoadMeshFromX("data/MODEL/container.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[13], NULL, &g_nNumMatObject, &g_pMeshObject[13]);
	D3DXLoadMeshFromX("data/MODEL/tree.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[12], NULL, &g_nNumMatObject, &g_pMeshObject[12]);
	D3DXLoadMeshFromX("data/MODEL/stone2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[11], NULL, &g_nNumMatObject, &g_pMeshObject[11]);
	D3DXLoadMeshFromX("data/MODEL/stone.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[10], NULL, &g_nNumMatObject, &g_pMeshObject[10]);
	D3DXLoadMeshFromX("data/MODEL/fence101.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[9], NULL, &g_nNumMatObject, &g_pMeshObject[9]);
	D3DXLoadMeshFromX("data/MODEL/bench.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[8], NULL, &g_nNumMatObject, &g_pMeshObject[8]);
	D3DXLoadMeshFromX("data/MODEL/tree000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[7], NULL, &g_nNumMatObject, &g_pMeshObject[7]);
	D3DXLoadMeshFromX("data/MODEL/glass000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[6], NULL, &g_nNumMatObject, &g_pMeshObject[6]);
	D3DXLoadMeshFromX("data/MODEL/building04.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[5], NULL, &g_nNumMatObject, &g_pMeshObject[5]);
	D3DXLoadMeshFromX("data/MODEL/building03.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[4], NULL, &g_nNumMatObject, &g_pMeshObject[4]);
	D3DXLoadMeshFromX("data/MODEL/tower000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[3], NULL, &g_nNumMatObject, &g_pMeshObject[3]);
	D3DXLoadMeshFromX("data/MODEL/����.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[2], NULL, &g_nNumMatObject, &g_pMeshObject[2]);
	D3DXLoadMeshFromX("data/MODEL/building00.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[1], NULL, &g_nNumMatObject, &g_pMeshObject[1]);
	D3DXLoadMeshFromX("data/MODEL/baloon01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[0], NULL, &g_nNumMatObject, &g_pMeshObject[0]);

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// ���_�����擾
		object[nCntObject].nNumVtx = g_pMeshObject[object[nCntObject].nType]->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
		object[nCntObject].sizeFVF = D3DXGetFVFVertexSize(g_pMeshObject[object[nCntObject].nType]->GetFVF());

		// �ϐ��̏�����
		object[nCntObject].pos = D3DXVECTOR3(0.0f, -5000.0f, 0.0f);
		object[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		object[nCntObject].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		object[nCntObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		object[nCntObject].bUse = false;
		object[nCntObject].nType = 0;
	}

	//��񂾂��ǂݍ���
	if (LoadData == 0)
	{
		//�O���I�u�t�@�C����ǂݍ���
		LoadObject();
		LoadData = 1;
	}

	for (int nCnt = 0; nCnt < g_FailCntDateObject; nCnt++)
	{
		//�O���t�@�C���̓ǂݍ���
		//�I�u�W�F�N�g�z�u
		SetObject(D3DXVECTOR3(object[nCnt].posX, object[nCnt].posY, object[nCnt].posZ),
			D3DXVECTOR3(object[nCnt].rotX, object[nCnt].rotY, object[nCnt].rotZ), object[nCnt].Type);
	}

	//// ���_�o�b�t�@�����b�N
	//g_pMeshObject[0]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&object[nCntObject].pVtxBuff);

	//// ���_���W�̔�r
	//for (int nCntVtx = 0; nCntVtx < object[nCntObject].nNumVtx; nCntVtx++)
	//{
	//	object[nCntObject].vtx = *(D3DXVECTOR3*)object[nCntObject].pVtxBuff;	// ���_���W�̑��

	//	// �e���W�̍ő�l�̔�r
	//	if (object[nCntObject].vtxMaxObject.x < object[nCntObject].vtx.x)
	//	{
	//		object[nCntObject].vtxMaxObject.x = object[nCntObject].vtx.x;
	//	}
	//	if (object[nCntObject].vtxMaxObject.y < object[nCntObject].vtx.y)
	//	{
	//		object[nCntObject].vtxMaxObject.y = object[nCntObject].vtx.y;
	//	}
	//	if (object[nCntObject].vtxMaxObject.z < object[nCntObject].vtx.z)
	//	{
	//		object[nCntObject].vtxMaxObject.z = object[nCntObject].vtx.z;
	//	}

	//	// �e���W�̍ŏ��l�̔�r
	//	if (object[nCntObject].vtxMinObject.x > object[nCntObject].vtx.x)
	//	{
	//		object[nCntObject].vtxMinObject.x = object[nCntObject].vtx.x;
	//	}
	//	if (object[nCntObject].vtxMinObject.y > object[nCntObject].vtx.y)
	//	{
	//		object[nCntObject].vtxMinObject.y = object[nCntObject].vtx.y;
	//	}
	//	if (object[nCntObject].vtxMinObject.z > object[nCntObject].vtx.z)
	//	{
	//		object[nCntObject].vtxMinObject.z = object[nCntObject].vtx.z;
	//	}

	//	object[nCntObject].pVtxBuff += object[nCntObject].sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	//}
	//// ���_�o�b�t�@���A�����b�N
	//g_pMeshObject[0]->UnlockVertexBuffer();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitObject(void)
{
	//// ���b�V���̔j��
	//if (g_pMeshObject[0] != NULL)
	//{
	//	g_pMeshObject[0]->Release();
	//	g_pMeshObject[0] = NULL;
	//}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < MAX_OBJECT_TYPE; nCntTexture++)
	{
		// ���b�V���̔j��
		if (g_pMeshObject[nCntTexture] != NULL)
		{
			g_pMeshObject[nCntTexture]->Release();
			g_pMeshObject[nCntTexture] = NULL;
		}

		// �}�e���A���̔j��
		if (g_pBuffMatObject[nCntTexture] != NULL)
		{
			g_pBuffMatObject[nCntTexture]->Release();
			g_pBuffMatObject[nCntTexture] = NULL;
		}
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateObject(void)
{
	//�ŐV�̃I�u�W�F�N�g������
	if (GetKeyboardTrigger(DIK_H) == true)
	{
		object[g_nDateObjectNumber - g_nDateObjectNumber2].bUse = false;

		//�ŐV�̃I�u�W�F�N�g��i�߂�
		g_nDateObjectNumber2 += 1;
	}

	if (GetKeyboardTrigger(DIK_G) == true)
	{
		//�ŐV�̃I�u�W�F�N�g��i�߂�
		g_nDateObjectNumber2 = 0;
	}

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// ���_�����擾
		object[nCntObject].nNumVtx = g_pMeshObject[object[nCntObject].nType]->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
		object[nCntObject].sizeFVF = D3DXGetFVFVertexSize(g_pMeshObject[object[nCntObject].nType]->GetFVF());

		// ���_�o�b�t�@�����b�N
		g_pMeshObject[object[nCntObject].nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&object[nCntObject].pVtxBuff);

		// ���_���W�̔�r
		for (int nCntVtx = 0; nCntVtx < object[nCntObject].nNumVtx; nCntVtx++)
		{
			object[nCntObject].vtx = *(D3DXVECTOR3*)object[nCntObject].pVtxBuff;	// ���_���W�̑��

			// �e���W�̍ő�l�̔�r
			if (object[nCntObject].vtxMaxObject.x < object[nCntObject].vtx.x)
			{
				object[nCntObject].vtxMaxObject.x = object[nCntObject].vtx.x;
			}
			if (object[nCntObject].vtxMaxObject.y < object[nCntObject].vtx.y)
			{
				object[nCntObject].vtxMaxObject.y = object[nCntObject].vtx.y;
			}
			if (object[nCntObject].vtxMaxObject.z < object[nCntObject].vtx.z)
			{
				object[nCntObject].vtxMaxObject.z = object[nCntObject].vtx.z;
			}

			// �e���W�̍ŏ��l�̔�r
			if (object[nCntObject].vtxMinObject.x > object[nCntObject].vtx.x)
			{
				object[nCntObject].vtxMinObject.x = object[nCntObject].vtx.x;
			}
			if (object[nCntObject].vtxMinObject.y > object[nCntObject].vtx.y)
			{
				object[nCntObject].vtxMinObject.y = object[nCntObject].vtx.y;
			}
			if (object[nCntObject].vtxMinObject.z > object[nCntObject].vtx.z)
			{
				object[nCntObject].vtxMinObject.z = object[nCntObject].vtx.z;
			}

			//tree�̏ꍇ�������ς���
			if (object[nCntObject].nType == 12)
			{
				object[nCntObject].vtxMaxObject.x = 5;
				object[nCntObject].vtxMaxObject.z = 5;
				object[nCntObject].vtxMinObject.x = -5;
				object[nCntObject].vtxMinObject.z = -5;
			}

			object[nCntObject].pVtxBuff += object[nCntObject].sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
		// ���_�o�b�t�@���A�����b�N
		g_pMeshObject[object[nCntObject].nType]->UnlockVertexBuffer();
	}

	//�N���A�����ɒB������
	if (nItemScoe >= g_Clear)
	{
		SetFade(FADE_OUT, MODE_RANKING);
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawObject(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&object[nCntObject].mtxWorld);

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, object[nCntObject].rot.y, object[nCntObject].rot.x, object[nCntObject].rot.z);
		D3DXMatrixMultiply(&object[nCntObject].mtxWorld, &object[nCntObject].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, object[nCntObject].pos.x, object[nCntObject].pos.y, object[nCntObject].pos.z);
		D3DXMatrixMultiply(&object[nCntObject].mtxWorld, &object[nCntObject].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &object[nCntObject].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		pMat = (D3DXMATERIAL*)g_pBuffMatObject[object[nCntObject].nType]->GetBufferPointer();

		//�g�p����Ă���Ƃ�
		if (object[nCntObject].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// ���f��(�p�[�c)�̕`��
				g_pMeshObject[object[nCntObject].nType]->DrawSubset(nCntMat);
			}
		}
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==============================================================================
// �I�u�W�F�N�g�̎擾
//==============================================================================
OBJECT *GetObject(void)
{
	return object;
}

//==============================================================================
// �O�ς𗘗p���������蔻��
//==============================================================================
bool CollisionVec(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{
	// ���[�J���ϐ��錾
	bool bLand = false;
	D3DXVECTOR3 aVec[COLLISION_PARTS];	// ��`���_���画��Ώۂւ̃x�N�g��
	float fPlayerVec[COLLISION_PARTS];	// �e�ʂ̃x�N�g���Ƃ̔���i�{�|�j
	D3DXVECTOR3 pos = *pPos;			// ����Ώۂ̈ʒu

	PLAYER *pModel;
	pModel = GetModel();

	int nCntObject = 0;
	int nCntObjectPlayerVec = 0;

	for (int nCntObjectUse = 0; nCntObjectUse < MAX_OBJECT; nCntObjectUse++)
	{
		//�g�p����Ă���Ƃ�
		if (object[nCntObjectUse].bUse == true)
		{
			for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
			{
				// �I�u�W�F�N�g��`�̊e���_
				object[nCntObject].aPos[0 + (4 * nCntObject)] = D3DXVECTOR3(object[nCntObject].pos.x + object[nCntObject].vtxMinObject.x, 0.0f, object[nCntObject].pos.z + object[nCntObject].vtxMinObject.z);	// ����O
				object[nCntObject].aPos[1 + (4 * nCntObject)] = D3DXVECTOR3(object[nCntObject].pos.x + object[nCntObject].vtxMinObject.x, 0.0f, object[nCntObject].pos.z + object[nCntObject].vtxMaxObject.z);	// ����
				object[nCntObject].aPos[2 + (4 * nCntObject)] = D3DXVECTOR3(object[nCntObject].pos.x + object[nCntObject].vtxMaxObject.x, 0.0f, object[nCntObject].pos.z + object[nCntObject].vtxMaxObject.z);	// �E��
				object[nCntObject].aPos[3 + (4 * nCntObject)] = D3DXVECTOR3(object[nCntObject].pos.x + object[nCntObject].vtxMaxObject.x, 0.0f, object[nCntObject].pos.z + object[nCntObject].vtxMinObject.z);	// �E��O
				
				// �I�u�W�F�N�g��`�̊e�ʂ̃x�N�g��
				object[nCntObject].aVec[0 + (4 * nCntObject)] = object[nCntObject].aPos[1 + (4 * nCntObject)] - object[nCntObject].aPos[0 + (4 * nCntObject)];
				object[nCntObject].aVec[1 + (4 * nCntObject)] = object[nCntObject].aPos[2 + (4 * nCntObject)] - object[nCntObject].aPos[1 + (4 * nCntObject)];
				object[nCntObject].aVec[2 + (4 * nCntObject)] = object[nCntObject].aPos[3 + (4 * nCntObject)] - object[nCntObject].aPos[2 + (4 * nCntObject)];
				object[nCntObject].aVec[3 + (4 * nCntObject)] = object[nCntObject].aPos[0 + (4 * nCntObject)] - object[nCntObject].aPos[3 + (4 * nCntObject)];
			}

			//����������
			g_nCnyDateObject = 0;
			nCntObject = 0;

			// �I�u�W�F�N�g�Ƃ̓����蔻��
			for (int nCnt = 0; nCnt < COLLISION_PARTS; nCnt++)
			{
				if (nCnt == 0 + g_nCnyDateObject)
				{// ����
					aVec[nCnt] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - object[nCntObject].aPos[nCnt];
				}
				else if (nCnt == 1 + g_nCnyDateObject)
				{// ����
					aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - object[nCntObject].aPos[nCnt];
				}
				else if (nCnt == 2 + g_nCnyDateObject)
				{// �E��
					aVec[nCnt] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - object[nCntObject].aPos[nCnt];
				}
				else if (nCnt == 3 + g_nCnyDateObject)
				{// ��O
					aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - object[nCntObject].aPos[nCnt];
				}

				// ���l���u+�v�̎��A�����蔻�肪�L��
				fPlayerVec[nCnt] = (object[nCntObject].aVec[nCnt].z * aVec[nCnt].x) - (object[nCntObject].aVec[nCnt].x * aVec[nCnt].z);

				if (pPos->y <= object[nCntObject].pos.y + object[nCntObject].vtxMaxObject.y - fHeightMin && pPos->y > object[nCntObject].pos.y + object[nCntObject].vtxMinObject.y - fHeightMax)
				{
					if (fPlayerVec[0 + (4 * nCntObject)] > 0.0f && fPlayerVec[1 + (4 * nCntObject)] > 0.0f && fPlayerVec[2 + (4 * nCntObject)] > 0.0f && fPlayerVec[3 + (4 * nCntObject)] > 0.0f)
					{

						//�g�p����Ă���Ƃ�
						if (object[nCntObjectUse].bUse == true)
						{
							if (pPos->x > pPosOld->x && pPosOld->x < object[nCntObject].pos.x + object[nCntObject].vtxMinObject.x)
							{
								// ����	
								pPos->x = object[nCntObject].pos.x + object[nCntObject].vtxMinObject.x - fWidthMax;
								ObjectFalseType(nCntObject, object[nCntObject].nType);
							}
							else if (pPos->x < pPosOld->x && pPosOld->x > object[nCntObject].pos.x + object[nCntObject].vtxMaxObject.x)
							{
								// �E��	
								pPos->x = object[nCntObject].pos.x + object[nCntObject].vtxMaxObject.x - fWidthMin;
								ObjectFalseType(nCntObject, object[nCntObject].nType);
							}
							else if (pPos->z < pPosOld->z && pPos->z > object[nCntObject].pos.z + object[nCntObject].vtxMaxObject.z)
							{
								// ����
								pPos->z = object[nCntObject].pos.z + object[nCntObject].vtxMaxObject.z - fDepthMin;
								ObjectFalseType(nCntObject, object[nCntObject].nType);
							}
							else if (pPos->z > pPosOld->z && pPos->z < object[nCntObject].pos.z + object[nCntObject].vtxMinObject.z)
							{
								// ��O
								pPos->z = object[nCntObject].pos.z + object[nCntObject].vtxMinObject.z - fDepthMax;
								ObjectFalseType(nCntObject, object[nCntObject].nType);
							}

							else if (pPos->y < pPosOld->y && pPos->y > object[nCntObject].pos.y + object[nCntObject].vtxMaxObject.y)
							{
								// ���
								pPos->y = object[nCntObject].pos.y + object[nCntObject].vtxMaxObject.y - fHeightMax;
								ObjectFalseType(nCntObject, object[nCntObject].nType);

								//�W�����v�����B��
								pModel->block = false;

								//�ʒu��߂�
								pPos->y = pPosOld->y;
							}
						}
					}
				}

				//���̃I�u�W�F�N�g�̓����蔻��
				if (nCnt == 3 + (4 * nCntObject))
				{
					//������ς���
					g_nCnyDateObject += 4;

					//���̃I�u�W�F�N�g��
					nCntObject += 1;
				}
			}
		}
	}
	return bLand;
}

//==============================================================================
// �I�u�W�F�N�g�̐ݒ�
//==============================================================================
void SetObject(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, int nType)
{
	//VERTEX_3D *pVtx;
	//LPDIRECT3DDEVICE9 pDevice;

	////�f�o�C�X�̎擾
	//pDevice = GetDevice();

	if (nType == 0)
	{
		g_Clear++;
	}

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// ���_�o�b�t�@�����b�N
		g_pMeshObject[0]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&object[nCntObject].pVtxBuff);

		//�g�p����Ă���Ƃ�
		if (object[nCntObject].bUse == false)
		{
			//�ʒu
			object[nCntObject].pos = Pos;

			//����
			object[nCntObject].rot = rot;

			//�^�C�v
			object[nCntObject].nType = nType;

			//�g�p����
			object[nCntObject].bUse = true;

			//��O�̃I�u�W�F�N�g���L��
			g_nDateObjectNumber = nCntObject;

			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pMeshObject[0]->UnlockVertexBuffer();
}

//==============================================================================
//�I�u�W�F�N�g����������
//==============================================================================
void ObjectFalseType(int nCnt , int nType)
{
		if (nType == 0)
		{
			//�p�[�e�B�N��
			SetFire(object[nCnt].pos);

			//�T�E���h������
			PlaySound(SOUND_LABEL_SE_EXPLOSION);

			//�X�R�A���Z
			AddScore(1);

			//�N���A����
			nItemScoe++;

			object[nCnt].pos = D3DXVECTOR3(0.0f, -1000.0f, 0.0f);
			object[nCnt].bUse = false;
		}
}
//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
int GetobjectNumber(void)
{
	return MaxOject;
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
int GetobjectDate(void)
{
	return g_nDateObjectNumber2;
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
int GetobjectType(void)
{
	return MaxOjectType;
}

//---------------------------------------------
//X�t�@�C���̓ǂݍ���
//---------------------------------------------
void LoadObject(void)
{
	FILE *pFile = NULL;
	char aEqual[2] = { NULL };					// �u=�v�ǂݎ��p�ϐ�
	bool bComment = false;						// �R�����g�A�E�g���邩
	char aText[TEXT_LENGTH] = { NULL };			// �e�L�X�g�ǂݎ��p�ϐ�
	char aSetObject[DATA_LENGTH] = { NULL };	// �e�L�X�g�ǂݎ��p�ϐ�
	char aSetObjectEND[DATA_LENGTH] = { NULL };	// �e�L�X�g�ǂݎ��p�ϐ�

												// strcmp�ǂݎ��p�|�C���^
	char *pText = &aText[0];
	char *pSetObject = &aSetObject[0];
	char *pSetObjectEND = &aSetObjectEND[0];

	pFile = fopen("data/TEXT/Object.txt", "r");

	aText[0] = { NULL };
	pSetObject[0] = { NULL };
	pSetObjectEND[0] = { NULL };

	while (strcmp("END_SCRIPT", pText) != 0)
	{
		aText[0] = { NULL };

		if (bComment == false)
		{
			// �R�����g�A�E�g���Ă��Ȃ�
			fscanf(pFile, "%s", &aText[0]);

			if (aText[0] == '#')
			{
				// ������̐擪���u#�v�Ȃ�΃R�����g�A�E�g��
				bComment = true;
			}

			else
			{
				if (strcmp("OBJECTSET", aText) == 0)
				{
					pSetObjectEND[0] = { NULL };

					while (strcmp("END_SETOBJECT", pSetObjectEND) != 0)
					{
						fscanf(pFile, "%s", &pSetObjectEND[0]);

						if (strcmp("POSX", pSetObjectEND) == 0)
						{
							// ���f��posX
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%f", &object[g_FailCntDateObject].posX);
						}

						if (strcmp("POSY", pSetObjectEND) == 0)
						{
							// ���f��posY
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%f", &object[g_FailCntDateObject].posY);
						}

						if (strcmp("POSZ", pSetObjectEND) == 0)
						{
							// ���f��posZ
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%f", &object[g_FailCntDateObject].posZ);
						}

						if (strcmp("ROTX", pSetObjectEND) == 0)
						{
							// ���f��posX
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%f", &object[g_FailCntDateObject].rotX);
						}

						if (strcmp("ROTY", pSetObjectEND) == 0)
						{
							// ���f��posY
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%f", &object[g_FailCntDateObject].rotY);
						}

						if (strcmp("ROTZ", pSetObjectEND) == 0)
						{
							// ���f��posZ
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%f", &object[g_FailCntDateObject].rotZ);
						}

						if (strcmp("TYPE", pSetObjectEND) == 0)
						{
							// ���f��TYPE
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &object[g_FailCntDateObject].Type);

							g_FailCntDateObject++;
						}
					}
				}
			}
		}
		else if (bComment == true)
		{
			// �R�����g�A�E�g����
			// ���[�J���ϐ��錾
			char a = NULL;
			char b = NULL;
			fscanf(pFile, "%c", &a);
			while (a != '\n' && b != '\n')
			{
				fscanf(pFile, "%s", &aText[0]);
				fscanf(pFile, "%c", &b);
			}
			bComment = false;
		}
	}
	fclose(pFile);
}