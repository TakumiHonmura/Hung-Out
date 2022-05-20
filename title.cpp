#include "scene.h"

//FPS
const int fadeTimeMill = 3000;						//�؂�ւ��~���b
const int fadeTimeMax = fadeTimeMill / 1000 * 60;	//�~���b���t���[���b�ɕϊ�

//�t�F�[�h�A�E�g
const int fadeOutInCntInit = 0;				//�����l
int fadeOutInCnt = fadeOutInCntInit;		//�t�F�[�h�A�E�g�̃J�E���^
const int fadeOutInCntMax = fadeTimeMax;	//�t�F�[�h�A�E�g�̃J�E���^MAX

BOOL isTitleEyeIn = FALSE;

const int titleEyeTimeMilli = 500; //�؂�ւ��ɂ����鎞��(�~���b)
const int titleEyeTimeMax = titleEyeTimeMilli * 60 / 1000;

//�A�C�C��
const int titleEyeInCntInit = 0;
int titleEyeInCnt = titleEyeInCntInit;
const int titleEyeInCntMax = titleEyeTimeMax;

//===�^�C�g���̏����Ŏg�p===


//===�t�@�C���f�ށi�N���X�j===

SOUND TitleBGM;					//�^�C�g����BGM
IMAGE TitleIMAGE;				//�^�C�g���̔w�i
IMAGE HikkaduwaPresenIMAGE[2];	//�q�b�J�h�D�A�̃v���C�����̉摜����ꂽ�z��
IMAGE TrublePresenIMAGE[2];	//�q�b�J�h�D�A�̃v���C�����̉摜����ꂽ�z��


//�^�C�g���f�ރ��[�h
BOOL GameLoad_Title()
{
	//if (TitleBGM.LordSound(".\\audio\\title\\harpohikunezumi.mp3", 100, PLAYTYPE::BGM) == FALSE) return FALSE;

	return TRUE;
}

//�^�C�g��������
VOID GameInit_Title()
{
	//�t�F�[�h�A�E�g
	fadeOutInCnt = fadeOutInCntInit;		//�t�F�[�h�A�E�g�̃J�E���^
	isTitleEyeIn = FALSE;
	//�A�C�C��
	titleEyeInCnt = titleEyeInCntInit;
}

//�^�C�g���폜
VOID GameDelete_Title(VOID)
{
	TitleBGM.~SOUND();
}

VOID Title()
{
	Title_Proc();
	Title_Draw();

	return;
}

//�^�C�g������
VOID Title_Proc()
{

	return;
}

//�^�C�g���`��
VOID Title_Draw()
{

	return;
}