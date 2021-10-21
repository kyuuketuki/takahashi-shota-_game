//-----------------------------------------------------------------
//
// �X�R�A�̏��� (score.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "timer.h"

#define  MAX_TIMER (4)

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTextureTimer = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;//���_���
D3DXVECTOR3 g_PosTimer;
TIMER g_aTimer[MAX_TIMER];
int g_nTimer;//�X�R�A
int g_nTimerCnt;//�X�R�A

//====================
//�|���S���̏���������
//====================
HRESULT InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_pTextureTimer);

	//�X�R�A���Z�b�g
	g_nTimer = 0;
	g_nTimerCnt = 0;

	for (int nCntEnemy = 0; nCntEnemy < MAX_TIMER; nCntEnemy++)
	{
		g_aTimer[nCntEnemy].nType = 0;
		g_aTimer[nCntEnemy].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTimer, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_TIMER; nCntBullet++, pVtx += 4)
	{
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
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTimer->Unlock();

	return S_OK;
}

//==================
//�|���S���̏I������
//==================
void UninitTimer(void)
{
	//�e�N�X�`���̊J��
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_TIMER; nCntEnemyType++)
	{
		if (g_pTextureTimer != NULL)
		{
			g_pTextureTimer->Release();
			g_pTextureTimer = NULL;
		}
	}
	//�o�b�t�@�̊J��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}

}


//==================
//�|���S���̍X�V����
//==================
void UpdateTimer(void)
{
	VERTEX_2D *pVtx;
	int nNumber2[MAX_TIMER];

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	nNumber2[0] = g_nTimer % 6000 / 1000;
	nNumber2[1] = g_nTimer % 1000 / 60;
	nNumber2[2] = g_nTimer % 60 / 10;
	nNumber2[3] = g_nTimer % 10 / 1;

	for (int nCutEnemy = 0; nCutEnemy < MAX_TIMER; nCutEnemy++)
	{
		pVtx[0].pos = D3DXVECTOR3((g_aTimer[nCutEnemy].pos.x - TIMER_SIZE) + nCutEnemy * 10, g_aTimer[nCutEnemy].pos.y + TIMER_SIZE, 0);
		pVtx[1].pos = D3DXVECTOR3((g_aTimer[nCutEnemy].pos.x - TIMER_SIZE) + nCutEnemy * 10, g_aTimer[nCutEnemy].pos.y - TIMER_SIZE, 0);
		pVtx[2].pos = D3DXVECTOR3((g_aTimer[nCutEnemy].pos.x + TIMER_SIZE) + nCutEnemy * 10, g_aTimer[nCutEnemy].pos.y + TIMER_SIZE, 0);
		pVtx[3].pos = D3DXVECTOR3((g_aTimer[nCutEnemy].pos.x + TIMER_SIZE) + nCutEnemy * 10, g_aTimer[nCutEnemy].pos.y - TIMER_SIZE, 0);

		//���_���̐ݒ�(�����j���O�}��)
		pVtx[0].tex = D3DXVECTOR2(0.1f*nNumber2[nCutEnemy], 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f*nNumber2[nCutEnemy], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*(nNumber2[nCutEnemy] + 1), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*(nNumber2[nCutEnemy] + 1), 0.0f);

		pVtx += 4;
	}
}

//==================
//�|���S���̕`�揈��
//==================
void DrawTimer(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	int nCntVertex = 0;

	TIMER *pTimer;
	pTimer = &g_aTimer[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	//�|���S���̕`��
	for (int nCntBullet = 0; nCntBullet < MAX_TIMER; nCntBullet++, pTimer++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTimer);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntVertex, 2);
		if (g_aTimer[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntVertex, 2);
		}

		nCntVertex += 4;
	}
}

///=================
//���Z����
//==================
void AddTimer(int nValue)
{
	g_nTimerCnt += nValue;
	if ((g_nTimerCnt % 60) == 0)
	{
		g_nTimer += 1;
	}

}

//-----------------------------------------------------------------------------
// ���Ԃ̐ݒ�
//-----------------------------------------------------------------------------
void SetTimer(D3DXVECTOR3 pos, int nType)
{
	TIMER *pTimer;
	pTimer = &g_aTimer[0];

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_TIMER; nCntEnemy++, pTimer++)
	{
		if (pTimer->bUse == false)
		{

			pTimer->pos = pos;

			//���_���W
			SetVertexTimer(nCntEnemy);

			pTimer->nType = nType;

			pTimer->bUse = true;
			break;
		}
		g_pVtxBuffTimer->Unlock(); //�A�����b�N
	}
}

//-----------------------------------------------------------------------------
// �G�̏K��
//-----------------------------------------------------------------------------
int GetTimer(void)
{
	return g_nTimer;
}

//-----------------------------------------------------------------------------
// �G�̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexTimer(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_aTimer[nIdx].pos.x - TIMER_SIZE, g_aTimer[nIdx].pos.y + TIMER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTimer[nIdx].pos.x - TIMER_SIZE, g_aTimer[nIdx].pos.y - TIMER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTimer[nIdx].pos.x + TIMER_SIZE, g_aTimer[nIdx].pos.y + TIMER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTimer[nIdx].pos.x + TIMER_SIZE, g_aTimer[nIdx].pos.y - TIMER_SIZE, 0.0f);

	//���_���̐ݒ�(�����j���O�}��)
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
}


