//-----------------------------------------------------------------
//
// �v���C���[�̏��� (player.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
//#include "player.h"
#include"camera.h"
#include "shadow.h"
#include "model.h"

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			//�e�N�X�`��
SHADOW g_Shadow[MAX_SHADOW];

//-----------------------------------------------------------------------------
// �|���S���̏���������
//-----------------------------------------------------------------------------
HRESULT InitShadow(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/shadow000.jpg", &g_pTextureShadow);

	// �ϐ��̏�����
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].fWidth = 1.0f;
		g_Shadow[nCntShadow].fDepth = 1.0f;
		g_Shadow[nCntShadow].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffShadow, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++, pVtx += 4)
	{
		// �|���S���̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_Shadow[nCnt].pos.x - g_Shadow[nCnt].fWidth, g_Shadow[nCnt].pos.y, g_Shadow[nCnt].pos.z - g_Shadow[nCnt].fDepth);
		pVtx[1].pos = D3DXVECTOR3(g_Shadow[nCnt].pos.x - g_Shadow[nCnt].fWidth, g_Shadow[nCnt].pos.y, g_Shadow[nCnt].pos.z + g_Shadow[nCnt].fDepth);
		pVtx[2].pos = D3DXVECTOR3(g_Shadow[nCnt].pos.x + g_Shadow[nCnt].fWidth, g_Shadow[nCnt].pos.y, g_Shadow[nCnt].pos.z - g_Shadow[nCnt].fDepth);
		pVtx[3].pos = D3DXVECTOR3(g_Shadow[nCnt].pos.x + g_Shadow[nCnt].fWidth, g_Shadow[nCnt].pos.y, g_Shadow[nCnt].pos.z + g_Shadow[nCnt].fDepth);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);
		pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);
		pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);
		pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �|���S���̏I������
//-----------------------------------------------------------------------------
void UninitShadow(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//-----------------------------------------------------------------------------
// �|���S���̍X�V����
//-----------------------------------------------------------------------------
void UpdateShadow(void)
{

}

//-----------------------------------------------------------------------------
// �|���S���̕`�揈��
//-----------------------------------------------------------------------------
void DrawShadow(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	SHADOW *pShadow;
	pShadow = &g_Shadow[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���Z�����̐���
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_Shadow[nCnt].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pShadow->mtxWorld);

			// �����𔽉f
			pShadow->mtxWorld._11 = pShadow->fWidth;
			pShadow->mtxWorld._33 = pShadow->fDepth;

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pShadow->rot.y, pShadow->rot.x, pShadow->rot.z);
			D3DXMatrixMultiply(&pShadow->mtxWorld, &pShadow->mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pShadow->pos.x, pShadow->pos.y, pShadow->pos.z);
			D3DXMatrixMultiply(&pShadow->mtxWorld, &pShadow->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pShadow->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			// �|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
				2);						// �`�悷��v���~�e�B�u��
		}
	}

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
//int SetShadow(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	SHADOW *pShadow;
	pShadow = &g_Shadow[0];
	int nIdx = -1;

	// �e�̐ݒ�
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++, pShadow++)
	{
		if (pShadow->bUse == false)
		{
			pShadow->pos = pos;			// �ʒu�̐ݒ�

			pShadow->fWidth = fWidth;	// ���̐ݒ�

			pShadow->fDepth = fDepth;	// ���s�̐ݒ�

			pShadow->bUse = true;		// �g�p��Ԃւ̈ڍs

			nIdx = nCnt;				// �C���f�b�N�X�ւ̑��

			break;
		}
	}

	return nIdx;	// nIdx�ԖڂƂ��ĕԂ�
}

void SetPositionShadow(int nIdx, D3DXVECTOR3 pos)
{
	g_Shadow[nIdx].pos = pos;

	//VERTEX_3D *pVtx;
	//SHADOW *pShadow;
	//pShadow = &g_Shadow[0];

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	////pSpeed += nIdx;

	//pVtx += nIdx * 4;

	////���_���W
	//pVtx[0].pos = D3DXVECTOR3(pos.x - SHADOW_SIZE, 0.0f, pos.z + SHADOW_SIZE);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + SHADOW_SIZE, 0.0f, pos.z + SHADOW_SIZE);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - SHADOW_SIZE, 0.0f, pos.z - SHADOW_SIZE);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + SHADOW_SIZE, 0.0f, pos.z - SHADOW_SIZE);

	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffShadow->Unlock();
}
