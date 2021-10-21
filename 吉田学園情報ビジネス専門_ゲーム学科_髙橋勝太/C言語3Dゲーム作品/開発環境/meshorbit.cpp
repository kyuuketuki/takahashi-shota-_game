//==============================================================================
//
// ���b�V���t�B�[���h�̕`��kmeshorbit.cpp�l
// AUTHOR : TAKAHASHI SHOTA
//
//==============================================================================
#include "meshorbit.h"
#include "model.h"
#include "input.h"
#include "score.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define ORBIT_WIDTHNUM	(10)								// ��(��)
#define ORBIT_DEPTHNUM	(1)									// �s��(���s)
#define ORBIT_WIDTH		(0.0f)							// ���̑傫��
#define ORBIT_DEPTH		(0.0f)							// ���s�̑傫��

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshOrbit = NULL;	// �o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshOrbit = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshOrbit = NULL;		// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posMeshOrbit;							// �ʒu
D3DXVECTOR3 g_rotMeshOrbit;							// ����
D3DXMATRIX g_mtxWorldMeshOrbit;						// ���[���h�}�g���b�N�X
MeshOrbit g_orbit[ORBIT_MAX];						//�t�B�[���h�̏��
int g_nAllPointOrbit;								// �����_��
int g_nPolygonOrbit;								// �|���S����
int g_nIdxPointOrbit;								// �C���f�b�N�X�o�b�t�@�̕K�v�Ȋm�ې�
float g_fWidthOrbit = ORBIT_WIDTH;					// �����̒[
float g_fDepthOrbit = ORBIT_DEPTH;					// ���s�̒[
int g_nWidthOrbit = ORBIT_WIDTHNUM + 1;				// �����̒��_��
int g_nDepthOrbit = ORBIT_DEPTHNUM + 1;				// ���s�̒��_��
													
