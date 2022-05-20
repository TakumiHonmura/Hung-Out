#pragma once
#include "main.h"
#include "font.h"		//�t�H���g�g�p�ړI
#include "keyboard.h"	//�L�[���͖ړI

//�V�[���Ɋւ���֐��������Ă��܂�

//�V�[���̓ǂݍ���
BOOL GameLoad_Title(VOID);		//�^�C�g���V�[���ǂݍ���
BOOL GameLoad_TrunblePlay(VOID);		//Trunble�v���C�V�[���ǂݍ���

//�V�[���̏�����
VOID GameInit_Title(VOID);		//�^�C�g���V�[��������
VOID GameInit_TrunblePlay(VOID);		//Trunble�v���C�V�[��������

//�V�[���̍폜
VOID GameDelete_Title(VOID);	//�^�C�g���V�[���폜
VOID GameDelete_TrunblePlay(VOID);	//Trunble�v���C�V�[���폜


extern VOID Title(VOID);		//�^�C�g�����
extern VOID Title_Proc(VOID);	//�^�C�g�����(����)
extern VOID Title_Draw(VOID);	//�^�C�g�����(�`��)

extern VOID Trunble_Play(VOID);		//Trunble�̃v���C���
extern VOID Trunble_PlayProc(VOID);	//Trunble�̃v���C���(����)
extern VOID Trunble_PlayDraw(VOID);	//Trunble�̃v���C���(�`��)

extern VOID Hikkaduwa_Play(VOID);		//Hikkaduwa�̃v���C���
extern VOID Hikkaduwa_PlayProc(VOID);	//Hikkaduwa�̃v���C���(����)
extern VOID Hikkaduwa_PlayDraw(VOID);	//Hikkaduwa�̃v���C���(�`��)

extern VOID ChangeScreen(GAME_SCREEN gameScreen); //�V�[����؂�ւ���