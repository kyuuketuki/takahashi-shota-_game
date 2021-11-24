//=============================================================================
//
// �v���C���[���� [player.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//==============================================================================
//�C���N���[�h
//==============================================================================
#include "main.h"
#include "scene2D.h"

//�}�N����`
#define PLAYER_SIZE (50)

//=============================================================================
// �v���C���[�N���X�̒�`
//=============================================================================
//�p����`��N���X
class CPlayer : public CScene2D
{
public:
	CPlayer(int nPriority = 2);								//�R���X�g���N�^
	virtual ~CPlayer();										//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY);					//����������
	void	Uninit(void);																	//�I������
	void	Update(void);																	//�X�V����
	void	Draw(void);																		//�`�揈��

	static CPlayer	*Create(D3DXVECTOR3 pos, int nLifefloat, float fSizeX, float fSizeY);	//��������
	static HRESULT	Load(void);																//�e�N�X�`���ǂݍ���
	static void		Unload(void);															//�e�N�X�`���j��

	static void BulletLevel(void);
	static void SetBulletLevel(int nData);

	static bool GetBumped(void);
	static void SetBumped(bool bBumped);

	static D3DXVECTOR3	GetPlayer(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[5];		//�e�N�X�`���|�C���^�[
	D3DXVECTOR3					m_pos;				//�ʒu
	D3DXVECTOR3					m_move;				//�ړ���
	int							m_nType;			//�^�C�v�e�N�X�`�����ʗp
	int							m_nSpeed;			//�ړ���
	bool						m_nBulletLevelUP;	//�e�̃��x��
	bool						m_nBullet;			//�e�̃��x���p
	bool						m_nBullet2;			//�e�̃��x���p
	bool						m_nBullet3;			//�e�̃��x���p

	LPDIRECT3DTEXTURE9 m_pTextureMT[2];
	LPDIRECT3DSURFACE9 m_pRenderMT[2];
	LPDIRECT3DSURFACE9 m_pBuffMT[2];
	D3DVIEWPORT9 m_ViewportMT;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMT;
};

#endif