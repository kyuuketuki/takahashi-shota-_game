//==============================================================================
//
// �Q�[���p�b�h����[gamepad.h]
// Author; takahashi shota
//
//==============================================================================

#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

//==============================================================================
//�C���N���[�h
//==============================================================================
#include "main.h"
#include "input.h"

//=============================================================================
// �Q�[���p�b�h�N���X�̒�`
//=============================================================================
class CGamepad : CInput
{
public:

	//�񋓌^�i�{�^���̎�ށj
	typedef enum
	{
		ButtonStateNone = 0,
		ButtonStateDown,
		ButtonStatePush,
		ButtonStateUp,
		ButtonStateMax,
	} ButtonState;

	CGamepad();
	~CGamepad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	void ButtonSet(DIJOYSTATE pad_data);
	bool IsButtonPush(KEYINFO button);
	bool IsButtonUp(KEYINFO button);
	bool IsButtonDown(KEYINFO button);
	bool BuPu(KEYINFO button, int nCnt);
	bool BuUp(KEYINFO button, int nCnt);
	bool BuDo(KEYINFO button, int nCnt);

	static BOOL CALLBACK EnumJoysticksCallback(
		const DIDEVICEINSTANCE *pdidoi, VOID *pContext);		// �R�[���o�b�N�֐�
	int GetNumControl(void) { return m_nController; }			// �R���g���[���[�̐����擾
private:
	ButtonState m_ButtonStates[KEYINFO::KEYINFO_MAX];
	static int m_nController;
};
#endif

