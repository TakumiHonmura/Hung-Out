#pragma once
#include "main.h"
#include "font.h"		//�t�H���g�g�p�ړI
#include "keyboard.h"	//�L�[���͖ړI

//�V�[���Ɋւ���֐��������Ă��܂�

extern VOID Title(VOID);		//�^�C�g�����
extern VOID TitleProc(VOID);	//�^�C�g�����(����)
extern VOID TitleDraw(VOID);	//�^�C�g�����(�`��)

extern VOID ChangeScreen(GAME_SCREEN gameScreen); //�V�[����؂�ւ���