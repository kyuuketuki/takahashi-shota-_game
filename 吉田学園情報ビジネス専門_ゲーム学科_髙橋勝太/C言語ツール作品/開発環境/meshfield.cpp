//==============================================================================
//
// ���b�V���t�B�[���h�̕`��kmeshfield.cpp�l
// AUTHOR : TAKAHASHI SHOTA
//
//==============================================================================
#include "meshfield.h"
#include "model.h"
#include "car.h"
#include "input.h"
#include "score.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define WIDTHNUM	(30)									// ��(��)
#define DEPTHNUM	(30)									// �s��(���s)
#define WIDTH		(100.0f)								// ���̑傫��
#define DEPTH		(100.0f)								// ���s�̑傫��

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	// �o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;		// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posMeshfield;							// �ʒu
D3DXVECTOR3 g_rotMeshfield;							// ����
D3DXMATRIX g_mtxWorldMeshfield;						// ���[���h�}�g���b�N�X
MeshField g_aField[FIELD_MAX];						//�t�B�[���h�̏��
int g_nAllPoint;									// �����_��
int g_nPolygon;										// �|���S����
int g_nIdxPoint;									// �C���f�b�N�X�o�b�t�@�̕K�v�Ȋm�ې�
float g_fWidth = WIDTH;								// �����̒[
float g_fDepth = DEPTH;								// ���s�̒[
int g_nWidth = WIDTHNUM + 1;						// �����̒��_��
int g_nDepth = DEPTHNUM + 1;						// ���s�̒��_��
//float g_SpeedCarDate;
//float g_CarDate;
									
//==============================================================================
// ����������
//==============================================================================
HRESULT InitMeshfield(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	WORD *pIdx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	//�s�s
	D3DXCreateTextureFromFile(pDevice,"data/TEXTURE/field002.jpg",&g_pTextureMeshfield);

	//�X��
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field004.jpg", &g_pTextureMeshfield);

	//�r��
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/wilderness.jpg", &g_pTextureMeshfield);

	// �ϐ��̏�����
	g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	g_nAllPoint = DEPTHNUM * 2 * (WIDTHNUM + 2) - 2;				// �����_��
	g_nPolygon = WIDTHNUM * DEPTHNUM * 2 + (4 * (DEPTHNUM - 1));	// ���|���S����
	g_nIdxPoint = g_nWidth * g_nDepth;								// �C���f�b�N�X�o�b�t�@�ł̒��_��

	for (int nCnt = 0; nCnt < FIELD_MAX; nCnt++)
	{
		g_aField[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].g_rotMeshfield = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		g_aField[nCnt].g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].nAllPoint = 0;
		g_aField[nCnt].nPolygon = 0;
		g_aField[nCnt].nIdxPoint = 0;
		g_aField[nCnt].bUse = false;
	}

	float fWidthMax = g_fWidth * (float)WIDTHNUM;
	float fDepthMax = g_fDepth * (float)DEPTHNUM;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_nIdxPoint,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < g_nDepth; nCnt++)
	{// ���s��
		for (int nCntA = 0; nCntA < g_nWidth; nCntA++ )
		{

			// ����
			// �|���S���̊e���_���W
			pVtx[0].pos = D3DXVECTOR3(-fWidthMax / 2.0f + (float)nCntA * g_fWidth, g_posMeshfield.y, fDepthMax / 2.0f - (float)nCnt * g_fDepth);

			//pVtx[0].pos = D3DXVECTOR3(g_aField[nCntA].g_posMeshfield.x + (float)nCntA * g_fWidth, g_posMeshfield.y, g_aField[nCntA].g_posMeshfield.z - (float)nCnt * g_fDepth);
			
			// �@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �e���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntA, 1.0f * nCnt);

			pVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshfield->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * g_nAllPoint,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntA = 0; nCntA < DEPTHNUM; nCntA++)
	{
		for (int nCnt = 0; nCnt < g_nWidth + 1; nCnt++, pIdx += 2)
		{
			if (nCnt != 0 && nCnt == g_nWidth && nCntA != DEPTHNUM - 1)
			{// �E�[����܂�Ԃ���
				pIdx[0] = pIdx[-1];
				pIdx[1] = pIdx[-2] + 1;
			}
			else if (nCntA == DEPTHNUM - 1 && nCnt == g_nWidth)
			{// �I�����ɖ�������
				break;
			}
			else
			{// �ʏ�z�u
				pIdx[0] = g_nWidth + (g_nWidth * nCntA) + nCnt;
				pIdx[1] = pIdx[0] - g_nWidth;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshfield->Unlock();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitMeshfield(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateMeshfield(void)
{

}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawMeshfield(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	MeshField *pField;
	pField = &g_aField[0];

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < FIELD_MAX; nCnt++, pField++)
	{
		if (pField->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldMeshfield);

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pField->g_rotMeshfield.y, pField->g_rotMeshfield.x, pField->g_rotMeshfield.z);
			D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pField->g_posMeshfield.x, pField->g_posMeshfield.y, pField->g_posMeshfield.z);
			D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshfield);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshfield);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				0,
				0,
				g_nIdxPoint,			// ���_��
				0,
				g_nPolygon);			// �v���~�e�B�u��
		}
	}
}

MeshField * GetMesh(void)
{
	return &g_aField[0];
}

//==============================================================================
// �t�B�[���h�̐ݒ�
//==============================================================================
void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float X, float Z)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;

	MeshField *pField;
	pField = &g_aField[0];

	// �t�B�[���h�̐ݒ�
	for (int nCnt = 0; nCnt < FIELD_MAX; nCnt++, pField++)
	{
		if (pField->bUse == false)
		{
			//����
			pField->g_rotMeshfield = rot;
			
			//�ʒu
			pField->g_posMeshfield = pos;

			pField->posM = pos;

			//�g�p���Ă����邩
			pField->bUse = true;

			break;
		}
	}
}