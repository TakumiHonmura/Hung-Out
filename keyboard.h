#pragma once
#include "main.h"

//===================================================================
// �}�N����`
//===================================================================

//�L�[�̎��
#define KEY_KIND_MAX	256

//===================================================================
// �L�[�{�[�h�N���X
//===================================================================

class KEYBOARD
{
private:
	char tempKeyState[KEY_KIND_MAX];	//���͏�Ԃ��Ǘ�
	int allKeyState[KEY_KIND_MAX];		//�S�ẴL�[�̓��͎��Ԃ��Ǘ�
	int oldAllKeyState[KEY_KIND_MAX];	//�ȑO�̑S�ẴL�[�̓��͎��Ԃ��Ǘ�
public:
	KEYBOARD();
	VOID AllKeyUpdate(VOID);						//�L�[�̓��͏�Ԃ��X�V
	BOOL KeyDown(int KEY_INPUT_);					//�L�[�R�[�h�ŃL�[�̓��͂𔻒f
	BOOL KeyUp(int KEY_INPUT_);						//�L�[�R�[�h�ŃL�[�̉����グ�𔻒f
	BOOL KeyClick(int KEY_INPUT_);					//�L�[�R�[�h�ŃL�[�̃N���b�N�𔻒f
	BOOL KeyDownKeep(int KEY_INPUT_, int millTime);	//�L�[�R�[�h�ŃL�[�̌p�����͂𔻒f
};

//=========================================================
// �ϐ��̊O���錾
//=========================================================

//�L�[�{�[�h�̊Ǘ�
extern KEYBOARD keyboard;