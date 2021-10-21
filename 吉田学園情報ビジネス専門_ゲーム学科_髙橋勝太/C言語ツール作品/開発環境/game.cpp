#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------
//
// game (game.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include<stdio.h>
#include "main.h"
#include "camera.h"
#include "light.h"
#include"model.h"
#include "xinput.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "stdio.h"
#include "object.h"
#include "billboard.h"
#include "effect.h"
#include "ui.h"
#include "meshfield.h"
#include "bullet.h"
#include "pause.h"
#include "bg.h"
#include "car.h"
#include "score.h"
#include "gamepad.h"
#include "timer.h"
#include "fade.h"
#include "meshorbit.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define TEXT_LENGTH			(128)		// �e�L�X�g�ǂݍ��݂̍ő吔
#define DATA_LENGTH			(64)		// �f�[�^�ǂݍ��݂̍ő吔

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
bool g_bPause;						//�|�[�Y��Ԕ���
int g_PlayerChange = 0;				//�������Ă���v���C���[
int g_nDataTime = 0;				//�������
float g_nDataTime2 = 0;				//�������
int g_nDataItem = 0;				//�������
int g_nDataItem2 = 0;				//�������
FAILDATE FailDate[MAX_OBJECT];
int g_nObjectDate = 0;
int g_nItemDate = 0;
int g_FPSCnt = 0;
char g_GameStage;

//--------------
//����������
//--------------
HRESULT InitGame()
{
	g_bPause = false;

	//LoadGame();

	InitPause();

	InitBG();

	InitScore();

	InitMeshfield();

	InitMeshOrbit();

	InitWall();

	InitBillboard();

	InitBullet();

	InitShadow();

	InitPlayer();

	InitCar();

	InitObject();

	InitCamera();

	Initlight();

	InitEffect();

	InitUi();

	InitTimer();

	//�X�R�A�̕\��
	for (int nCount = 0; nCount < 8; nCount++)
	{
		SetScore(D3DXVECTOR3(1600 + 70.0f * (nCount + 1), 50.0f, 0.0f), 0);
	}

	//�^�C���̕\��
	//��
	for (int nCount = 0; nCount < 2; nCount++)
	{
		SetTimer(D3DXVECTOR3(800 + 50.0f * (nCount + 1), 50.0f, 0.0f), 0);
	}
	//�b
	for (int nCount = 0; nCount < 2; nCount++)
	{
		SetTimer(D3DXVECTOR3(950 + 50.0f * (nCount + 1), 50.0f, 0.0f), 0);
	}

	//�t�B�[���h�̐ݒ�
	SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);	//����

	return E_NOTIMPL;
}

//----------------
//�I������
//----------------
void UninitGame(void)
{
	UninitBG();

	UninitScore();

	UninitMeshfield();

	UninitMeshOrbit();

	UninitWall();

	UninitBillboard();

	UninitBullet();

	UninitShadow();

	UninitPlayer();

	UninitCar();

	UninitObject();

	UninitCamera();

	Uninitlight();

	UninitEffect();

	UninitUi();

	UninitTimer();

	// �|�[�Y���j���[�̏I������
	UninitPause();
}

