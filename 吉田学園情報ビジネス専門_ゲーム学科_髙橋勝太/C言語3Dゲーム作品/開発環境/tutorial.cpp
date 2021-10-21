//-----------------------------------------------------------------
//
// �w�i (bg.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "tutorial.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTextureTutorial[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;//���_���
int g_nTutorial;
bool g_EndTutorial;

//====================
//�|���S���̏���������
//====================
HRESULT InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_nTutorial = 0;
	g_EndTutorial = false;

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/tutorial01.jpg", &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/tutorial02.jpg", &g_pTextureTutorial[1]);
	
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);//2D��0.0�Œ�
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTutorial->Unlock();

	return S_OK;
}
//==================
//�|���S���̏I������
//==================
void UninitTutorial(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < 2; nCntTexture++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureTutorial[nCntTexture] != NULL)
		{
			g_pTextureTutorial[nCntTexture]->Release();
			g_pTextureTutorial[nCntTexture] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

}
//==================
//�|���S���̍X�V����
//==================
void UpdateTutorial(void)
{
	//��ʂ�i�߂�
	if (IsButtonDown(A) || GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_nTutorial++;
	}

	if (g_nTutorial == 1)
	{
		if (g_EndTutorial == false)
		{
			VERTEX_2D *pVtx;

			//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
			g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

			//���_���W�̐ݒ�
			pVtx[4].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);//2D��0.0�Œ�
			pVtx[5].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			//rhw�̐ݒ�
			pVtx[4].rhw = 1.0f;
			pVtx[5].rhw = 1.0f;
			pVtx[6].rhw = 1.0f;
			pVtx[7].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//���_���̐ݒ�
			pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffTutorial->Unlock();

			//��񂾂��ǂݍ���
			g_EndTutorial = true;
		}
	}

	if (g_nTutorial == 2)
	{
		SetFade(FADE_OUT, MODE_GAME);
	}
}

//==================
//�|���S���̕`�揈��
//==================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntTexture = 0; nCntTexture < 2; nCntTexture++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorial[nCntTexture]);

		//�|���S���̕`��
		//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 4);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}

