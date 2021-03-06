//=============================================================================
//
// ライフ処理 [life.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "life.h"
#include "manager.h"
#include "scene2D.h"
#include "scene.h"
#include "player.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CLife::m_apTextureLife[1] = {};
int g_nRecoveryCount = 0;

//==============================================================================
// コンストラクタ
//==============================================================================
CLife::CLife(int nPriority) : CScene2D(nPriority)
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CLife::~CLife()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	CScene2D::Init(pos, fSizeX, fSizeY);

	CManager::RecoveryPlayerLife(1);

	//現在のHPを取得
	m_nCount = CManager::GetPlayerLife();

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CLife::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
// 更新処理
//==============================================================================
void CLife::Update(void)
{
	//現在のライフを読み込む
	int nLifePlayer = CManager::GetPlayerLife();

	//ダメージを与える
	if (m_nCount == (nLifePlayer + 1))
	{
		//一番最後を消す
		Uninit();
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CLife::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
// 生成処理
//==============================================================================
CLife * CLife::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// ポインタ変数の生成
	CLife *pLife;
	pLife = new CLife;

	// NULLチェック
	if (pLife != NULL)
	{
		//ライフ生成
		pLife->Init(pos, fSizeX, fSizeY);
	}

	//テクスチャを入れる
	pLife->BindTexture(m_apTextureLife[0]);

	return pLife;
}

//==============================================================================
// テクスチャの読み込み
//==============================================================================
HRESULT CLife::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/life000.png", &m_apTextureLife[0]);

	return S_OK;
}

//==============================================================================
// テクスチャの破棄
//==============================================================================
void CLife::Unload(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		if (m_apTextureLife != NULL)
		{
			m_apTextureLife[nCnt]->Release();
			m_apTextureLife[nCnt] = NULL;
		}
	}
}

//==============================================================================
// 回復
//==============================================================================
void CLife::Recovery(int nLife)
{
	g_nRecoveryCount += nLife;
}
