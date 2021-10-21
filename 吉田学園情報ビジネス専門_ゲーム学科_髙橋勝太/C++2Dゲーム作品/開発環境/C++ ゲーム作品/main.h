//=============================================================================
//
// ���C������ [main.h]
// Author : takahashi shota
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"						//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"						//���͏����ɕK�v
#include "xaudio2.h"					//�T�E���h�Đ��ɕK�v
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define CLASS_NAME "WindowClass"			//�E�B���h�E�̃N���X�̖��O
//#define WINDOW_NAME "WARNING"				//�E�B���h�E�̖��O
#define ID_BUTTON000	(101)				//�{�^����ID
#define ID_EDIT000		(111)				//�G�f�B�b�g��ID
#define WINDOW_POS_X	(40)				//
#define WINDOW_POS_Y	(40)				//
#define ID_TIMER		(121)				//
#define TIMER_INTERVAL	(1000/60)			//
#define LOOP_PLAYER		(3)					//
#define SCREEN_WIDTH	(1920)				//��ʂ̕�
#define SCREEN_HEIGHT	(1080)				//��ʂ̍���
#define MAX_POLYGON		(300)				//�`��ł��鐔
#define MAX_LIFE		(5)					//�v���C���[�̃��C�t��

//*****************************************************************************
// �֐���`
//*****************************************************************************
int GetFPS(void);

//�O���錾
class CRenderer;
class CManager;

//�v���g�^�C�v�錾
//CRenderer *GetRenderer(void);
CManager *GetManager(void);

#endif