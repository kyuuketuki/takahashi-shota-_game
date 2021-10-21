//-----------------------------------------------------------------
//
// �^�C�g���̏��� (titile.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "gamepad.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_PATTERN     (3)										// �A�j���[�V�����p�^�[��No.�̍ő吔
#define TITLELOGO_X		(1000.0f)								// �^�C�g�����S��
#define TITLELOGO_Y		(500.0f)								// �^�C�g�����S�̍���
#define HEIGHT_Y		(500.0f * -1.0f)						// �^�C�g�����S�̏������SY���W
#define MOVE_TITLELOGO	(5.0f)									// �^�C�g�����S�̈ړ���
#define PRESSENTER_X	(300.0f)								// �v���X�G���^�[�̕�
#define PRESSENTER_Y	(100.0f)								// �v���X�G���^�[�̍���

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTitle[3] = {};
D3DXVECTOR3 g_posTitleLogo;						// �^�C�g�����S�̒��S���W
D3DXVECTOR3 g_posPressEnter;					// �v���X�G���^�[�̒��S���W
D3DXCOLOR g_color;								// �F
float g_nCnt;									// �J�E���g

//-----------------------------------------------------------------
// �^�C�g���̏���������
//-----------------------------------------------------------------
HRESULT InitTitle(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �ϐ��̏�����
	g_posTitleLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, HEIGHT_Y, 0.0f);
	g_posPressEnter = D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 4) * 3, 0.0f);
	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_nCnt = 0;

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &g_pTextureTitle[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/topgear.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/town.jpg", &g_pTextureTitle[0]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_PATTERN, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_PATTERN; nCntTitle++)
	{
		// ���_���W�̐ݒ�
		SetVertexTexture(nCntTitle);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_color;
		pVtx[1].col = g_color;
		pVtx[2].col = g_color;
		pVtx[3].col = g_color;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���̍X�V
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �^�C�g���̏I������
//-----------------------------------------------------------------
void UninitTitle(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < MAX_PATTERN; nCntTexture++)
	{
		if (g_pTextureTitle[nCntTexture] != NULL)
		{
			g_pTextureTitle[nCntTexture]->Release();
			g_pTextureTitle[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �^�C�g���̍X�V����
//-----------------------------------------------------------------
void UpdateTitle(void)
{
	// �t�F�[�h���̎擾
	int nFade = GetFade();

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �^�C�g�����S�̈ʒu�X�V
	pVtx[4].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLELOGO_X / 2), g_posTitleLogo.y + (TITLELOGO_Y / 2), 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLELOGO_X / 2), g_posTitleLogo.y - (TITLELOGO_Y / 2), 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLELOGO_X / 2), g_posTitleLogo.y + (TITLELOGO_Y / 2), 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLELOGO_X / 2), g_posTitleLogo.y - (TITLELOGO_Y / 2), 0.0f);

	// �v���X�G���^�[�̐F�X�V
	pVtx[8].col = g_color;
	pVtx[9].col = g_color;
	pVtx[10].col = g_color;
	pVtx[11].col = g_color;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	if (IsButtonDown(A) || GetKeyboardTrigger(DIK_RETURN) == true)
	{// �G���^�[�L�[���������Ƃ�
		if (nFade == FADE_IN)
		{// �t�F�[�h�C���̎�
			SetFade(FADE_NONE, MODE_GAME);
			g_posTitleLogo.y = SCREEN_HEIGHT / 4;
		}
		else if (g_posTitleLogo.y <= (SCREEN_HEIGHT / 4))
		{
			g_posTitleLogo.y = SCREEN_HEIGHT / 4;
		}
		else if (nFade == FADE_NONE && (g_posTitleLogo.y >= (SCREEN_HEIGHT / 4)))
		{// �������Ă��Ȃ��Ƃ�
			// SetFade(FADE_OUT, MODE_GAME);
			SetFade(FADE_OUT, MODE_TUTORIAL);
			g_nCnt = 0;
		}
	}
	// �X�V����
	if (nFade == FADE_NONE && g_posTitleLogo.y <= (SCREEN_HEIGHT / 4))
	{// �^�C�g�����S�̈ړ��ʂ̍X�V
		g_posTitleLogo.y += MOVE_TITLELOGO;
	}
	else if (nFade == FADE_NONE)
	{// �v���X�G���^�[�̐F�X�V
	 // �J�E���g����
		g_nCnt++;
		if (g_nCnt == 10)
		{// 10�̂Ƃ��s������
		 //g_color.a = 1.0f;
		}
		else if (g_nCnt == 70)
		{// 70�̂Ƃ�������
		 //g_color.a = 0.0f;
			g_nCnt = 0;			// �J�E���g��������
		}
	}
	else if (nFade == FADE_OUT)
	{ // �J�E���g����
		g_nCnt++;
		if (g_nCnt == 10)
		{// 10�̂Ƃ��s������
		 //g_color.a = 1.0f;
		}
		else if (g_nCnt == 20)
		{// 20�Ƃ�������
		 //g_color.a = 0.0f;
			g_nCnt = 0;			// �J�E���g��������
		}
	}
	else
	{// �v���X�G���^�[�̓�����
	 //g_color.a = 0.0f;
	}
}

//-----------------------------------------------------------------
// �^�C�g���̕`�揈��
//-----------------------------------------------------------------
void DrawTitle(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntTexture = 0; nCntTexture < MAX_PATTERN; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureTitle[nCntTexture]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}

//-----------------------------------------------------------------
// �^�C�g����ʂɓ\��e�N�X�`���̎w��
//-----------------------------------------------------------------
void SetVertexTexture(int nCntTitle)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if (nCntTitle == 0)
	{
		pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
		g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	else if (nCntTitle == 1)
	{
		pVtx[4].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLELOGO_X / 2), g_posTitleLogo.y + (TITLELOGO_Y / 2), 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLELOGO_X / 2), g_posTitleLogo.y - (TITLELOGO_Y / 2), 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLELOGO_X / 2), g_posTitleLogo.y + (TITLELOGO_Y / 2), 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLELOGO_X / 2), g_posTitleLogo.y - (TITLELOGO_Y / 2), 0.0f);
	}

	else if (nCntTitle == 2)
	{
		pVtx[8].pos = D3DXVECTOR3(g_posPressEnter.x - (PRESSENTER_X / 2), g_posPressEnter.y + (PRESSENTER_Y / 2), 0.0f);
		pVtx[9].pos = D3DXVECTOR3(g_posPressEnter.x - (PRESSENTER_X / 2), g_posPressEnter.y - (PRESSENTER_Y / 2), 0.0f);
		pVtx[10].pos = D3DXVECTOR3(g_posPressEnter.x + (PRESSENTER_X / 2), g_posPressEnter.y + (PRESSENTER_Y / 2), 0.0f);
		pVtx[11].pos = D3DXVECTOR3(g_posPressEnter.x + (PRESSENTER_X / 2), g_posPressEnter.y - (PRESSENTER_Y / 2), 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}