//==============================================================================
//
// 3D�v���C���[�̕`��kplayer.cpp�l
// AUTHOR : TAKAHASHI
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"
#include "object.h"
#include "math.h"
#include "effect.h"
#include "meshfield.h"
#include "gamepad.h"
#include "meshorbit.h"
#include "sound.h"
#include <stdio.h>

//==============================================================================
// �}�N����`
//==============================================================================

#define PLAYER_MOVE		(1.0f)
#define PLAYER_TURN		(0.1f)
#define VTX_MINP		(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))			// �����_�ŏ��l
#define	VTX_MAXP		(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))		// �����_�ő�l
#define PLAYER_X		(50)												// ���S����[�܂ł܂ł̒���(x)
#define PLAYER_Y		(50)
#define MODEL_MOVE		(2.0f + ModelSpeed)
#define SPEEDDOWN		(0.2f)
#define VTX_MINP		(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))			// �����_�ŏ��l
#define	VTX_MAXP		(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))		// �����_�ő�l

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
PLAYER g_player;							// �v���C���[�̍\����
D3DXVECTOR3 g_vtxMinplayer, g_vtxMaxplayer;	// ���f���̊e���W�̍ő�l�E�ŏ��l
float ModelSpeed = 0;

//==============================================================================
// ����������
//==============================================================================
HRESULT InitPlayer(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	g_player.aModel[0].MinModel = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);

	g_player.aModel[0].MaxModel = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

	// X�t�@�C���̓ǂݍ���
	//model�ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[0].pBuffMatModel, NULL, &g_player.aModel[0].nNumMatModel, &g_player.aModel[0].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/����.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[1].pBuffMatModel, NULL, &g_player.aModel[1].nNumMatModel, &g_player.aModel[1].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[2].pBuffMatModel, NULL, &g_player.aModel[2].nNumMatModel, &g_player.aModel[2].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/�E��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[3].pBuffMatModel, NULL, &g_player.aModel[3].nNumMatModel, &g_player.aModel[3].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/�E�r.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[4].pBuffMatModel, NULL, &g_player.aModel[4].nNumMatModel, &g_player.aModel[4].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/�E��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[5].pBuffMatModel, NULL, &g_player.aModel[5].nNumMatModel, &g_player.aModel[5].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/����.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[6].pBuffMatModel, NULL, &g_player.aModel[6].nNumMatModel, &g_player.aModel[6].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/���r.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[7].pBuffMatModel, NULL, &g_player.aModel[7].nNumMatModel, &g_player.aModel[7].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/����.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[8].pBuffMatModel, NULL, &g_player.aModel[8].nNumMatModel, &g_player.aModel[8].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/�E��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[9].pBuffMatModel, NULL, &g_player.aModel[9].nNumMatModel, &g_player.aModel[9].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/�E�Ђ���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[10].pBuffMatModel, NULL, &g_player.aModel[10].nNumMatModel, &g_player.aModel[10].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/�E�C.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[11].pBuffMatModel, NULL, &g_player.aModel[11].nNumMatModel, &g_player.aModel[11].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/����.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[12].pBuffMatModel, NULL, &g_player.aModel[12].nNumMatModel, &g_player.aModel[12].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/���Ђ���.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[13].pBuffMatModel, NULL, &g_player.aModel[13].nNumMatModel, &g_player.aModel[13].MeshModel);
	D3DXLoadMeshFromX("data/MODEL/���C.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[14].pBuffMatModel, NULL, &g_player.aModel[14].nNumMatModel, &g_player.aModel[14].MeshModel);

	//���f����
	g_player.nNumModel = MODEL_PARTS;

	// ���[�J���ϐ��錾
	int nNumVtx;			// ���_��
	DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^

	// ���_�����擾
	nNumVtx = g_player.aModel[0].MeshModel->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
	sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[0].MeshModel->GetFVF());

	//�e�p�[�c�̊K�w�\���ݒ�	��
	g_player.aModel[0].nIdxModelParent = -1;
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 52.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	����
	g_player.aModel[1].nIdxModelParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	��
	g_player.aModel[2].nIdxModelParent = 1;
	g_player.aModel[2].pos = D3DXVECTOR3(0.0f, 27.0f, 0.0f);
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	�E��
	g_player.aModel[3].nIdxModelParent = 1;
	g_player.aModel[3].pos = D3DXVECTOR3(-15.5f, 18.5f, 0.0f);
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	�E�r
	g_player.aModel[4].nIdxModelParent = 3;
	g_player.aModel[4].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	�E��
	g_player.aModel[5].nIdxModelParent = 4;
	g_player.aModel[5].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	����
	g_player.aModel[6].nIdxModelParent = 1;
	g_player.aModel[6].pos = D3DXVECTOR3(15.5f, 18.5f, 0.0f);
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	���r
	g_player.aModel[7].nIdxModelParent = 6;
	g_player.aModel[7].pos = D3DXVECTOR3(12.0f, 0.0f, 0.0f);
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	����
	g_player.aModel[8].nIdxModelParent = 7;
	g_player.aModel[8].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	�E��
	g_player.aModel[9].nIdxModelParent = 0;
	g_player.aModel[9].pos = D3DXVECTOR3(-6.0f, 0.0f, 0.0f);
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	�E�Ђ���
	g_player.aModel[10].nIdxModelParent = 9;
	g_player.aModel[10].pos = D3DXVECTOR3(0.0f, -25.0f, 0.0f);
	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	�E�C
	g_player.aModel[11].nIdxModelParent = 10;
	g_player.aModel[11].pos = D3DXVECTOR3(0.0f, -20.0f, 0.0f);
	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	����
	g_player.aModel[12].nIdxModelParent = 0;
	g_player.aModel[12].pos = D3DXVECTOR3(6.0f, 0.0f, 0.0f);
	g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	���Ђ���
	g_player.aModel[13].nIdxModelParent = 12;
	g_player.aModel[13].pos = D3DXVECTOR3(0.0f, -25.0f, 0.0f);
	g_player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�p�[�c�̊K�w�\���ݒ�	���C
	g_player.aModel[14].nIdxModelParent = 13;
	g_player.aModel[14].pos = D3DXVECTOR3(0.0f, -20.0f, 0.0f);
	g_player.aModel[14].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �ϐ��̏�����
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.motionType = MOTIONTYPE_NEUTRAL;
	g_player.bLoopMotion = false;
	g_player.Jump = false;
	g_player.nNumKey = 0;
	g_player.nKey = 0;
	g_player.nCounterMotion = 0;
	g_vtxMinplayer = VTX_MINP;
	g_vtxMaxplayer = VTX_MAXP;

	// ���_�o�b�t�@�����b�N
	g_player.aModel[0].MeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//���_�����擾
	nNumVtx = g_player.aModel[0].MeshModel->GetNumVertices();

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[0].MeshModel->GetFVF());

		//���_�o�b�t�@�����b�N
		g_player.aModel[0].MeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			// �e���W�̍ő�l�̔�r
			if (g_vtxMaxplayer.x < vtx.x)
			{
				g_vtxMaxplayer.x = vtx.x;
			}
			if (g_vtxMaxplayer.y < vtx.y)
			{
				g_vtxMaxplayer.y = vtx.y;
			}
			if (g_vtxMaxplayer.z < vtx.z)
			{
				g_vtxMaxplayer.z = vtx.z;
			}

			// �e���W�̍ŏ��l�̔�r
			if (g_vtxMinplayer.x > vtx.x)
			{
				g_vtxMinplayer.x = vtx.x;
			}
			if (g_vtxMinplayer.y > vtx.y)
			{
				g_vtxMinplayer.y = vtx.y;
			}
			if (g_vtxMinplayer.z > vtx.z)
			{
				g_vtxMinplayer.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y����i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_player.aModel[0].MeshModel->UnlockVertexBuffer();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		if (g_player.aModel[nCnt].MeshModel != NULL)
		{// ���b�V���̔j��
			g_player.aModel[nCnt].MeshModel->Release();
			g_player.aModel[nCnt].MeshModel = NULL;
		}

		if (g_player.aModel[nCnt].pBuffMatModel != NULL)
		{// �o�b�t�@�̔j��
			g_player.aModel[nCnt].pBuffMatModel->Release();
			g_player.aModel[nCnt].pBuffMatModel = NULL;
		}
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdatePlayer(void)
{
	CAMERA  *pCamera;
	pCamera = GetCamera();

	//�ʒu�����L��
	g_player.posOld = g_player.pos;

	if (GetKeyboardTrigger(DIK_6) == true)
	{
		ModelSpeed += 1.0f;
	}

	if (GetKeyboardTrigger(DIK_7) == true)
	{
		ModelSpeed -= 1.0f;
	}

	// ���[�V�����J�E���^�[�̉��Z
	g_player.nCounterMotion++;

	// ���[�V�����̍X�V
	UpdateMotion(g_player.motionType);

	// �ړ��ʂ̉��Z
	g_player.pos += g_player.move;

	//�n�ʂ̏�ɂ���
	if (g_player.Jump == false)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true || IsButtonPush(A))
		{
			//�T�E���h������
			PlaySound(SOUND_LABEL_SE_JUMP);

			// �W�����v�������̒l
			g_player.move.y += 50.0f;

			//�W�����v���Ă����Ԃł���
			g_player.Jump = true;
		}
	}

	//�I�u�W�F�N�g�̏�ɂ���
	else if (g_player.block == false || IsButtonPush(A))
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			//�T�E���h������
			PlaySound(SOUND_LABEL_SE_JUMP);

			// �W�����v�������̒l
			g_player.move.y += 50.0f;

			//�W�����v���Ă����Ԃł���
			g_player.block = true;
		}
	}

	//�d�͊J�n����
	if (g_player.Jump == true)
	{
		//�d��
		g_player.move.y -= 2.5f;
	}

	//�n�ʂɕt����
	if (g_player.pos.y <= -5.0f)
	{
		//�n�ʂɂ���
		g_player.pos.y = 0.0f;
		g_player.move.y = 0.0f;

		//���n���Ă����Ԃł���
		g_player.Jump = false;
	}

	// ���f���̈ړ�
	if (GetKeyboardPress(DIK_W) == true || IsButtonPush(UP))
	{
		g_player.motionType = MOTIONTYPE_MOVE;

		if (GetKeyboardPress(DIK_A) == true || IsButtonPush(LEFT))
		{// �������
			g_player.move.x -= cosf(pCamera->rot.y + D3DX_PI / 4) * MODEL_MOVE;
			g_player.move.z += sinf(pCamera->rot.y + D3DX_PI / 4) * MODEL_MOVE;
			g_player.rotDest.y = pCamera->rot.y + (D3DX_PI * 3 / 4);
		}
		else if (GetKeyboardPress(DIK_D) == true || IsButtonPush(RIGHT))
		{// �E�����
			g_player.move.x += cosf(pCamera->rot.y - D3DX_PI / 4) * MODEL_MOVE;
			g_player.move.z -= sinf(pCamera->rot.y - D3DX_PI / 4) * MODEL_MOVE;
			g_player.rotDest.y = pCamera->rot.y - (D3DX_PI * 3 / 4);
		}
		else
		{// �����
			g_player.move.x += sinf(pCamera->rot.y) * MODEL_MOVE;
			g_player.move.z += cosf(pCamera->rot.y) * MODEL_MOVE;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI;
		}
	}

	else if (GetKeyboardPress(DIK_S) == true || IsButtonPush(DOWN))
	{
		g_player.motionType = MOTIONTYPE_MOVE;

		if (GetKeyboardPress(DIK_D) == true || IsButtonPush(RIGHT))
		{// �E�����
			g_player.move.x += cosf(pCamera->rot.y + D3DX_PI / 4) * MODEL_MOVE;
			g_player.move.z -= sinf(pCamera->rot.y + D3DX_PI / 4) * MODEL_MOVE;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / -4;
		}
		else if (GetKeyboardPress(DIK_A) == true || IsButtonPush(LEFT))
		{// �������
			g_player.move.x -= cosf(pCamera->rot.y - D3DX_PI / 4) * MODEL_MOVE;
			g_player.move.z += sinf(pCamera->rot.y - D3DX_PI / 4) * MODEL_MOVE;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 4;
		}
		else
		{// ������
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI) * MODEL_MOVE;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * MODEL_MOVE;
			g_player.rotDest.y = pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_A) == true || IsButtonPush(LEFT))
	{
		g_player.motionType = MOTIONTYPE_MOVE;

		// ������
		g_player.move.x -= cosf(pCamera->rot.y) * MODEL_MOVE;
		g_player.move.z += sinf(pCamera->rot.y) * MODEL_MOVE;
		g_player.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);
	}
	else if (GetKeyboardPress(DIK_D) == true || IsButtonPush(RIGHT))
	{
		g_player.motionType = MOTIONTYPE_MOVE;

		// �E����
		g_player.move.x += cosf(pCamera->rot.y) * MODEL_MOVE;
		g_player.move.z -= sinf(pCamera->rot.y) * MODEL_MOVE;
		g_player.rotDest.y = pCamera->rot.y + (D3DX_PI / -2);
	}

	//�j���[�g������Ԃɂ���
	else
	{
		g_player.motionType = MOTIONTYPE_NEUTRAL;
	}

	//�ړ��L�[���������Ƃ�
	if (GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_D) == true || GetKeyboardTrigger(DIK_A) == true || IsButtonDown(UP) || IsButtonDown(DOWN) || IsButtonDown(LEFT) || IsButtonDown(RIGHT))
	{
		g_player.nCounterMotion = 0;
		g_player.aModel[0].pos.y = 55.0f;
		g_player.aModel[0].pos.x = 0.0f;
		g_player.aModel[0].pos.z = 0.0f;
	}
	//�ړ��L�[���͂Ȃ����Ƃ�
	if (GetKeyboardRelease(DIK_W) == true || GetKeyboardRelease(DIK_S) == true || GetKeyboardRelease(DIK_D) == true || GetKeyboardRelease(DIK_A) == true || IsButtonUp(UP) || IsButtonUp(DOWN) || IsButtonUp(LEFT) || IsButtonUp(RIGHT))
	{
		g_player.nCounterMotion = 0;
		g_player.nKey = 0;
		g_player.aModel[0].pos.y = 55.0f;
		g_player.aModel[0].pos.x = 0.0f;
		g_player.aModel[0].pos.z = 0.0f;
		g_player.motionType = MOTIONTYPE_NEUTRAL;
	}

	// �ړI�̉�]�p�̏��
	if (g_player.rotDest.y - g_player.rot.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}

	// �����̍X�V
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	// ���݂̉�]�p�̏��
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	// ������̌�������
	g_player.move.x += (0.0f - g_player.move.x) * SPEEDDOWN;
	g_player.move.y += (0.0f - g_player.move.y) * SPEEDDOWN;
	g_player.move.z += (0.0f - g_player.move.z) * SPEEDDOWN;

	//�ړ�����
	if (g_player.pos.x >= 1500.0f)
	{
		g_player.pos = g_player.posOld;
		g_player.move.x = 0.0f;
	}
	if (g_player.pos.x <= -1500.0f)
	{
		g_player.pos = g_player.posOld;
		g_player.move.x = 0.0f;
	}
	if (g_player.pos.z >= 1500.0f)
	{
		g_player.pos = g_player.posOld;
		g_player.move.z = 0.0f;
	}
	if (g_player.pos.z <= -1500.0f)
	{
		g_player.pos = g_player.posOld;
		g_player.move.z = 0.0f;
	}

	//�I�u�W�F�N�g�̓����蔻��
	CollisionVec(&g_player.pos, &g_player.posOld, &g_player.move, g_vtxMaxplayer.x, g_vtxMinplayer.x, g_vtxMaxplayer.z, g_vtxMinplayer.z, g_vtxMaxplayer.y, g_vtxMinplayer.y);
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawPlayer(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

												// �v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// �v���C���[�̌����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// �v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	// �v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

												// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		// �e�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		// �e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		// �e�p�[�c�̐e�}�g���b�N�X��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld;	// �v���C���[�̃}�g���b�N�X��ݒ�
		}

		// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxParent);

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			g_player.aModel[nCntModel].MeshModel->DrawSubset(nCntMat);
		}
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==============================================================================
// ���f���̎擾
//==============================================================================
PLAYER *GetModel(void)
{
	return &g_player;
}

