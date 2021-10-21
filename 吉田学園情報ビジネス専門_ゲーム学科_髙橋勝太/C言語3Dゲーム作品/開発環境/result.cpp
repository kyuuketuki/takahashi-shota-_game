//-----------------------------------------------------------------
//
// ���U���g��� (result.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "result.h"
#include "input.h"
#include "fade.h"
#include "gamepad.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_PATTERN     (3)										// �A�j���[�V�����p�^�[��No.�̍ő吔
#define TITLELOGO_X		(1000.0f)								// �^�C�g�����S��
#define TITLELOGO_Y		(200.0f)								// �^�C�g�����S�̍���
#define HEIGHT_Y		(500.0f * -1.0f)						// �^�C�g�����S�̏������SY���W
#define PRESSENTER_X	(800.0f)								// �v���X�G���^�[�̕�
#define PRESSENTER_Y	(300.0f)								// �v���X�G���^�[�̍���

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
LPDIRECT3DTEXTURE9 g_pTextureResult[3] = {};
D3DXVECTOR3 g_posResultLogo;						// �^�C�g�����S�̒��S���W
D3DXVECTOR3 g_posPressEnterResult;					// �v���X�G���^�[�̒��S���W
D3DXCOLOR g_Resultcolor;
RESULT  g_aResult[256];
float g_nCntResult;
int g_nCntResult2;
int g_resultclear;

//-----------------------------------------------------------------
// �^�C�g���̏���������
//-----------------------------------------------------------------
HRESULT InitResult(void)
{
	g_resultclear = 0;

	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �ϐ��̏�����
	g_posResultLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, HEIGHT_Y, 0.0f);
	g_posPressEnterResult = D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 4), 0.0f);
	g_Resultcolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_nCntResult = 0;

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/space_1.png", &g_pTextureResult[0]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameclear.png", &g_pTextureResult[1]);

	for (int nCntResult = 0; nCntResult < 256; nCntResult++)
	{
		g_aResult[nCntResult].nType = 0;
		g_aResult[nCntResult].nData = 0;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_PATTERN, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_PATTERN; nCntTitle++)
	{
		// ���_���W�̐ݒ�
		SetVertexTextureResult(nCntTitle);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_Resultcolor;
		pVtx[1].col = g_Resultcolor;
		pVtx[2].col = g_Resultcolor;
		pVtx[3].col = g_Resultcolor;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���̍X�V
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �^�C�g���̏I������
//-----------------------------------------------------------------
void UninitResult(void)
{
	g_resultclear += 1;

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < 2; nCntTexture++)
	{
		if (g_pTextureResult[nCntTexture] != NULL)
		{
			g_pTextureResult[nCntTexture]->Release();
			g_pTextureResult[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �^�C�g���̍X�V����
//-----------------------------------------------------------------
void UpdateResult(void)
{
	if (IsButtonDown(B) || GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//��ʐ؂�ւ�
		SetMode(MODE_RANKING);
	}
}

//-----------------------------------------------------------------
// �^�C�g���̕`�揈��
//-----------------------------------------------------------------
void DrawResult(void)
{
	RESULT *pResult;

	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	pResult = &g_aResult[0];

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntTexture = 0; nCntTexture < 3; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureResult[nCntTexture]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}

}

//-----------------------------------------------------------------
// �^�C�g����ʂɓ\��e�N�X�`���̎w��
//-----------------------------------------------------------------
void SetVertexTextureResult(int nCntResult)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	g_nCntResult2 = nCntResult;

	if (g_nCntResult2 == 0)
	{
		pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	}

	else if (g_nCntResult2 == 1)
	{
		pVtx[4].pos = D3DXVECTOR3(g_posPressEnterResult.x - (PRESSENTER_X / 2), g_posPressEnterResult.y + (PRESSENTER_Y / 2), 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_posPressEnterResult.x - (PRESSENTER_X / 2), g_posPressEnterResult.y - (PRESSENTER_Y / 2), 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_posPressEnterResult.x + (PRESSENTER_X / 2), g_posPressEnterResult.y + (PRESSENTER_Y / 2), 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_posPressEnterResult.x + (PRESSENTER_X / 2), g_posPressEnterResult.y - (PRESSENTER_Y / 2), 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();
}

int GetResultclear(void)
{
	return g_resultclear;
}