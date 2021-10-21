#define _CRT_SECURE_NO_WARNINGS
//======================
//
//Windows�̏���[main.cpp]
//Author: shota
//======================

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
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
#include "meshfield.h"
#include "bullet.h"
#include "game.h"
#include "title.h"
#include"fade.h"
#include "result.h"
#include"gamepad.h"
#include "ranking.h"
#include "tutorial.h"
#include "sound.h"
#include "pause.h"
#include <stdio.h>
#include <string.h>

//================
//�v���g�^�C�v�錾
//================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

//===============
//�O���[�o���ϐ�
//===============
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
LPD3DXFONT g_pFont = NULL;//�t�H���g�̃|�C���^
int g_nCountFPS;//FPS�J�E���^�[
int g_camera;
int g_Itemdate;
int g_EndGameDate;
MODE g_mode = MODE_TITLE; //���[�h�̎��
//MODE g_mode = MODE_GAME; //���[�h�̎��
bool bPauseMain;

//==========
//���C���֐�
//==========
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_EXCLAMATION),
		LoadCursor(NULL,IDC_HAND),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_EXCLAMATION),
	};
	HWND hWnd;
	MSG msg;

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�̍쐬
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);
	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	//�E�C���h�E
	if (FAILED(Init(hInstance, hWnd, false)))
	{
		return -1;
	}

	////�t���X�N���[��
	//if (FAILED(Init(hInstance, hWnd, FALSE)))
	//{
	//	return -1;
	//}

	//�E�B���h�E�̕\��
	UpdateWindow(hWnd);

	ShowWindow(hWnd, nCmdShow);
	DWORD dwExcelastTime;//�������s�ŏI����
	DWORD dwFPSLastTime;//FPS�v�����s�ŏI����
	DWORD dwCurrentTime;//���ݎ���
	DWORD dwFrameCount;//�t���[���J�E���g

	dwExcelastTime = dwFPSLastTime = dwCurrentTime = timeGetTime();
	dwFrameCount = 0;//���ݎ�����ݒ�

					 //���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExcelastTime) >= 1000)//0.5�b�o��
			{
				//g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;//�ۑ�
				dwFrameCount = 0;//���Z�b�g
			}

			if ((dwCurrentTime - dwExcelastTime) > (1000 / 60))
			{
				dwFPSLastTime = dwCurrentTime;//�ۑ�

				g_EndGameDate = EndGame();

				//�|�[�Y��ʂ���E�B���h�E�����
				if (g_EndGameDate == 1)
				{
					DestroyWindow(hWnd);
				}

				//�X�V����
				Update();

				//�`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}
	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass(CLASS_NAME,//�E�B���h�E�N���X�̖��O
		wcex.hInstance);
	return (int)msg.wParam;
}

