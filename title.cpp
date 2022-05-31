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

//===�^�C�g���̏����Ŏg�p�@�i�֐��j===

//PushEnter��_�ł����鎞�Ɏg���֐�
int PushEnterCnt = 0;				//�J�E���^
const int PushEnterCntMAX = 100;	//�J�E���^MAX�l
BOOL PushEnterBrink = FALSE;		//�_�ł��Ă��邩�H

//===�t�@�C���f�ށi�N���X�j===

//����
MOVIE OpeningMOVIE;				//�I�[�v�j���O���[�r�[

//���y
SOUND TitleBGM;					//�^�C�g����BGM

//�摜
IMAGE TitleIMAGE;				//�^�C�g���̔w�i
IMAGE TitleEnterIMAGE;			//PushEnter

IMAGE HikkaduwaPresenIMAGE[HikkaduwaPresen_SIZE];	//�q�b�J�h�D�A�̃v���C�����̉摜����ꂽ�z��
IMAGE TrublePresenIMAGE[TruNblePresen_SIZE];		//�^���u�[���̃v���C�����̉摜����ꂽ�z��

//�^�C�g���f�ރ��[�h
BOOL GameLoad_Title()
{
	//�摜�̓ǂݍ���
	if (TitleIMAGE.LoadImageMem(".\\image\\title\\�^�C�g�����.png") == FALSE) return FALSE;				//�^�C�g���w�i�摜
	if (TitleEnterIMAGE.LoadImageMem(".\\image\\title\\TitlePushEnter.png") == FALSE) return FALSE;				//�^�C�g���w�i�摜

	if (HikkaduwaPresenIMAGE[0].LoadImageMem(".\\image\\title\\�q�b�J�h�D�A����1.png") == FALSE) return FALSE;	//�q�b�J�h�D�A�v���C�����摜�@
	if (HikkaduwaPresenIMAGE[1].LoadImageMem(".\\image\\title\\�q�b�J�h�D�A����2.png") == FALSE) return FALSE;	//�q�b�J�h�D�A�v���C�����摜�A
	if (TrublePresenIMAGE[0].LoadImageMem(".\\image\\title\\�^���u�[������1.png") == FALSE) return FALSE;		//�^���u�[���v���C�����摜�@
	if (TrublePresenIMAGE[1].LoadImageMem(".\\image\\title\\�^���u�[������2.png") == FALSE) return FALSE;		//�^���u�[���v���C�����摜�@

	//���y�̓ǂݍ���
	//if (TitleBGM.LordSound(".\\audio\\title\\harpohikunezumi.mp3", 100, PLAYTYPE::BGM) == FALSE) return FALSE;

	//����̓ǂݍ���
	if (OpeningMOVIE.LoadMOVIE(".\\movie\\�I�[�v�j���O.mp4",0,PLAYTYPE::NOMAL) == FALSE) return FALSE;		//�I�[�v�j���O���[�r�[

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

	//�摜�̈ʒu��ݒ�
	TitleIMAGE.SetImage(0, 0);					//�w�i�摜
	HikkaduwaPresenIMAGE[0].SetImage(0,0);		//�q�b�J�h�D�A�̐����摜�@
	HikkaduwaPresenIMAGE[1].SetImage(0,0);		//�q�b�J�h�D�A�̐����摜�A
	TrublePresenIMAGE[0].SetImage(0,0);			//�^���u�[���̐����摜�@
	TrublePresenIMAGE[1].SetImage(0,0);			//�^���u�[���̐����摜�A
	
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
VOID Title_Proc(){



	return;
}

//�^�C�g���`��
VOID Title_Draw()
{

	//OpeningMOVIE.MyPlayMOVIE();

	//�^�C�g�����_�w�i
	TitleIMAGE.DrawImage();

	//PushEnter��_�ł�����
	if (PushEnterCnt < PushEnterCntMAX) { PushEnterCnt++; }
	else
	{
		if (PushEnterBrink == TRUE)PushEnterBrink = FALSE;
		else if (PushEnterBrink == FALSE)PushEnterBrink = TRUE;

		PushEnterCnt = 0;	//�J�E���^��������
	}

	if (PushEnterBrink == TRUE)
	{
		//�������ɂ���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)PushEnterCnt / PushEnterCntMAX) * 255);

		//PushEnter�̕`��
		TitleEnterIMAGE.DrawImage();

		//�������I��
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (PushEnterBrink == FALSE)
	{
		//�������ɂ���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)(PushEnterCntMAX - PushEnterCnt) / PushEnterCntMAX) * 255);

		//PushEnter�̕`��
		TitleEnterIMAGE.DrawImage();

		//�������I��
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//�q�b�J�h�D�A�̐����摜��\��
	//HikkaduwaPresenIMAGE[0].DrawImage();
	//HikkaduwaPresenIMAGE[1].DrawImage();

	//�^���u�[���̐����摜��\��
	//TrublePresenIMAGE[0].DrawImage();
	//TrublePresenIMAGE[1].DrawImage();




	return;
}



