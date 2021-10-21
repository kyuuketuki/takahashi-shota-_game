//=============================================================================
//
// ���b�V���t�B�[���h����[meshfield.cpp]
// Author; takahashi syota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "meshfield.h"
#include "Scene3D.h"
#include "manager.h"
#include "Renderer.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMeshfield::CMeshfield()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMeshfield::~CMeshfield()
{

}

//=============================================================================
//���b�V���t�B�[���h�̏���������
//=============================================================================
HRESULT CMeshfield::Init(D3DXVECTOR3 pos, float fHight, float fWidth)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;

	LPDIRECT3DDEVICE9 pDevice;
	WORD *pIdx;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �ϐ��̏�����
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nAllPoint = DEPTHNUM * 2 * (WIDTHNUM + 2) - 2;				// �����_��
	m_nPolygon = WIDTHNUM * DEPTHNUM * 2 + (4 * (DEPTHNUM - 1));	// ���|���S����
	m_nIdxPoint = m_nWidth * m_nDepth;								// �C���f�b�N�X�o�b�t�@�ł̒��_��

	//�ő�T�C�Y�̌v�Z
	float fWidthMax = fWidth * (float)WIDTHNUM;
	float fDepthMax = fHight * (float)DEPTHNUM;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nIdxPoint,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_pVtxBuff,NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nDepth; nCnt++)
	{
		// ���s��
		for (int nCntA = 0; nCntA < m_nWidth; nCntA++)
		{
			// ����	 
			// �|���S���̊e���_���W
			pVtx[0].pos = D3DXVECTOR3(-fWidthMax / 2.0f + (float)nCntA * m_fWidth, m_pos.y, fDepthMax / 2.0f - (float)nCnt * m_fDepth);

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
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nAllPoint,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_pIdxBuff,NULL);

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntA = 0; nCntA < DEPTHNUM; nCntA++)
	{
		for (int nCnt = 0; nCnt < m_nWidth + 1; nCnt++, pIdx += 2)
		{
			if (nCnt != 0 && nCnt == m_nWidth && nCntA != DEPTHNUM - 1)
			{
				// �E�[����܂�Ԃ���
				pIdx[0] = pIdx[-1];
				pIdx[1] = pIdx[-2] + 1;
			}
			else if (nCntA == DEPTHNUM - 1 && nCnt == m_nWidth)
			{
				// �I�����ɖ�������
				break;
			}
			else
			{
				// �ʏ�z�u
				pIdx[0] = m_nWidth + (m_nWidth * nCntA) + nCnt;
				pIdx[1] = pIdx[0] - m_nWidth;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;
}


//=============================================================================
//���b�V���t�B�[���h�̏I������
//=============================================================================
void CMeshfield::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
//���b�V���t�B�[���h�̍X�V����
//=============================================================================
void CMeshfield::Update(void)
{

}

//=============================================================================
//���b�V���t�B�[���h�̕`�揈��
//=============================================================================
void CMeshfield::Draw(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;// �v�Z�p�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,NULL);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,
		0,
		m_nIdxPoint,			// ���_��
		0,
		m_nPolygon);			// �v���~�e�B�u��
}

//=============================================================================
//���b�V���t�B�[���h�̃N���G�C�g����
//=============================================================================
CMeshfield * CMeshfield::Create(D3DXVECTOR3 pos,float fHight, float fWidth)
{
	//�C���X�^���X����
	CMeshfield *pMeshfield = NULL;
	pMeshfield = new CMeshfield;

	//�������Ăяo��
	pMeshfield->Init(pos, fHight, fWidth);

	return pMeshfield;
}
