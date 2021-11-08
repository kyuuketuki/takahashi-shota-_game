//=============================================================================
//
// �v���C���[3D���� [player3D.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _PLAYER3D_H_
#define _PLAYER3D_H_

#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#include "main.h"
#include "scene.h"
#include "model.h"

#define MAX_PLAYER_PARTS (15)

//=============================================================================
// �|���S���N���X�̒�`
//=============================================================================
//�p����`��N���X
class CPlayer3D : public CScene
{
public:
	CPlayer3D(int nPriority = 5, int nType = 0);								//�R���X�g���N�^
	virtual ~CPlayer3D();														//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);					//����������
	void Uninit(void);															//�I������
	void Update(void);															//�X�V����
	void Draw(void);															//�`�揈��

	static CPlayer3D *Create();													//��������

private:
	CModel			*m_apModel[MAX_PLAYER_PARTS];				//���f���ւ̃|�C���^
	int				m_aIndexParent[MAX_PLAYER_PARTS];			//���f���̐e
	float			m_aOffset[MAX_PLAYER_PARTS][6];				//���f���̈ʒu������ݒu
	char			*m_pTextName[MAX_PLAYER_PARTS];				//���O�ۑ�

	LPD3DXMESH		m_pMesh;			//���b�V��
	LPD3DXBUFFER	m_pBuffMat;			//�o�b�t�@
	DWORD			m_nNumMat;			//�}�g���b�N�X
	D3DXMATRIX		m_mtxWorld;			//���[���h�}�g���b�N�X
	D3DXVECTOR3		m_pos;				//�ʒu
	D3DXVECTOR3		m_rot;				//����
	int				m_nNumVtx;			//���_��
	float			m_fRot;				//��]
};

#endif