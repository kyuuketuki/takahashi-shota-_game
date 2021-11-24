//=============================================================================
//
// ���͏��� [input.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "main.h"

//=============================================================================
//�C���v�b�g�N���X�̒�`
//=============================================================================
class CInput
{
public:
	//�񋓌^�i�{�^���̎��)
	typedef enum
	{
		RETURN = 0,
		X,
		W,
		S,
		A,
		D,
		SPACE,
		BACKSPACE,
		F,
		T,
		B,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		P,
		KEYINFO_MAX
	} KEYINFO;

	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
protected:
	LPDIRECTINPUTDEVICE8 m_pDeviceKey;
	static LPDIRECTINPUTDEVICE8 m_pDevice;
	static LPDIRECTINPUT8 m_pInput;
};

//=============================================================================
//�C���v�b�g�L�[�{�[�h�N���X�̒�`
//=============================================================================
class CInputKeyboard : CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
private:
	BYTE m_aKeyState[256];
	BYTE m_aKeyStateTrigger[256];
};
#endif
