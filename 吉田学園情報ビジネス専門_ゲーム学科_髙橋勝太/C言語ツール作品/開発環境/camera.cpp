//==============================================================================
//
// �J�����̐ݒ�kcamera.cpp�l
// AUTHOR : shota takahashi
//
//==============================================================================
#include "camera.h"
#include "model.h"
#include "car.h"
#include "input.h"
#include "game.h"
#include "gamepad.h"
#include "car.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define CAMERA_MOVE				(2.0f)							// �J�����̈ړ���
#define CAMERA_TURN				(D3DX_PI / 100.0f)				// �J�����̐��񑬓x
#define CAMERA_RANGE_CAR		(500.0f)						// ���_�E�����_�Ԃ̋���
#define CAMERA_RANGE_MODEL		(250.0f)						// ���_�E�����_�Ԃ̋���
#define CAMERA_HEIGHT			(500.0f)						// �J����(���_)�̍���
#define CAMERA_SPDOWN			(0.5f)							// �����W�� 

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
CAMERA g_camera[2];
float nHeight = 2500;
float nHeight2 = 500;

//==============================================================================
// ����������
//==============================================================================
void InitCamera(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�֐��Ăяo��
		CameraInfo(nCnt);
	}
}			

//==============================================================================
// �I������
//==============================================================================
void UninitCamera(void)
{

}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateCamera(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// ���[�J���ϐ��錾
		PLAYER *player;
		player = GetModel();

		//�A�h���X��n��
		CAR  *pCar;
		pCar = GetCar();
		CAMERA  *pCamera;
		pCamera = GetCamera();

		//�ЂƂO�̈ʒu�����L��
		pCar->posOld = pCar->pos;

		//�v���C�����_
		// �ړI�̒����_
		g_camera[1].posRDest.x = player->pos.x - g_camera[1].fFront * sinf(player->rotDest.y);
		g_camera[1].posRDest.z = player->pos.z - g_camera[1].fFront * cosf(player->rotDest.y);
		g_camera[1].posRDest.y = player->pos.y + g_camera[1].fHeightR;

		// �ړI�̎��_
		g_camera[1].posVDest.x = player->pos.x - sinf(g_camera[1].rot.y) * g_camera[1].fLength;
		g_camera[1].posVDest.z = player->pos.z - cosf(g_camera[1].rot.y) * g_camera[1].fLength;
		g_camera[1].posVDest.y = player->pos.y + cosf(g_camera[1].rot.x) * g_camera[1].fLength + g_camera[1].fHeightV;

		//���f����ʂ̎�
		if (GetGame() == 1)
		{
			//�L�[�{�[�h�������Ƃ�
			//C��������
			if (GetKeyboardPress(DIK_C) == true)
			{
				g_camera[1].rot.y += CAMERA_TURN;

				if (g_camera[1].rot.y > D3DX_PI)
				{
					g_camera[1].rot.y -= D3DX_PI * 2.1f;
				}

				g_camera[1].posV.x = g_camera[1].posR.x - sinf(g_camera[1].rot.y) * g_camera[1].fLength;
				g_camera[1].posV.z = g_camera[1].posR.z - cosf(g_camera[1].rot.y) * g_camera[1].fLength;
			}
			//Z��������
			if (GetKeyboardPress(DIK_Z) == true)
			{
				g_camera[1].rot.y -= CAMERA_TURN;

				if (g_camera[1].rot.y < -D3DX_PI)
				{
					g_camera[1].rot.y += D3DX_PI * 2.0f;
				}

				g_camera[1].posV.x = g_camera[1].posR.x - sinf(g_camera[1].rot.y) * g_camera[1].fLength;
				g_camera[1].posV.z = g_camera[1].posR.z - cosf(g_camera[1].rot.y) * g_camera[1].fLength;
			}

			//��������
			if (GetKeyboardPress(DIK_8) == true)
			{
				nHeight2 += 10.0f;
			}
			if (GetKeyboardPress(DIK_9) == true)
			{
				nHeight2 -= 10.0f;
			}

			//�J�������Z�b�g
			if (GetKeyboardTrigger(DIK_0) == true)
			{
				g_camera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �J�����̊p�x
				nHeight2 = 0.0f;
			}
		}

		//�c�[����ʂ̎�
		if (GetGame() == 0)
		{
			// �ړI�̒����_
			g_camera[0].posRDest.x = pCar->pos.x - g_camera[0].fFront * sinf(pCar->rotDest.y);
			g_camera[0].posRDest.z = pCar->pos.z - g_camera[0].fFront * cosf(pCar->rotDest.y);
			g_camera[0].posRDest.y = pCar->pos.y + g_camera[0].fHeightR;

			// �ړI�̎��_
			g_camera[0].posVDest.x = pCar->pos.x - sinf(g_camera[0].rot.y) * g_camera[0].fLength;
			g_camera[0].posVDest.z = pCar->pos.z - cosf(g_camera[0].rot.y) * g_camera[0].fLength;
			g_camera[0].posVDest.y = pCar->pos.y + cosf(g_camera[0].rot.x) * g_camera[0].fLength + g_camera[0].fHeightV;

			//�L�[�{�[�h�������Ƃ�
			//C��������
			if (GetKeyboardPress(DIK_C) == true)
			{
				g_camera[0].rot.y += CAMERA_TURN;

				if (g_camera[0].rot.y > D3DX_PI)
				{
					g_camera[0].rot.y -= D3DX_PI * 2.0f;
				}

				g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fLength;
				g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fLength;
			}

			//Z��������
			if (GetKeyboardPress(DIK_Z) == true)
			{
				g_camera[0].rot.y -= CAMERA_TURN;

				if (g_camera[0].rot.y < -D3DX_PI)
				{
					g_camera[0].rot.y += D3DX_PI * 2.0f;
				}

				g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fLength;
				g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fLength;
			}

			//��������
			if (GetKeyboardPress(DIK_8) == true)
			{
				nHeight += 10.0f;
			}

			if (GetKeyboardPress(DIK_9) == true)
			{
				nHeight -= 10.0f;
			}

			//�J�������Z�b�g
			if (GetKeyboardTrigger(DIK_0) == true)
			{
				g_camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �J�����̊p�x
				nHeight = 0.0f;
			}
		}

		//�X�V
		g_camera[0].fHeightV = nHeight;							//���_�̍����̍X�V
		g_camera[0].fLength = CAMERA_RANGE_MODEL;				//���_�̋����̍X�V

		//�X�V
		g_camera[1].fHeightV = nHeight2;						//���_�̍����̍X�V
		g_camera[1].fLength = CAMERA_RANGE_MODEL;				//���_�̋����̍X�V

		// �����_�̈ʒu�X�V
		g_camera[nCnt].posR.x += (g_camera[nCnt].posRDest.x - g_camera[nCnt].posR.x) * CAMERA_SPDOWN;
		g_camera[nCnt].posR.z += (g_camera[nCnt].posRDest.z - g_camera[nCnt].posR.z) * CAMERA_SPDOWN;
		g_camera[nCnt].posR.y += (g_camera[nCnt].posRDest.y - g_camera[nCnt].posR.y) * CAMERA_SPDOWN;

		// ���_�̈ʒu�X�V
		g_camera[nCnt].posV.x += (g_camera[nCnt].posVDest.x - g_camera[nCnt].posV.x) * CAMERA_SPDOWN;
		g_camera[nCnt].posV.z += (g_camera[nCnt].posVDest.z - g_camera[nCnt].posV.z) * CAMERA_SPDOWN;
		g_camera[nCnt].posV.y += (g_camera[nCnt].posVDest.y - g_camera[nCnt].posV.y) * CAMERA_SPDOWN;
	}
}

