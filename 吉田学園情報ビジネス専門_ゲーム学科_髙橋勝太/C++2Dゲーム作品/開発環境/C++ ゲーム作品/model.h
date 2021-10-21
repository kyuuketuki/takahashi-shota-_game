//=============================================================================
//
// ���f������ [model.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _MODEL_H_
#define _MODEL_H_

#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#include "main.h"
#include "scene.h"

//=============================================================================
// �|���S���N���X�̒�`
//=============================================================================
//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 nor;
//	D3DCOLOR col;
//	D3DXVECTOR2 tex;
//} VERTEX_3D;

//�p����`��N���X
class CModel
{
public:
	CModel(int nPriority = 5, int nType = 0);								//�R���X�g���N�^
	virtual ~CModel();														//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pTextName);		//����������
	void Uninit(void);														//�I������
	void Update(void);														//�X�V����
	void Draw(void);														//�`�揈��

	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pTextName);								//��������

	void SetParent(CModel *pModel);
	D3DXMATRIX GetMtxWorld(void);

private:
	LPD3DXMESH		m_pMesh;			//���b�V��
	LPD3DXBUFFER	m_pBuffMat;			//�o�b�t�@
	DWORD			m_nNumMat;			//�}�g���b�N�X
	D3DXMATRIX		m_mtxWorld;			//���[���h�}�g���b�N�X
	D3DXVECTOR3		m_pos;				//�ʒu
	D3DXVECTOR3		m_rot;				//����
	int				m_nNumVtx;			//���_��
	float			m_fRot;				//
	CModel			*m_pParent;			//

};

#endif