//==============================================================================
// ���[�V�����̐ݒ�
//==============================================================================
void SetMotion(MOTIONTYPE motionType)
{
	//g_player.motionType = motionType;

	if (motionType == MOTIONTYPE_NEUTRAL)
	{// �ҋ@���[�V����
		g_player.bLoopMotion = true;	// ���[�v����
		g_player.nNumKey = 2;	// �L�[��
		g_player.aMotionInfo[0].aKeySet[0].nFrame = 40;	// �t���[����

		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fRotX = -0.03f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fRotX = -0.09f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fRotX = 0.3f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fRotY = -0.03f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fRotZ = 1.48f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fRotY = -0.13f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fRotZ = 0.06f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fRotY = -0.22f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fRotZ = 0.16f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fRotY = -0.03f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fRotZ = -1.48f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fRotY = 0.13f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fRotZ = -0.12f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fRotY = 0.13f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fRotZ = -0.16f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fRotX = 0.13f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fRotZ = -0.1f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fRotX = -0.13f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fRotY = -0.03f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fRotZ = 0.06f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fRotX = 0.03f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fRotZ = 0.06f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fRotX = 0.13f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fRotZ = 0.13f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fRotX = -0.13f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fRotY = 0.03f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fRotZ = -0.06f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fRotX = 0.03f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fRotY = 0.00f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fRotZ = -0.06f;

		g_player.aMotionInfo[0].aKeySet[1].nFrame = 40;	// �t���[����

		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fRotX = -0.03f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fRotX = 0.03f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fRotX = -0.09f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fRotX = -0.03f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fRotY = 0.19f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fRotZ = 1.55f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fRotX = -0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fRotY = -0.13f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fRotZ = 0.06f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fRotY = -0.22f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fRotZ = -0.03f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fRotY = -0.19f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fRotZ = -1.51f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fRotY = 0.13f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fRotZ = -0.06f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fRotY = 0.13f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fRotZ = 0.03f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fRotX = 0.09f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fRotY = 0.13f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fRotZ = -0.06f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fRotX = -0.06f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fRotY = -0.03f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fRotZ = 0.06f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fRotX = -0.06f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fRotZ = 0.06f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fRotX = 0.06f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fRotZ = 0.1f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fRotX = -0.06f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fRotY = 0.03f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fRotZ = -0.06f;

		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fRotX = -0.06f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fRotZ = -0.06f;
	}
	else if (g_player.motionType == MOTIONTYPE_MOVE)
	{// �ړ����[�V����
		g_player.bLoopMotion = true;					// ���[�v����
		g_player.nNumKey = 4;							// �L�[��
		g_player.aMotionInfo[1].aKeySet[0].nFrame = 4;	// �t���[����

		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fPosY = 3.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fRotX = -0.28f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fRotY = -0.16f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fRotX = -0.28f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fRotY = -0.16f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fRotX = 0.44f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fRotY = 0.22f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fRotX = -0.6f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fRotZ = 1.48f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fRotY = -1.07f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fRotX = 0.69f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fRotY = 0.09f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fRotZ = -1.19f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fRotY = 0.79f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fRotZ = -0.35f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fRotX = -0.25f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fRotX = -0.53f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fRotX = -0.50f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fRotX = 1.29f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fRotX = -0.79f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fRotX = 0.16f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].nFrame = 10;	// �t���[����

		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fPosY = -3.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fRotX = -0.28f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fRotY = -0.16f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fRotX = -0.28f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fRotY = -0.28f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fRotX = 0.51f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fRotY = 0.32f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fRotZ = 1.38f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fRotY = -1.57f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fRotZ = -0.22f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fRotZ = -1.38f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fRotY = 1.51f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fRotX = -0.50f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fRotX = -1.1f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fRotX = 0.5f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fRotX = 0.85f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fRotX = -0.35f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fRotX = -0.44f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fRotZ = 0.0f;


		g_player.aMotionInfo[1].aKeySet[2].nFrame = 8;	// �t���[����

		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fPosY = 1.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fPosZ = -1.6f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fRotX = -0.28f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fRotY = 0.16f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fRotX = -0.28f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fRotY = 0.16f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fRotZ = 0.f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fRotX = 0.41f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fRotY = -0.22f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fRotX = -0.31f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fRotY = 0.19f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fRotZ = 1.29f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fRotY = -1.6f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fRotX = 0.88f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fRotZ = -0.97f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fRotY = 0.75f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fRotZ = -0.5f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fRotX = 1.29f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fRotX = -0.79f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fRotX = 0.16f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fRotX = -0.25f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fRotX = -0.53f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fRotX = -0.5f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].nFrame = 10;	// �t���[����

		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fPosY = -3.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fRotX = -0.28f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fRotY = 0.16f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fRotX = -0.28f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fRotY = 0.28f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fRotX = 0.41f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fRotY = -0.25f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fRotX = -0.57f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fRotY = 0.25f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fRotZ = 0.97f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fRotY = -1.35f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fRotZ = 0.35f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fRotZ = -1.01f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fRotY = 1.13f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fRotX = 0.85f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fRotX = -0.35f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fRotX = -0.44f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fRotX = -0.5f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fRotX = -1.1f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fRotX = -0.5f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fRotZ = 0.0f;

	}

	//else if (g_player.motionType == MOTIONTYPE_JUMP)
	//{// ���[�V����
	//	g_player.bLoopMotion = true;					// ���[�v���Ȃ�
	//	g_player.nNumKey = 3;							// �L�[��
	//	g_player.aMotionInfo[1].aKeySet[0].nFrame = 20;	// �t���[����

	//	g_player.aMotionInfo[2].aKeySet[0].aKey[0].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[0].fPosY = -1.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[0].fPosZ = -5.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[0].fRotX = 0.13f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[0].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[0].fRotZ = 0.0f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[1].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[1].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[1].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[1].fRotX = 0.13f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[1].fRotY = 0.00f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[1].fRotZ = 0.0f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[2].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[2].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[2].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[2].fRotX = 0.34f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[2].fRotY = 0.00f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[2].fRotZ = 0.0f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[3].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[3].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[3].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[3].fRotX = 1.26f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[3].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[3].fRotZ = 1.04f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[4].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[4].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[4].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[4].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[4].fRotY = -0.26f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[4].fRotZ = 0.09f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[5].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[5].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[5].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[5].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[5].fRotY = -0.60f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[5].fRotZ = 0.16f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[6].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[6].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[6].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[6].fRotX = 1.26f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[6].fRotY = 0.09f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[6].fRotZ = -1.04f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[7].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[7].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[7].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[7].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[7].fRotY = 0.26f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[7].fRotZ = -0.09f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[8].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[8].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[8].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[8].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[8].fRotY = 0.6f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[8].fRotZ = -0.16f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[9].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[9].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[9].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[9].fRotX = 0.32f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[9].fRotY = -0.06f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[9].fRotZ = -0.19f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[10].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[10].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[10].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[10].fRotX = -0.51f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[10].fRotY = -0.03f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[10].fRotZ = -0.06f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[11].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[11].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[11].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[11].fRotX = 0.03f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[11].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[11].fRotZ = 0.06f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[12].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[12].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[12].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[12].fRotX = 0.32f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[12].fRotY = 0.06f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[12].fRotZ = 0.19f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[13].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[13].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[13].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[13].fRotX = -0.51f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[13].fRotY = 0.03f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[13].fRotZ = -0.06f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[14].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[14].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[14].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[14].fRotX = 0.03f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[14].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[0].aKey[14].fRotZ = -0.06f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].nFrame = 20;	// �t���[����
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[0].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[0].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[0].fPosZ = -8.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[0].fRotX = -0.53f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[0].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[0].fRotZ = 0.0f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[1].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[1].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[1].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[1].fRotX = -0.63f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[1].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[1].fRotZ = 0.0f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[2].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[2].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[2].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[2].fRotX = 0.44f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[2].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[2].fRotZ = 0.0f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[3].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[3].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[3].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[3].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[3].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[3].fRotZ = 1.38f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[4].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[4].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[4].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[4].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[4].fRotY = -0.26f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[4].fRotZ = -0.09f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[5].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[5].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[5].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[5].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[5].fRotY = -0.6f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[5].fRotZ = 0.16f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[6].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[6].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[6].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[6].fRotX = -2.73f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[6].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[6].fRotZ = -1.04f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[7].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[7].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[7].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[7].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[7].fRotY = 0.26f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[7].fRotZ = -0.09f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[8].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[8].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[8].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[8].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[8].fRotY = 0.6f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[8].fRotZ = -0.16f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[9].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[9].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[9].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[9].fRotX = -0.6f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[9].fRotY = -0.6f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[9].fRotZ = -0.19f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[10].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[10].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[10].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[10].fRotX = -1.67f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[10].fRotY = -0.03f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[10].fRotZ = 0.06f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[11].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[11].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[11].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[11].fRotX = -0.63f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[11].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[11].fRotZ = 0.06f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[12].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[12].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[12].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[12].fRotX = -0.06f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[12].fRotY = 0.06f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[12].fRotZ = 0.19f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[13].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[13].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[13].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[13].fRotX = -1.67f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[13].fRotY = 0.06f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[13].fRotZ = -0.06f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[14].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[14].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[14].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[14].fRotX = -0.63f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[14].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[1].aKey[14].fRotZ = -0.06f;
	//						 
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].nFrame = 40;	// �t���[����
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[0].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[0].fPosY = -1.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[0].fPosZ = -10.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[0].fRotX = -0.34f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[0].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[0].fRotZ = 0.0f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[1].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[1].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[1].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[1].fRotX = 0.25f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[1].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[1].fRotZ = 0.0f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[2].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[2].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[2].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[2].fRotX = 0.03f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[2].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[2].fRotZ = 0.0f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[3].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[3].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[3].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[3].fRotX = 1.1f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[3].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[3].fRotZ = 1.04f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[4].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[4].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[4].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[4].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[4].fRotY = 0.26f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[4].fRotZ = 0.09f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[5].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[5].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[5].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[5].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[5].fRotY = -0.13f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[5].fRotZ = 0.16f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[6].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[6].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[6].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[6].fRotX = 1.108f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[6].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[6].fRotZ = -0.04f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[7].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[7].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[7].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[7].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[7].fRotY = 0.26f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[7].fRotZ = -0.09f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[8].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[8].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[8].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[8].fRotX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[8].fRotY = 0.13f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[8].fRotZ = -0.16f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[9].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[9].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[9].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[9].fRotX = -0.06f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[9].fRotY = -0.06f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[9].fRotZ = -0.19f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[10].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[10].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[10].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[10].fRotX = -0.19f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[10].fRotY = -0.03f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[10].fRotZ = 0.06f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[11].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[11].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[11].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[11].fRotX = -0.32f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[11].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[11].fRotZ = 0.06f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[12].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[12].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[12].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[12].fRotX = -0.06f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[12].fRotY = 0.06f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[12].fRotZ = 0.19f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[13].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[13].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[13].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[13].fRotX = -0.19f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[13].fRotY = 0.03f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[13].fRotZ = 0.19f;
	//						 
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[14].fPosX = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[14].fPosY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[14].fPosZ = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[14].fRotX = -0.32f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[14].fRotY = 0.0f;
	//	g_player.aMotionInfo[2].aKeySet[2].aKey[14].fRotZ = -0.06f;
	//}
}

