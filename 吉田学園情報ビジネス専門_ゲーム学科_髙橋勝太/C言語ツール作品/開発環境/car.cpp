//-----------------------------------------------------------------
//
// �v���C���[�̏��� (model.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "car.h"
#include"camera.h"
#include "shadow.h"
#include "input.h"
#include "bullet.h"
#include "effect.h"
#include "object.h"
#include "meshfield.h"
#include "gamepad.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MAX_CAR			(1)
#define CAR_X			(50)									// ���S����[�܂ł܂ł̒���(x)
#define CAR_Y			(50)									// ���S����[�܂ł܂ł̒���(y)
#define CAR_MOVE		(5.0f)									//�ړ����x

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPD3DXMESH g_pMeshCar[MAX_CAR] = {};	//���_���
LPD3DXBUFFER g_pBuffMetCar[MAX_CAR] = {};
LPDIRECT3DTEXTURE9 g_pTextureCar[5] = {};			//�e�N�X�`��
DWORD  g_nNumMatCar = 0;							//�}�e���A���̐�
CAR g_Car[MAX_CAR];
D3DXMATRIX g_mtxWorldCar;							//���[���h�}�g���b�N�X
float g_carrot;
float g_SpeedCar = 0;
int g_CarnType = 0;

//-----------------------------------------------------------------------------
// �|���S���̏���������
//-----------------------------------------------------------------------------
HRESULT InitCar(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_CAR; nCnt++)
	{
		//�ő�ŏ��̒l������
		g_Car[nCnt].MinCar = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_Car[nCnt].MaxCar = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

		//model�ǂݍ���
		D3DXLoadMeshFromX("data/model/point.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetCar[0], NULL, &g_nNumMatCar, &g_pMeshCar[0]);
		//D3DXLoadMeshFromX("data/model/car004.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetCar[1], NULL, &g_nNumMatCar, &g_pMeshCar[1]);


		int nNumVtx;			//���_��
		DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^ 

		D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

		//���_�����擾
		nNumVtx = g_pMeshCar[nCnt]->GetNumVertices();
		g_Car[nCnt].nNumVtx = nNumVtx;

		//�}�e���A���f�[�^�ւ̃|�C���^�擾
		pMat = (D3DXMATERIAL*)g_pBuffMetCar[nCnt]->GetBufferPointer();

		//x�t�@�C���Ƀe�N�X�`��������ꍇ
		for (int nCntMat = 0; nCntMat < (int)g_nNumMatCar; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���ǂݍ���
				//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/50.png", &g_pTextureCar[0]);
			}
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshCar[nCnt]->GetFVF());

		//���_�o�b�t�@�����b�N
		g_pMeshCar[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//x�t�@�C���̍ő�ŏ��̒l������
			if (g_Car[nCnt].MinCar.x > vtx.x)
			{
				g_Car[nCnt].MinCar.x = vtx.x;
			}
			if (g_Car[nCnt].MaxCar.x < vtx.x)
			{
				g_Car[nCnt].MaxCar.x = vtx.x;
			}
			if (g_Car[nCnt].MinCar.y > vtx.y)
			{
				g_Car[nCnt].MinCar.y = vtx.y;
			}
			if (g_Car[nCnt].MaxCar.y < vtx.y)
			{
				g_Car[nCnt].MaxCar.y = vtx.y;
			}
			if (g_Car[nCnt].MinCar.z > vtx.z)
			{
				g_Car[nCnt].MinCar.z = vtx.z;
			}
			if (g_Car[nCnt].MaxCar.z < vtx.z)
			{
				g_Car[nCnt].MaxCar.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y����i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_pMeshCar[nCnt]->UnlockVertexBuffer();

		//�ʒu
		g_Car[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�ʒu
		//g_Car[1].pos = D3DXVECTOR3(0.0f, 0.0f, -400.0f);

		//����
		g_Car[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	return S_OK;
}

//-----------------------------------------------------------------------------
// �|���S���̏I������
//-----------------------------------------------------------------------------
void UninitCar(void)
{
	for (int nCnt = 0; nCnt < g_Car[nCnt].nNumVtx; nCnt++)
	{
		//���b�V���̊J��
		if (g_pMeshCar != NULL)
		{
			g_pMeshCar[nCnt]->Release();
			g_pMeshCar[nCnt] = NULL;
		}

		//�}�e���A���̊J��
		if (g_pBuffMetCar != NULL)
		{
			g_pBuffMetCar[nCnt]->Release();
			g_pBuffMetCar[nCnt] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �|���S���̍X�V����
//-----------------------------------------------------------------------------
void UpdateCar(void)
{
	CAMERA  *pCamera;
	pCamera = GetCamera();

	EFFECT *pEffect;
	pEffect = GetEffect();

	CAR  *pCar;
	pCar = GetCar();

	for (int nCnt = 0; nCnt < MAX_CAR; nCnt++)
	{
		//�ʏ�ړ�
		// ���f���̈ړ�
		if (GetKeyboardPress(DIK_W) == true)
		{
			if (GetKeyboardPress(DIK_A) == true)
			{// �������
				g_Car[nCnt].move.x -= cosf(pCamera->rot.y + D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].move.z += sinf(pCamera->rot.y + D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y + (D3DX_PI * 3 / 4);
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{// �E�����
				g_Car[nCnt].move.x += cosf(pCamera->rot.y - D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].move.z -= sinf(pCamera->rot.y - D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y - (D3DX_PI * 3 / 4);
			}
			else
			{// �����
				g_Car[nCnt].move.x += sinf(pCamera->rot.y) * CAR_MOVE;
				g_Car[nCnt].move.z += cosf(pCamera->rot.y) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			if (GetKeyboardPress(DIK_D) == true)
			{// �E�����
				g_Car[nCnt].move.x += cosf(pCamera->rot.y + D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].move.z -= sinf(pCamera->rot.y + D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI / -4;
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{// �������
				g_Car[nCnt].move.x -= cosf(pCamera->rot.y - D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].move.z += sinf(pCamera->rot.y - D3DX_PI / 4) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI / 4;
			}
			else
			{// ������
				g_Car[nCnt].move.x += sinf(pCamera->rot.y - D3DX_PI) * CAR_MOVE;
				g_Car[nCnt].move.z += cosf(pCamera->rot.y - D3DX_PI) * CAR_MOVE;
				g_Car[nCnt].rotDest.y = pCamera->rot.y;
			}
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{// ������.
			g_Car[nCnt].move.x -= cosf(pCamera->rot.y) * CAR_MOVE;
			g_Car[nCnt].move.z += sinf(pCamera->rot.y) * CAR_MOVE;
			g_Car[nCnt].rotDest.y = pCamera->rot.y + (D3DX_PI / 2);
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// �E����
			g_Car[nCnt].move.x += cosf(pCamera->rot.y) * CAR_MOVE;
			g_Car[nCnt].move.z -= sinf(pCamera->rot.y) * CAR_MOVE;
			g_Car[nCnt].rotDest.y = pCamera->rot.y + (D3DX_PI / -2);
		}

		if (GetKeyboardPress(DIK_6) == true)
		{// �����
			g_Car[nCnt].move.y += 10.0;
		}

		if (GetKeyboardPress(DIK_7) == true)
		{// ������
			g_Car[nCnt].move.y -= 10.0;
		}

		//�ʒu���Z�b�g
		if (GetKeyboardPress(DIK_0) == true)
		{
			g_Car[nCnt].pos.y = 0.0;
		}

		if (g_Car[nCnt].pos.y <= 0.0f)
		{// ������
			g_Car[nCnt].pos.y = 0.0f;
		}

		//�ړ��ʂ̌���
		g_Car[nCnt].move.x -= (0 + g_Car[nCnt].move.x) * 0.5f;
		g_Car[nCnt].move.y -= (0 + g_Car[nCnt].move.y) * 0.5f;
		g_Car[nCnt].move.z -= (0 + g_Car[nCnt].move.z) * 0.5f;

		//�ʒu�X�V
		g_Car[nCnt].pos.x += g_Car[nCnt].move.x;
		g_Car[nCnt].pos.y += g_Car[nCnt].move.y;
		g_Car[nCnt].pos.z += g_Car[nCnt].move.z;

		// �ړI�̉�]�p�̏��
		if (g_Car[nCnt].rotDest.y - g_Car[nCnt].rot.y < -D3DX_PI)
		{
			g_Car[nCnt].rotDest.y += D3DX_PI * 2.0f;
		}
		else if (g_Car[nCnt].rotDest.y - g_Car[nCnt].rot.y > D3DX_PI)
		{
			g_Car[nCnt].rotDest.y -= D3DX_PI * 2.0f;
		}

		// �����̍X�V
		g_Car[nCnt].rot.y += (g_Car[nCnt].rotDest.y - g_Car[nCnt].rot.y) * 0.1f;

		// ���݂̉�]�p�̏��
		if (g_Car[nCnt].rot.y < -D3DX_PI)
		{
			g_Car[nCnt].rot.y += D3DX_PI * 2.0f;
		}
		else if (g_Car[nCnt].rot.y > D3DX_PI)
		{
			g_Car[nCnt].rot.y -= D3DX_PI * 2.0f;
		}

		//�e�̈ʒu�X�V
		SetPositionShadow(0, D3DXVECTOR3(g_Car[nCnt].pos.x, 0.0f, g_Car[nCnt].pos.z));
	}
}

//-----------------------------------------------------------------------------
// �|���S���̕`�揈��
//-----------------------------------------------------------------------------
void DrawCar(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ�
	D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_CAR; nCnt++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldCar);

		//�����̔��]
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Car[nCnt].rot.y, g_Car[nCnt].rot.x, g_Car[nCnt].rot.z);
		D3DXMatrixMultiply(&g_mtxWorldCar, &g_mtxWorldCar, &mtxRot);

		//�ʒu�̔��]
		D3DXMatrixTranslation(&mtxTrans, g_Car[nCnt].pos.x, g_Car[nCnt].pos.y, g_Car[nCnt].pos.z);
		D3DXMatrixMultiply(&g_mtxWorldCar, &g_mtxWorldCar, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldCar);

		//���݂̃}�e���A���̎擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^�擾
		pMat = (D3DXMATERIAL*)g_pBuffMetCar[nCnt]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatCar; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			//pDevice->SetTexture(0, g_pTextureCar[nCntMat]);

			//���f���p�[�c�̕`��
			g_pMeshCar[nCnt]->DrawSubset(nCntMat);
		}
	}

	//�ۑ������}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
CAR *GetCar(void)
{
	return &g_Car[0];
}
