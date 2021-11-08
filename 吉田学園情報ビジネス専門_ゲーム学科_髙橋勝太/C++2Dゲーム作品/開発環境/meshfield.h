//=============================================================================
//
//���b�V���t�B�[���h����[meshfield.h]
// Author; takahashi syota
//
//=============================================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "main.h"
#include "Scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define WIDTHNUM	(5)		// ��(��)
#define DEPTHNUM	(5)		// �s��(���s)
#define WIDTH		(40.0f)	// ���̑傫��
#define DEPTH		(40.0f)	// ���s�̑傫��
#define FIELD_MAX	(1)	// �t�B�[���h�̍ő吔

//=============================================================================
//�V�[��3D�N���X�̒�`
//=============================================================================
class CMeshfield : public CScene
{
public:
	CMeshfield(); //�R���X�g���N�^
	~CMeshfield();//�f�X�g���N�^

	static CMeshfield *Create(D3DXVECTOR3 pos,float fHight, float fWidth);

	HRESULT Init(D3DXVECTOR3 pos,float fHight, float fWidth);       //����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// �o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// ����
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	int m_nAllPoint;							// �����_��
	int m_nPolygon;								// �|���S����
	int m_nIdxPoint;							// �C���f�b�N�X�o�b�t�@�̕K�v�Ȋm�ې�
	float m_fWidth = WIDTH;				// �����̒[
	float m_fDepth = DEPTH;				// ���s�̒[
	int m_nWidth = WIDTHNUM + 1;		// �����̒��_��
	int m_nDepth = DEPTHNUM + 1;		// ���s�̒��_��
};
#endif
