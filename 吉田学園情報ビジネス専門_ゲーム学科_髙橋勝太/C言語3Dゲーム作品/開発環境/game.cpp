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

	InitPlayer();

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

	UninitPlayer();

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
	if (GetKeyboardTrigger(DIK_P) == true || IsButtonDown(P))
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

		UpdatePlayer();

		UpdateObject();

		UpdateCamera();

		Updatelight();

		UpdateEffect();

		UpdateUi();

		UpdateBG();

		UpdateTimer();

		AddTimer(1);
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

	DrawBullet();
	
	DrawUi();

	DrawScore();

	DrawPlayer();

	DrawEffect();

	DrawTimer();

	

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