//------------------------------------
//�E�B���h�E�v���V�[�W��
//------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	switch (uMsg)
	{

	case WM_DESTROY://�E�B���h�E��j������

		PostQuitMessage(0);//WM_QUIT���b�Z�[�W��Ԃ�

		break;

	case WM_COMMAND:

		if (LOWORD(wParam) == ID_BUTTON000)
		{
			nID = MessageBox(hWnd, "�I�����܂����H", "�{���ɁH", MB_YESNOCANCEL | MB_ICONASTERISK);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}

			else
			{
				return 0;
			}
		}

		break;

	default:

		break;

	case WM_CLOSE://�~�{�^���Ŋm�F�\��
		nID = MessageBox(NULL, "�I�����܂����H", "�{���ɁH", MB_YESNOCANCEL | MB_ICONASTERISK);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);//YES�����������
		}

		else
		{
			return 0;//����ȊO�̓E�B���h�E�͕��Ȃ�
		}

		break;
	}

	switch (wParam)
	{

	case WM_KEYDOWN://�L�[�������Ƃ��̃��b�Z�[�W

	case VK_UP:
		//�����̈�������I�ɔ���������
		InvalidateRect(hWnd, &rect, FALSE);
		break;

	case VK_RIGHT:
		//nPosy++;
		//�����̈�������I�ɔ���������
		InvalidateRect(hWnd, &rect, FALSE);
		break;

	case VK_ESCAPE://�G�X�P�[�v�L�[�ŕ\��
		DestroyWindow(hWnd);
		break;

		//case VK_SPACE://�X�y�[�X�L�[�ŕ\��
		//DestroyWindow(hWnd);
		//break;

	default:

		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//==========
//����������
//==========
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//�f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�[�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3D�f���@�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice
	)))
	{

		if (FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice
		)))
		{

			if (FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice
			)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//����
	//g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �k�����ɕ��
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �g�厞�ɕ��
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// U�l�̌J��Ԃ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// V�l�̌J��Ԃ�

																			//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // ���l�̍���
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//FPS�����̑傫��(18)
	D3DXCreateFont(g_pD3DDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//�L�[�{�[�h����������
	InitKeyboard(hInstance, hWnd);

	// �p�b�h���͂̏���������
	InitGamepad(hInstance, hWnd);

	//�t�F�C�h����
	InitFade(g_mode);

	InitSound(hWnd);

	//���[�h�̐ݒ�
	SetMode(g_mode);

	return S_OK;
}

//-------------------
//���[�h�̐ݒ�
//-------------------
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:

		//�^�C�g����ʂ̏I������
		UninitTitle();
		break;

	case MODE_GAME:

		//�Q�[����ʂ̏I������
		UninitGame();
		break;

	case MODE_RESULT:

		//�Q�[����ʂ̏I������
		UninitResult();
		break;

	case MODE_RANKING:
		// �����L���O��ʂ̏I������
		UninitRanking();
		break;

	case MODE_TUTORIAL:
		// �����L���O��ʂ̏I������
		UninitTutorial();
		break;

	default:
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:

		//�^�C�g����ʂ̏���������
		InitTitle();

		//���y������
		StopSound(SOUND_LABEL_BGM004);
		PlaySound(SOUND_LABEL_BGM003);
		break;

	case MODE_GAME:

		//�Q�[����ʂ̏���������
		InitGame();

		//���y������
		StopSound(SOUND_LABEL_BGM003);
		PlaySound(SOUND_LABEL_BGM004);
		break;

	case MODE_RESULT:

		//�Q�[����ʂ̏���������
		InitResult();
		break;

	case MODE_RANKING:
		// �����L���O��ʂ̏���������
		InitRanking();
		break;

	case MODE_TUTORIAL:
		// �����L���O��ʂ̏���������
		InitTutorial();
		break;

	default:
		break;
	}
	g_mode = mode;
}

//========
//�I������
//========
void Uninit(void)
{
	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	UninitGamepad();

	//UninitPlayer();

	UninitMeshfield();

	UninitWall();

	UninitBillboard();

	UninitBullet();

	UninitPlayer();

	UninitObject();

	UninitCamera();

	Uninitlight();

	UninitEffect();

	UninitSound();

	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//=========
//�X�V����
//=========
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	UpdateGamepad();

	switch (g_mode)
	{
	case MODE_TITLE:

		//�^�C�g����ʂ̍X�V����
		UpdateTitle();
		break;

	case MODE_GAME:

		//�Q�[����ʂ̍X�V����
		UpdatetGame();
		break;

	case MODE_RESULT:

		//�Q�[����ʂ̍X�V����
		UpdateResult();
		break;

	case MODE_RANKING:
		// �����L���O��ʂ̍X�V����
		UpdateRanking();
		break;

	case MODE_TUTORIAL:
		// �����L���O��ʂ̍X�V����
		UpdateTutorial();
		break;

	default:
		break;
	}

	//�t�F�C�h����
	UpdateFade();

	CAMERA  *pCamera;
	pCamera = GetCamera();

	////�R���g���[���[�̐ݒ�
	//XINPUT_STATE state;
	//ZeroMemory(&state, sizeof(XINPUT_STATE));

	//// Simply get the state of the controller from XInput.
	//DWORD dwResult = XInputGetState(0, &state);

	//if (dwResult == ERROR_SUCCESS)
	//{
	//	// Controller is connected
	//}
	//else
	//{
	//	// Controller is not connected
	//}

	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	//{
	//	// A �{�^���������ꂽ
	//	//�ړ�
	//	//pCar->move.x += sinf(pCamera->rot.y) * 0.2;
	//	//pCar->move.x += sinf(pCamera->rot.y) * 0.2;
	//}

	//if (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	//{
	//	// �X�e�B�b�N�̍��������ꂽ

	//
	//}
}

