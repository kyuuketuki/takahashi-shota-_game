//-----------------------------------------------------------------
//
// �X�R�A�̏��� (score.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "score.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_SCORE		(3)						// �����蔻��̖ʂ̐�

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTextureScore = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//���_���
D3DXVECTOR3 g_PosScore;
SCORE g_aScore[256];
int g_nScore;//�X�R�A

//====================
//�|���S���̏���������
//====================
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_pTextureScore);

	//�X�R�A���Z�b�g
	g_nScore = 0;

	for (int nCntEnemy = 0; nCntEnemy < MAX_SCORE; nCntEnemy++)
	{
		g_aScore[nCntEnemy].nType = 0;
		g_aScore[nCntEnemy].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScore, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_SCORE; nCntBullet++, pVtx += 4)
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

		//���_���̐ݒ�(�����j���O�}��)
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();

	return S_OK;
}

//==================
//�|���S���̏I������
//==================
void UninitScore(void)
{
	//�e�N�X�`���̊J��
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_SCORE; nCntEnemyType++)
	{
		if (g_pTextureScore != NULL)
		{
			g_pTextureScore->Release();
			g_pTextureScore = NULL;
		}
	}
	//�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

}


//==================
//�|���S���̍X�V����
//==================
void UpdateScore(void)
{
	VERTEX_2D *pVtx;
	int nNumber[MAX_SCORE];

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//nNumber[0] = g_nScore % 100000000 / 10000000;
	//nNumber[1] = g_nScore % 10000000 / 1000000;
	//nNumber[2] = g_nScore % 1000000 / 100000;
	//nNumber[3] = g_nScore % 100000 / 10000;
	//nNumber[4] = g_nScore % 10000 / 1000;
	nNumber[0] = g_nScore % 1000 / 100;
	nNumber[1] = g_nScore % 100 / 10;
	nNumber[2] = g_nScore % 10 / 1;

	for (int nCutEnemy = 0; nCutEnemy < MAX_SCORE; nCutEnemy++)
	{
		pVtx[0].pos = D3DXVECTOR3((g_aScore[nCutEnemy].pos.x - SCORE_SIZE) + nCutEnemy * 10, g_aScore[nCutEnemy].pos.y + SCORE_SIZE, 0);
		pVtx[1].pos = D3DXVECTOR3((g_aScore[nCutEnemy].pos.x - SCORE_SIZE) + nCutEnemy * 10, g_aScore[nCutEnemy].pos.y - SCORE_SIZE, 0);
		pVtx[2].pos = D3DXVECTOR3((g_aScore[nCutEnemy].pos.x + SCORE_SIZE) + nCutEnemy * 10, g_aScore[nCutEnemy].pos.y + SCORE_SIZE, 0);
		pVtx[3].pos = D3DXVECTOR3((g_aScore[nCutEnemy].pos.x + SCORE_SIZE) + nCutEnemy * 10, g_aScore[nCutEnemy].pos.y - SCORE_SIZE, 0);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f*nNumber[nCutEnemy], 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f*nNumber[nCutEnemy], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*(nNumber[nCutEnemy] + 1), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*(nNumber[nCutEnemy] + 1), 0.0f);

		pVtx += 4;
	}
}

//==================
//�|���S���̕`�揈��
//==================
void DrawScore(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	int nCntVertex = 0;

	SCORE *pScore;
	pScore = &g_aScore[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCntBullet = 0; nCntBullet < MAX_SCORE; nCntBullet++, pScore++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScore);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntVertex, 2);
		if (g_aScore[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntVertex, 2);
		}

		nCntVertex += 4;
	}

}

///=================
//���Z����
//==================
void AddScore(int nValue)
{
	g_nScore += nValue;
}

//-----------------------------------------------------------------------------
// score�̐ݒ�
//-----------------------------------------------------------------------------
void SetScore(D3DXVECTOR3 pos, int nType)
{
	SCORE *pScore;
	pScore = &g_aScore[0];

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_SCORE; nCntEnemy++, pScore++)
	{
		if (pScore->bUse == false)
		{
			pScore->pos = pos;

			//���_���W
			SetVertexScore(nCntEnemy);

			pScore->nType = nType;

			pScore->bUse = true;

			break;
		}
		g_pVtxBuffScore->Unlock(); //�A�����b�N
	}
}

//-----------------------------------------------------------------------------
// �G�̏K��
//-----------------------------------------------------------------------------
SCORE*GetScore(void)
{
	return &g_aScore[0];
}

//-----------------------------------------------------------------------------
// �G�̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexScore(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_aScore[nIdx].pos.x - SCORE_SIZE, g_aScore[nIdx].pos.y + SCORE_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aScore[nIdx].pos.x - SCORE_SIZE, g_aScore[nIdx].pos.y - SCORE_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aScore[nIdx].pos.x + SCORE_SIZE, g_aScore[nIdx].pos.y + SCORE_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aScore[nIdx].pos.x + SCORE_SIZE, g_aScore[nIdx].pos.y - SCORE_SIZE, 0.0f);

	//���_���̐ݒ�(�����j���O�}��)
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