//==============================================================================
// �J�����̐ݒ菈��
//==============================================================================
void SetCamera(int nIdx)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//�r���[�|�[�g���擾
	pDevice->SetViewport(&g_camera[nIdx].viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nIdx].mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(
		&g_camera[nIdx].mtxProjection,
		D3DXToRadian(45.0f),									// ��p�̐ݒ�
		(float)SCREEN_WIDTH / 2 / SCREEN_HEIGHT,				// �䗦
		10.0f,													// ��O���E�̕`�拗��
		4000.0f);												// �����E�̕`�拗��

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nIdx].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nIdx].mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&g_camera[nIdx].mtxView,
		&g_camera[nIdx].posV,
		&g_camera[nIdx].posR,
		&g_camera[nIdx].vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nIdx].mtxView);
}

//==============================================================================
// �J�����̏��
//==============================================================================
void CameraInfo(int nIdx)
{
	// ���[�J���ϐ��錾
	PLAYER *player;
	player = GetModel();

	player += nIdx;

	switch (nIdx)
	{
	case 1:
		// �\���̂̏�����
		g_camera[nIdx].posV = D3DXVECTOR3(
			player->pos.x,
			player->pos.y + 100.0f,
			player->pos.z - 200.0f);							// �J�������_�̈ʒu
		g_camera[nIdx].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����_�ʒu
		g_camera[nIdx].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ������x�N�g��
		g_camera[nIdx].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
		g_camera[nIdx].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �J�����̊p�x
		g_camera[nIdx].fLength = 500;							// ���_�E�����_�Ԃ̋���
		g_camera[nIdx].fHeightV = -60.0f;						// ���_�̍���
		g_camera[nIdx].fHeightR = 100.0f;		// �����_�̍���
		g_camera[nIdx].fFront = 15.0f;							// ���f���̑O���̋���
		g_camera[nIdx].bAutoTurn = false;						// �J�����̉�荞��ON�EOFF

		g_camera[nIdx].viewport.X = (DWORD)0.0f;				// �`�悷���ʍ���̂w���W
		g_camera[nIdx].viewport.Y = (DWORD)0.0f;				// �`�悷���ʍ���̂x���W
		g_camera[nIdx].viewport.Width = (DWORD)960.0f;			// �`�悷���ʂ̕�
		g_camera[nIdx].viewport.Height = (DWORD)1080.0f;		// �`�悷���ʂ̍���
		g_camera[nIdx].viewport.MinZ = 0.0f;
		g_camera[nIdx].viewport.MaxZ = 1.0f;
		break;

	case 0:
		// �\���̂̏�����
		g_camera[nIdx].posV = D3DXVECTOR3(player->pos.x,
			player->pos.y + 100.0f,
			player->pos.z - 200.0f);							// �J�������_�̈ʒu
		g_camera[nIdx].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����_�ʒu
		g_camera[nIdx].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ������x�N�g��
		g_camera[nIdx].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
		g_camera[nIdx].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �J�����̊p�x
		g_camera[nIdx].fLength = 200;							// ���_�E�����_�Ԃ̋���
		g_camera[nIdx].fHeightV = -60.0f;						// ���_�̍���
		g_camera[nIdx].fHeightR = player->pos.y + 100.0f;		// �����_�̍���
		g_camera[nIdx].fFront = 15.0f;							// ���f���̑O���̋���
		g_camera[nIdx].bAutoTurn = false;						// �J�����̉�荞��ON�EOFF
		g_camera[nIdx].viewport.X = (DWORD)960.0f;				// �`�悷���ʍ���̂w���W
		g_camera[nIdx].viewport.Y = (DWORD)0.0f;				// �`�悷���ʍ���̂x���W 
		g_camera[nIdx].viewport.Width = (DWORD)970.0f;			// �`�悷���ʂ̕�
		g_camera[nIdx].viewport.Height = (DWORD)1080.0f;		// �`�悷���ʂ̍���
		g_camera[nIdx].viewport.MinZ = 0.0f;
		g_camera[nIdx].viewport.MaxZ = 1.0f;

		break;
	default:
		break;
	}
}

//==============================================================================
// �J�����̎擾
//==============================================================================
CAMERA *GetCamera(void)
{
	return &g_camera[0];
}

//==============================================================================
// �J�����̎擾
//==============================================================================
CAMERA *GetCamera2(void)
{
	return &g_camera[1];
}