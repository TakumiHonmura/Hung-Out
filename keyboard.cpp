#include "keyboard.h"
//�L�[�{�[�h�Ɋւ���֐��������Ă��܂�

//=========================================================
//  �O���[�o���ϐ�
//=========================================================

KEYBOARD keyboard;


//=========================================================
//  �N���X�֐�
//=========================================================

KEYBOARD::KEYBOARD()
{
	for (int i = 0; i < KEY_KIND_MAX; ++i) tempKeyState[i] = '\0';
	for (int i = 0; i < KEY_KIND_MAX; ++i) allKeyState[i] = NULL;
	for (int i = 0; i < KEY_KIND_MAX; ++i) oldAllKeyState[i] = NULL;
}

/// <summary>
/// �L�[�̓��͏�Ԃ��X�V
/// </summary>
/// <param name=""></param>
VOID KEYBOARD::AllKeyUpdate(VOID)
{
	//���O�̃L�[���͂��Ƃ��Ă���
	for (int i = 0; i < KEY_KIND_MAX; ++i)
	{
		oldAllKeyState[i] = allKeyState[i];
	}

	//���ׂẴL�[�̓��͏�Ԃ𓾂�
	GetHitKeyStateAll(tempKeyState);

	//������Ă���L�[�̎��Ԃ��X�V����
	for (int i = 0; i < KEY_KIND_MAX; ++i)
	{
		//�L�[�R�[�h�������Ă���Ƃ�
		if (tempKeyState[i] != 0)
		{
			++allKeyState[i];	//�����Ă��鎞�Ԃ����Z
		}
		else
		{
			allKeyState[i] = 0;	//�����Ă��鎞�Ԃ�0�ɖ߂�
		}
	}

	return;
}

/// <summary>
/// �L�[�R�[�h�ŃL�[�̓��͂𔻒f
/// </summary>
/// <param name="KEY_INPUT_">�L�[�R�[�h</param>
/// <returns></returns>
BOOL KEYBOARD::KeyDown(int KEY_INPUT_)
{
	if (allKeyState[KEY_INPUT_] != 0)	return TRUE;
	else								return FALSE;
}

/// <summary>
/// �L�[�R�[�h�ŃL�[�̉����グ�𔻒f
/// </summary>
/// <param name="KEY_INPUT_">�L�[�R�[�h</param>
/// <returns></returns>
BOOL KEYBOARD::KeyUp(int KEY_INPUT_)
{
	if (
		oldAllKeyState[KEY_INPUT_] != 0	//�ȑO�͉����Ă���
		&& allKeyState[KEY_INPUT_] == 0	//���݂͉����Ă��Ȃ�
		)
	{
		 return TRUE;
	}
	else return FALSE;
}

/// <summary>
/// �L�[�R�[�h�ŃL�[�̃N���b�N�𔻒f
/// </summary>
/// <param name="KEY_INPUT_">�L�[�R�[�h</param>
/// <returns></returns>
BOOL KEYBOARD::KeyClick(int KEY_INPUT_)
{
	if (
		oldAllKeyState[KEY_INPUT_] != 0	//�ȑO�͉����Ă���
		&& allKeyState[KEY_INPUT_] == 0	//���݂͉����Ă��Ȃ�
		)
	{
		 return TRUE;
	}
	else return FALSE;
}

/// <summary>
/// �L�[�R�[�h�ŃL�[�̌p�����͂𔻒f
/// </summary>
/// <param name="KEY_INPUT_">�L�[�R�[�h</param>
/// <param name="millSec">�~���b</param>
/// <returns></returns>
BOOL KEYBOARD::KeyDownKeep(int KEY_INPUT_, int millTime)
{
	//�P�b��1000�~���b
	float MilliSec = 1000.0f;

	//���������Ă��鎞�Ԃ́A�~���b���~FPS�l
	//��j1500�~���b����/1000�~���@���@1.5�b�~60FPS = 90
	int UpdateTime = (millTime / (int)MilliSec) * 60;

	if (allKeyState[KEY_INPUT_] > UpdateTime)	return TRUE;	//���������Ă���
	else										return FALSE;	//���������Ă��Ȃ�
}