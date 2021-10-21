//-----------------------------------------------------------------
//
// �|�[�Y��ʂ̏��� (pause.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "pause.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "game.h"
#include "gamepad.h"

//=================================================================================================================
//	�}�N����`
//=================================================================================================================
#define MAX_PAUSE (5)	//�|�[�Y�̎��

//=================================================================================================================
//	�O���[�o���ϐ�
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexPause[MAX_PAUSE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;
int g_nPointNow;
int g_nPoint;
int g_gamedata;
int g_gamedata2;
int g_gamedata3;
int g_EndGame;

//-------------------------------------------
//	�|�[�Y�̏���������
//-------------------------------------------
HRESULT InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//������
	g_nPoint = 0;
	g_nPointNow = 1;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL)))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\�|�[�Y���2.png", &g_apTexPause[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TUTORIAL.png", &g_apTexPause[PAUSE_MENE_TUTORIAL]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\RETRY.png", &g_apTexPause[PAUSE_MENE_RETRY]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\QUIT.png", &g_apTexPause[PAUSE_MENE_QUIT]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pointer.png", &g_apTexPause[PAUSE_MENE_POINT]);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++, pVtx += 4)
	{
		if (nCntPause == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 100);
			pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 100);
			pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 100);
			pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 100);
		}

		if (nCntPause == PAUSE_MENE_TUTORIAL)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(900, 350, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(900, 300, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1200, 350, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1200, 300, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (nCntPause == PAUSE_MENE_RETRY)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(900, 450, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(900, 400, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1200, 450, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1200, 400, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (nCntPause == PAUSE_MENE_QUIT)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(900, 550, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(900, 500, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1200, 550, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1200, 500, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (nCntPause == PAUSE_MENE_POINT)
		{
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(850.0f, 350.0f + g_nPoint, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(850.0f, 300.0f + g_nPoint, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(800.0f, 350.0f + g_nPoint, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800.0f, 300.0f + g_nPoint, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	return S_OK;
}

//-------------------------------------
//	�|�[�Y�̏I������
//-------------------------------------
void UninitPause(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	for (int nCntPause = 0; nCntPause <MAX_PAUSE; nCntPause++)
	{
		//�e�N�X�`���̊J��
		if (g_apTexPause[nCntPause] != NULL)
		{
			g_apTexPause[nCntPause]->Release();
			g_apTexPause[nCntPause] = NULL;
		}
	}
}

//-------------------------------------
//	�|�[�Y�̍X�V����
//-------------------------------------
void UpdatePause(void)
{
	VERTEX_2D *pVtx;

	//S�L�[����������(���Ɉړ�)
	if (GetKeyboardTrigger(DIK_S) == true || IsButtonDown(DOWN))
	{
		g_nPoint += 100;
		g_nPointNow++;

		if (g_nPointNow > PAUSE_MENE_QUIT)	//QUIT��艺�̎�
		{
			g_nPointNow = PAUSE_MENE_TUTORIAL;
		}

		if (g_nPoint >= 300)
		{
			g_nPoint -= 300;
		}
	}

	//W�L�[����������
	if (GetKeyboardTrigger(DIK_W) == true || IsButtonDown(UP))
	{
		g_nPoint -= 100;
		g_nPointNow--;

		if (g_nPointNow < PAUSE_MENE_TUTORIAL)	//�`���[�g���A������̎�
		{
			g_nPointNow = PAUSE_MENE_QUIT;
		}

		if (g_nPoint < 0)
		{
			g_nPoint += 300;
		}
	}

	if (GetKeyboardPress(DIK_RETURN) == true || IsButtonDown(A))
	{
		if (g_nPointNow == PAUSE_MENE_TUTORIAL)
		{
			SetFade(FADE_OUT, MODE_TUTORIAL);	//�t�F�[�h�A�E�g�����ă`���[�g���A����ʂɔ�t��
		}

		if (g_nPointNow == PAUSE_MENE_RETRY)
		{
			SetFade(FADE_OUT, MODE_TITLE);	//�t�F�[�h�A�E�g�����ăQ�[����ʂɔ��
		}

		if (g_nPointNow == PAUSE_MENE_QUIT)
		{
			//�E�B���h�E�����
			g_EndGame = 1;
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ� (XYZ)
	pVtx[16].pos = D3DXVECTOR3(750.0f, 350.0f + g_nPoint, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(750.0f, 300.0f + g_nPoint, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(800.0f, 350.0f + g_nPoint, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(800.0f, 300.0f + g_nPoint, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

}

//----------------------------------------
//	�|�[�Y�̕`�揈��
//----------------------------------------
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexPause[nCntPause]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
int EndGame(void)
{
	return g_EndGame;
}