//=========
//�`�揈��
//=========
void Draw(void)
{
	//���[�J��
	//LPDIRECT3DDEVICE9 pDevice;

	//�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A�i��ʂ̃N���A�j
	//�w�i�̐F
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(137, 189, 222, 0),
		1.0f,
		0);

	//�`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		D3DVIEWPORT9 viewportDef;

		//�J����
		g_pD3DDevice->GetViewport(&viewportDef);

		switch (g_mode)
		{
		case MODE_TITLE:

			//�^�C�g����ʂ̕`�揈��
			DrawTitle();
			break;

			//case MODE_GAME:

			//	//�Q�[����ʂ̕`�揈��
			//	DrawGame();
			//	break;

		case MODE_GAME:

			// ���[�J���ϐ��錾
			D3DVIEWPORT9 viewportDef;

			// ���݂̃r���[�|�[�g���擾
			g_pD3DDevice->GetViewport(&viewportDef);

			// �J�����̐ݒ�
			for (int nCntCamera = 0; nCntCamera < 1; nCntCamera++)
			{
				SetCamera(nCntCamera);

				// �Q�[����ʂ̕`�揈��
				DrawGame();
			}

			// �r���[�|�[�g��߂�
			g_pD3DDevice->SetViewport(&viewportDef);

			break;

		case MODE_RESULT:

			//�Q�[����ʂ̕`�揈��
			DrawResult();
			break;

		case MODE_RANKING:
			// �����L���O��ʂ̕`�揈��
			DrawRanking();
			break;

		case MODE_TUTORIAL:
			// �����L���O��ʂ̕`�揈��
			DrawTutorial();
			break;
		}

		//�t�F�C�h����
		DrawFade();

		//#ifdef _DEBUG
		//DrawFPS();
		//#endif // DEBUG

		//�J����
		g_pD3DDevice->SetViewport(&viewportDef);

		//�`��̏I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//-------------------------
//FPS�\���ɕK�v
//-------------------------
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	CAMERA  *pCamera;
	pCamera = GetCamera();

	bPauseMain = PauseGame();

	MeshField *pMeshfild;
	pMeshfild = GetMesh();

	PLAYER *pModel;
	pModel = GetModel();

	char aStr[512];

	g_Itemdate = GetItem();

	int nNum = wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	nNum += sprintf(&aStr[nNum], "MODEL  pos:  X%.2f Y%.2f  Z%.2f\n\n\n", pModel->pos.x, pModel->pos.y, pModel->pos.z);

	nNum += sprintf(&aStr[nNum], "0     :  �J�����̊p�x���Z�b�g\n\n");

	nNum += sprintf(&aStr[nNum], "-----�L�����N�^�[�̐؂�ւ�-----\n");
	nNum += sprintf(&aStr[nNum], "1     :  �c�[�����\n");
	nNum += sprintf(&aStr[nNum], "1     :  ���f�����\n\n");

	nNum += sprintf(&aStr[nNum], "-----TOOL-----\n");
	nNum += sprintf(&aStr[nNum], "8     :  ���_�̍���UP\n");
	nNum += sprintf(&aStr[nNum], "9     :  ���_�̍���DOWN\n");
	nNum += sprintf(&aStr[nNum], "G     :  �I�u�W�F�N�g���� & data/ TEXT/Object.txt�ɕۑ�\n");
	nNum += sprintf(&aStr[nNum], "H     :  �I�u�W�F�N�g���� & data/ TEXT/Object.txt���C��\n");
	nNum += sprintf(&aStr[nNum], "T     :  �I�u�W�F�N�g���� & data/ TEXT/Item.txt�ɕۑ�\n");
	nNum += sprintf(&aStr[nNum], "Y     :  �I�u�W�F�N�g���� & data/ TEXT/Item.txt���C��\n");
	nNum += sprintf(&aStr[nNum], "����  :  �I�u�W�F�N�g�^�C�v�ύX\n");

	if (bPauseMain == true)
	{

	}

	//�e�L�X�g
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}