//==============================================================================
// ����������
//==============================================================================
HRESULT InitMeshOrbit(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	WORD *pIdx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/10.png", &g_pTextureMeshOrbit);

	// �ϐ��̏�����
	g_nAllPointOrbit = ORBIT_DEPTHNUM * 2 * (ORBIT_WIDTHNUM + 2) - 2;						// �����_��
	g_nPolygonOrbit = ORBIT_WIDTHNUM * ORBIT_DEPTHNUM * 2 + (4 * (ORBIT_DEPTHNUM - 1));		// ���|���S����
	g_nIdxPointOrbit = g_nWidthOrbit * g_nDepthOrbit;										// �C���f�b�N�X�o�b�t�@�ł̒��_��

	for (int nCnt = 0; nCnt < ORBIT_MAX; nCnt++)
	{
		g_orbit[nCnt].nAllPoint = 0;
		g_orbit[nCnt].nPolygon = 0;
		g_orbit[nCnt].nIdxPoint = 0;
		g_orbit[nCnt].bUse = false;
	}

	float fWidthMax = g_fWidthOrbit * (float)ORBIT_WIDTHNUM;
	float fDepthMax = g_fDepthOrbit * (float)ORBIT_DEPTHNUM;

	PLAYER *pModel;
	pModel = GetModel();

	//g_orbit[0].pMtxParent = pModel->mtxWorld;
	//g_orbit[0].pMtxParent = pModel->aModel[1].mtxWorld;

	//g_orbit[0].aOffice[0] = D3DXVECTOR3(pModel->aModel[5].mtxWorld._41, pModel->aModel[5].mtxWorld._42, pModel->aModel[5].mtxWorld._43);
	//g_orbit[0].aOffice[1] = D3DXVECTOR3(pModel->aModel[1].mtxWorld._41, pModel->aModel[1].mtxWorld._42, pModel->aModel[1].mtxWorld._43);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_nIdxPointOrbit,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshOrbit,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshOrbit->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < g_nDepthOrbit; nCnt++)
	{// ���s��
		for (int nCntA = 0; nCntA < g_nWidthOrbit; nCntA++)
		{
			// ����
			// �|���S���̊e���_���W
			pVtx[0].pos = D3DXVECTOR3(-fWidthMax / 2.0f + (float)nCntA * g_fWidthOrbit, g_posMeshOrbit.y, fDepthMax / 2.0f - (float)nCnt * g_fDepthOrbit);

			// �@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �e���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);

			// �e�N�X�`�����_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntA, 1.0f * nCnt);
			//pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshOrbit->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAllPointOrbit,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&g_pIdxBuffMeshOrbit,NULL);

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshOrbit->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntA = 0; nCntA < ORBIT_DEPTHNUM; nCntA++)
	{
		for (int nCnt = 0; nCnt < g_nWidthOrbit + 1; nCnt++, pIdx += 2)
		{
			if (nCnt != 0 && nCnt == g_nWidthOrbit && nCntA != ORBIT_DEPTHNUM - 1)
			{// �E�[����܂�Ԃ���
				pIdx[0] = pIdx[-1];
				pIdx[1] = pIdx[-2] + 1;
			}
			else if (nCntA == ORBIT_DEPTHNUM - 1 && nCnt == g_nWidthOrbit)
			{// �I�����ɖ�������
				break;
			}
			else
			{// �ʏ�z�u
				pIdx[0] = g_nWidthOrbit + (g_nWidthOrbit * nCntA) + nCnt;
				pIdx[1] = pIdx[0] - g_nWidthOrbit;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshOrbit->Unlock();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitMeshOrbit(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshOrbit != NULL)
	{
		g_pVtxBuffMeshOrbit->Release();
		g_pVtxBuffMeshOrbit = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureMeshOrbit != NULL)
	{
		g_pTextureMeshOrbit->Release();
		g_pTextureMeshOrbit = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshOrbit != NULL)
	{
		g_pIdxBuffMeshOrbit->Release();
		g_pIdxBuffMeshOrbit = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateMeshOrbit(void)
{

}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawMeshOrbit(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	MeshOrbit *pOrbit;
	pOrbit = &g_orbit[0];

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for (int nCnt = 0; nCnt < ORBIT_MAX; nCnt++, pOrbit++)
	{
		if (pOrbit->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldMeshOrbit);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_orbit[0].aOffice[0].x, g_orbit[0].aOffice[0].y, g_orbit[0].aOffice[0].z);
			D3DXMatrixMultiply(&pOrbit->aMtxWorldPoint[0], &pOrbit->aMtxWorldPoint[0], &mtxTrans);

			// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&pOrbit->aMtxWorldPoint[0], &pOrbit->aMtxWorldPoint[0], &g_orbit[0].pMtxParent);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_orbit[0].aOffice[1].x, g_orbit[0].aOffice[1].y, g_orbit[0].aOffice[1].z);
			D3DXMatrixMultiply(&pOrbit->aMtxWorldPoint[1], &pOrbit->aMtxWorldPoint[1], &mtxTrans);

			// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&pOrbit->aMtxWorldPoint[1], &pOrbit->aMtxWorldPoint[1], &g_orbit[0].pMtxParent);

			// ���[�J���ϐ��錾
			VERTEX_3D *pVtx;
			PLAYER *pModel;
			pModel = GetModel();

			//// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffMeshOrbit->Lock(0, 0, (void**)&pVtx, 0);

			//���炷
			pVtx[20].pos = pVtx[18].pos;
			pVtx[18].pos = pVtx[16].pos;
			pVtx[16].pos = pVtx[14].pos;
			pVtx[14].pos = pVtx[12].pos;
			pVtx[12].pos = pVtx[10].pos;
			pVtx[10].pos = pVtx[8].pos;
			pVtx[8].pos = pVtx[6].pos;
			pVtx[6].pos = pVtx[4].pos;
			pVtx[4].pos = pVtx[2].pos;
			pVtx[2].pos = pVtx[0].pos;

			//���
			pVtx[0].pos = D3DXVECTOR3(pModel->aModel[5].mtxWorld._41, pModel->aModel[5].mtxWorld._42, pModel->aModel[5].mtxWorld._43);
			//pVtx[0].pos = g_orbit[0].pos;

			//���炷
			pVtx[21].pos = pVtx[19].pos;
			pVtx[19].pos = pVtx[17].pos;
			pVtx[17].pos = pVtx[15].pos;
			pVtx[15].pos = pVtx[13].pos;
			pVtx[13].pos = pVtx[11].pos;
			pVtx[11].pos = pVtx[9].pos;
			pVtx[9].pos = pVtx[7].pos;
			pVtx[7].pos = pVtx[5].pos;
			pVtx[5].pos = pVtx[3].pos;
			pVtx[3].pos = pVtx[1].pos;

			//���
			pVtx[1].pos = D3DXVECTOR3(pModel->aModel[4].mtxWorld._41, pModel->aModel[4].mtxWorld._42, pModel->aModel[4].mtxWorld._43);
			///pVtx[1].pos = g_orbit[1].pos;

			// ���_�o�b�t�@���A�����b�N����
			g_pVtxBuffMeshOrbit->Unlock();

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshOrbit);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshOrbit, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshOrbit);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshOrbit);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				0,
				0,
				g_nIdxPointOrbit,			// ���_��
				0,
				g_nPolygonOrbit);			// �v���~�e�B�u��
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

MeshOrbit * GetOrbit(void)
{
	return &g_orbit[0];
}

//==============================================================================
// �t�B�[���h�̐ݒ�
//==============================================================================
void SetOrbit(D3DXVECTOR3 pos, D3DXVECTOR3 pos2)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;

	MeshOrbit *pOrbit;
	pOrbit = &g_orbit[0];

	// �t�B�[���h�̐ݒ�
	for (int nCnt = 0; nCnt < ORBIT_MAX; nCnt++, pOrbit++)
	{
		if (pOrbit->bUse == false)
		{
			pOrbit->pos = pos;
			pOrbit->pos2 = pos2;

			//�g�p���Ă����邩
			pOrbit->bUse = true;

			//break;
		}
	}
}