//--------------------
//�X�V����
//--------------------
void UpdatetGame(void)
{
	//�|�[�Y�{�^�����������Ƃ�
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;

	}

	if (g_bPause == true)
	{
		UpdatePause();
	}

	else
	{
		UpdateMeshfield();

		UpdateMeshOrbit();

		UpdateScore();

		UpdateBullet();

		UpdateWall();

		UpdateBillboard();

		UpdateShadow();


		//�v���C���[�̐؂�ւ�
		if (g_PlayerChange == 1)
		{
			UpdatePlayer();
		}

		//�v���C���[�̐؂�ւ�
		if (g_PlayerChange == 0)
		{
			UpdateCar();
		}

		UpdateObject();

		UpdateCamera();

		Updatelight();

		UpdateEffect();

		UpdateUi();

		UpdateBG();

		UpdateTimer();

		AddTimer(1);

		if (GetKeyboardTrigger(DIK_1) == true)
		{
			//�Ԃ��𓮂���
			if (g_PlayerChange == 1)
			{
				g_PlayerChange = 0;
			}

			//�v���C���[�𓮂���
			else if (g_PlayerChange == 0)
			{
				g_PlayerChange = 1;
			}
		}

		PLAYER *player;
		player = GetModel();

		//�I�u�W�F�N�g�̌�����ς���
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{
			g_nDataTime2 += D3DX_PI / 2;
		}

		if (GetKeyboardTrigger(DIK_LEFT) == true)
		{
			g_nDataTime2 += -D3DX_PI / 2;
		}

		CAR  *pCar;
		pCar = GetCar();

		//�v���C���[�̈ʒu�ɃI�u�W�F�N�g�𐶐�
		if (GetKeyboardTrigger(DIK_G) == true)
		{
			//�c�[���̈ʒu��
			SetObject(D3DXVECTOR3(pCar->pos.x, pCar->pos.y, pCar->pos.z), D3DXVECTOR3(0.0f, g_nDataTime2, 0.0f), g_nDataTime);

			//txt�t�@�C���ɏ�������
			FailObject();

			//G�{�^���������񐔂��J�E���g
			g_nObjectDate += 1;
		}

		//�ŐV�̃I�u�W�F�N�g������
		if (g_nObjectDate >= 1)
		{
			if (GetKeyboardTrigger(DIK_H) == true)
			{
				//H�{�^���������񐔂��J�E���g
				//�����󂯓n��
				g_nObjectDate -= 1;

				//txt�t�@�C���ɏ�������
				FailObject();
			}
		}

		//�I�u�W�F�N�g�̃^�C�v��ς���
		if (GetKeyboardTrigger(DIK_UP) == true)
		{
			g_nDataTime += 1;
		}

		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{
			g_nDataTime -= 1;
		}

		//�I�u�W�F�N�g�^�C�v�̏�����̏ꍇ0�ɖ߂�
		if (g_nDataTime > GetobjectType() - 1.0f)
		{
			g_nDataTime = 0.0f;
		}

		//�I�u�W�F�N�g�^�C�v�̏�����̏ꍇMAX�ɖ߂�
		if (g_nDataTime == -1.0f)
		{
			g_nDataTime = GetobjectType() - 1.0f;
		}

		//�A�C�e���̃^�C�v��ς���
		if (GetKeyboardTrigger(DIK_UP) == true)
		{
			g_nDataItem += 1;
		}

		if (GetKeyboardTrigger(DIK_DOWN) == true)
		{
			g_nDataItem -= 1;
		}
	}
}

//--------------------
//�`�揈��
//--------------------
void DrawGame(void)
{
	DrawMeshfield();

	DrawMeshOrbit();

	DrawObject();

	DrawWall();

	DrawBillboard();

	DrawShadow();

	DrawBullet();

	DrawPlayer();

	DrawCar();

	DrawEffect();

	DrawTimer();

	DrawUi();

	// �|�[�Y�̕`�揈��
	if (g_bPause == true)
	{
		DrawPause();
	}
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
int GetGame(void)
{
	return g_PlayerChange;
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
int GetItem(void)
{
	return g_nDataTime;
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
char GetGameTXT(void)
{
	return g_GameStage;
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
bool PauseGame(void)
{
	return g_bPause;
}

//---------------------------------------------
//�����o��
//---------------------------------------------
int FailObject()
{
	PLAYER *player;
	player = GetModel();

	CAR  *pCar;
	pCar = GetCar();

	FILE *fp;

	fp = fopen("data/TEXT/ObjectSet.txt", "w");

	//�I�u�W�F�N�g�̈ʒu���L��(CAR)
	FailDate[g_nObjectDate].X = pCar->pos.x;
	FailDate[g_nObjectDate].Y = pCar->pos.y;
	FailDate[g_nObjectDate].Z = pCar->pos.z;
	FailDate[g_nObjectDate].Rot = g_nDataTime2;
	FailDate[g_nObjectDate].Type = g_nDataTime;

	for (int nCnt = 0; nCnt < g_nObjectDate + 1; nCnt++)
	{
		//�������ޓ��e
		fprintf(fp, "OBJECTSET\n");
		fprintf(fp, "	POSX = %.1f\n", FailDate[nCnt].X);
		fprintf(fp, "	POSY = %.1f\n", FailDate[nCnt].Y);
		fprintf(fp, "	POSZ = %.1f\n", FailDate[nCnt].Z);
		fprintf(fp, "	ROTX = 0");
		fprintf(fp, "	ROTY = %.1f\n", FailDate[nCnt].Rot);
		fprintf(fp, "	ROTZ = 0");
		fprintf(fp, "	TYPE = %d\n", FailDate[nCnt].Type);
		fprintf(fp, "END_SETOBJECT\n\n");
	}

	//�utxt�v�̃t�@�C�������
	fclose(fp);

	return 0;
}