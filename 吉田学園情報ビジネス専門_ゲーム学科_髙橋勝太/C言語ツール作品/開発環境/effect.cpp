//================================================
//
//�ǂ̏���[Effect.h]
// Author; takahashi shouta
//
//================================================
#include "Effect.h"

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;				//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		//���_���
D3DXMATRIX g_mtxWorldEffect;							//���[���h�}�g���b�N�X
EFFECT g_Effect[MAX_EFFECT];							//�G�t�F�N�g�̍\����

//====================
//�r���{�[�h�̏���������
//====================
HRESULT InitEffect(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect.png", &g_pTextureEffect);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//�ʒu
		g_Effect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//����
		g_Effect[nCntEffect].nLife = 0;

		//����
		g_Effect[nCntEffect].nType = 0;

		//����
		g_Effect[nCntEffect].fHeigth = 0;

		//��
		g_Effect[nCntEffect].fWidth = 0;

		//�g���Ă��邩
		g_Effect[nCntEffect].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		SetVertexEffect(nCntEffect);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();

	return S_OK;
}

//==================
//�r���{�[�h�̏I������
//==================
void UninitEffect(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//==================
//�r���{�[�h�̍X�V����
//==================
void UpdateEffect(void)
{
	EFFECT *pEffect;
	pEffect = &g_Effect[0];
	VERTEX_3D *pVtx;

	int nSizeDate = 0;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		//�g�p����Ă���Ƃ�
		if (g_Effect[nCntEffect].bUse == true)
		{
			//���������炷
			pEffect->nLife--;
			pEffect->nLifeBullet += 25;

			//���̃J���[
			if (pEffect->nType == 2)
			{
				//���_�J���[�̐ݒ�			
				pVtx[0].col = D3DCOLOR_RGBA(128, 128, 128, 255 - pEffect->nLifeBullet);
				pVtx[1].col = D3DCOLOR_RGBA(128, 128, 128, 255 - pEffect->nLifeBullet);
				pVtx[2].col = D3DCOLOR_RGBA(128, 128, 128, 255 - pEffect->nLifeBullet);
				pVtx[3].col = D3DCOLOR_RGBA(128, 128, 128, 255 - pEffect->nLifeBullet);
			}

			//�����`�F�b�N
			if (pEffect->nLife <= 0)
			{
				pEffect->bUse = false;
			}

			//�ʒu�̍X�V
			pEffect->pos.x += pEffect->move.x;
			pEffect->pos.y += pEffect->move.y;
			pEffect->pos.z += pEffect->move.z;
		}
		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//====================
//�r���{�[�h�̕`�揈��
//====================
void DrawEffect(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxView;

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//Z�o�b�t�@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	////�A���t�@�e�X�g
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC,0);

	//���C�e�B���O�𖳌�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//// ���Z�����̐���
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//�g�p����Ă���Ƃ�
		if (g_Effect[nCntEffect].bUse == true)
		{
			if (g_Effect[nCntEffect].nType == 3)
			{
				//Z�o�b�t�@
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			}

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldEffect);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_mtxWorldEffect, NULL, &mtxView);//�t�s������߂�
			g_mtxWorldEffect._41 = 0.0f;
			g_mtxWorldEffect._42 = 0.0f;
			g_mtxWorldEffect._43 = 0.0f;

			//�ʒu�̔��]
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEffect);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			//�|���S���̕`��
			//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	//���C�e�B���O��L������
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�o�b�t�@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	////�A���t�@�e�X�g
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////�ʏ�̍����ɖ߂�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType, int nLifeBullet)
{
	EFFECT *pEffect;

	VERTEX_3D *pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pEffect = &g_Effect[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (g_Effect[nCntEffect].bUse == false)
		{
			//�ʒu
			pEffect->pos = pos;

			//�ړ���
			pEffect->move = move;

			//�^�C�v
			pEffect->nType = nType;

			//���C�t
			pEffect->nLife = nLife;

			//�J���[��ς��鎞��
			pEffect->nLifeBullet = nLifeBullet;

			//�g�p����
			pEffect->bUse = true;

			break;
		}
		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

void SetFire(D3DXVECTOR3 pos)
{
	EFFECT *pEffect;

	VERTEX_3D *pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�A�h���X
	pEffect = &g_Effect[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (g_Effect[nCntEffect].bUse == false)
		{
			//�p�[�e�B�N��
			for (int nCnt = 0; nCnt < 1; nCnt++)
			{
				D3DXVECTOR3 move;
				float fAngle;
				int nLife;
				int nSpeed;
				nLife = rand() % 70;
				nSpeed = (rand() % 10) / 10;
				fAngle = (float)(rand() % 628 - 314) / 100.0f;
				move.x = sinf(fAngle)*(0.1f + nSpeed);
				move.y = 0.9;
				move.z = cosf(fAngle)*(0.1f + nSpeed);
				SetEffect(D3DXVECTOR3(pos.x, pos.y, pos.z), move, nLife, 2, 50);
			}
		}
		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//-----------------------------------------------------------------------------
// �e�̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexEffect(int nIdx)
{
	VERTEX_3D *pVtx;
	EFFECT *pEffect;
	pEffect = &g_Effect[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - EFFECT_SIZE, pEffect->pos.y + EFFECT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x + EFFECT_SIZE, pEffect->pos.y + EFFECT_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x - EFFECT_SIZE, pEffect->pos.y - EFFECT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + EFFECT_SIZE, pEffect->pos.y - EFFECT_SIZE, 0.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//-------------------------------
//�e�̏��擾
//-------------------------------
EFFECT * GetEffect(void)
{
	return &g_Effect[0];
}