//==============================================================================
// ���[�V�����̍X�V
//==============================================================================
void UpdateMotion(MOTIONTYPE motionType)
{
	SetMotion(motionType);

	for (int nCnt = 0; nCnt < MODEL_PARTS; nCnt++)
	{
		if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == true)
		{
			g_player.aModel[nCnt].pos.x += (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosX) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].pos.y += (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosY) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].pos.z += (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosZ) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].rot.x = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.y = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.z = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			//g_player.aModel[nCnt].rot.x = pKey->fPosX + (pKeyTop->fPosX - pKey->fPosX) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel
			//g_player.aModel[nCnt].rot.x = rot[g_player.nKey][nCnt].x + (rot[0][nCnt].x - rot[g_player.nKey][nCnt].x) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.y = rot[g_player.nKey][nCnt].y + (rot[0][nCnt].y - rot[g_player.nKey][nCnt].y) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.z = rot[g_player.nKey][nCnt].z + (rot[0][nCnt].z - rot[g_player.nKey][nCnt].z) * (fCntMotion / fFrame[g_player.nKey]);
		}
		else
		{
			g_player.aModel[nCnt].pos.x += (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fPosX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosX) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].pos.y += (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fPosY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosY) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].pos.z += (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fPosZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosZ) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].rot.x = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fRotX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.y = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fRotY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.z = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fRotZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			//g_player.aModel[nCnt].rot.x = rot[g_player.nKey][nCnt].x + (rot[g_player.nKey + 1][nCnt].x - rot[g_player.nKey][nCnt].x) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.y = rot[g_player.nKey][nCnt].y + (rot[g_player.nKey + 1][nCnt].y - rot[g_player.nKey][nCnt].y) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.z = rot[g_player.nKey][nCnt].z + (rot[g_player.nKey + 1][nCnt].z - rot[g_player.nKey][nCnt].z) * (fCntMotion / fFrame[g_player.nKey]);


			if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == false)
			{
				break;
			}
		}

		if (g_player.nCounterMotion == g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame)
		{
			g_player.nCounterMotion = 0;

			if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == true)
			{
				g_player.nKey = 0;
			}
			else
			{
				g_player.nKey++;
			}
		}
	}
}