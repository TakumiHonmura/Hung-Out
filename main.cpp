#include "main.h"
#include "font.h"
#include "fps.h"
#include "keyboard.h"
#include "scene.h"


//=========================================================
//  �V�[���֌W�̃O���[�o���ϐ�
// 
// CTRL+G 155 �R�����g�A�E�g
//=========================================================

//�V�[���Ǘ��̕ϐ�
GAME_SCREEN GameScreen;		//���݂̃Q�[���V�[��
GAME_SCREEN OldGameScreen;	//��O�Q�[���V�[��
GAME_SCREEN NextGameScreen;	//���̃Q�[���V�[��

//===��ʂ̐؂�ւ�===
//����͑S���̃X�N���[���J�ڂŃC���E�A�E�g�ǂ������g��
IMAGE eyeAbove; //�؂�ւ���ʗp����1
IMAGE eyeBelow; //�؂�ւ���ʗp����2

BOOL isEyeIn  = FALSE;
BOOL isEyeOut = FALSE;

int eyeTimeMilli = 500; //�؂�ւ��ɂ����鎞��(�~���b)
int eyeTimeMax = eyeTimeMilli * 60 / 1000;

//�A�C�C���A�E�g
int eyeInOutCntInit = 0;
int eyeInOutCnt = eyeInOutCntInit;
int eyeInOutCntMax = eyeTimeMax;

//=========================================================
//  �Q�[���V�[�����Ƃ̊֐�
//=========================================================

BOOL GameLoad(VOID);		//�f�[�^��Ǎ�

VOID GameInit(VOID);		//�f�[�^�̏�����

VOID GameDelete(VOID);		//�f�[�^�̍폜

VOID Title(VOID);		//�^�C�g�����
VOID TitleProc(VOID);	//�^�C�g�����(����)
VOID TitleDraw(VOID);	//�^�C�g�����(�`��)

VOID Change(VOID);		//�؂�ւ����
VOID ChangeProc(VOID);	//�؂�ւ����(����)
VOID ChangeDraw(VOID);	//�؂�ւ����(�`��)

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//Log.txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɂ���
	SetMainWindowText(GAME_TITLE);						//�^�C�g�����E�B���h�E�̍���ɕ\��
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�E�B���h�E�̉𑜓x��ݒ�
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);				//�E�B���h�E�̑傫����ݒ�
	SetBackgroundColor(255, 255, 255);					//�w�i�F��ݒ�
	SetWindowIconID(GAME_ICON_ID);						//�A�C�R���t�@�C����Ǎ�
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�E�B���h�E�o�[�̏��
	SetWaitVSyncFlag(TRUE);								//�f�B�X�v���C�̐���������L���ɂ���
	SetAlwaysRunFlag(TRUE);								//�E�B���h�E�������ƃA�N�e�B�u�ɂ���

	//DX���C�u�����̏���������(�G���[���N�����璼���ɏI��)
	if (DxLib_Init()) return -1;

	//�_�u���o�b�t�@�����O��L����
	SetDrawScreen(DX_SCREEN_BACK);

	//�ŏ��̃V�[���̓^�C�g����ʂ���
	GameScreen = GAME_SCREEN::TITLE;

	//�V�[���J�ڂł͕K���؂�ւ�������̂őO��͐؂�ւ����
	NextGameScreen = GAME_SCREEN::CHANGE;
	OldGameScreen = GAME_SCREEN::CHANGE;

	//�t�H���g��ǉ�&�����Ƀt�H���g�̃N���X�ϐ����Ԃ����ޖ\���ɏo��
	if (!FontAdd()) return FALSE;
	
	//�Q�[���̓ǂݍ���(���s���̓f�[�^�������Ĉُ�I��)
	if (!GameLoad())
	{
		DxLib_End();
		return -1;
	}

	//�Q�[��������������
	GameInit();

	while (1)
	{
		if (ProcessMessage()) break;  //���b�Z�[�W���󂯎�葱����
		if (ClearDrawScreen()) break; //���b�Z�[�W���󂯎�葱����

		//�L�[�{�[�h�̓��͍X�V
		keyboard.AllKeyUpdate();

		//FPS�l�̍X�V
		fps.FPSUpdate();

		//ESC�L�[�ŋ����I��
		if (keyboard.KeyClick(KEY_INPUT_ESCAPE) == TRUE) { break; }

		switch (GameScreen)
		{
		case GAME_SCREEN::TITLE://�^�C�g�����
			Title();
			break;
		case GAME_SCREEN::CHANGE://�؂�ւ����
			Change();
			break;
		default:
			break;
		}

		//FPS�l��`��
		fps.FPSDraw();

		//FPS�l��҂�
		fps.FPSWait();

		ScreenFlip();			//�_�u���o�b�t�@�����O������ʂ�`��
	}

	GameDelete();	//�f�[�^(�n���h��)���폜

	FontRemove();	//�t�H���g���폜

	DxLib_End();	//DX���C�u�����̏I������

	return 0;		//�\�t�g�̏I��
}


//=========================================================
//  �Q�[���f�[�^�Ɋւ��֐�
//=========================================================

BOOL GameLoad(VOID)
{
	//�t�H���g�̃n���h�����擾
	if (fontDef.FontCreateHandle() == FALSE) { return FALSE; }
	if (fontDef_h1ver.FontCreateHandle() == FALSE) { return FALSE; }
	if (fontDef_h2ver.FontCreateHandle() == FALSE) { return FALSE; }
	if (fontDef_h3ver.FontCreateHandle() == FALSE) { return FALSE; }
	if (fontDef_h4ver.FontCreateHandle() == FALSE) { return FALSE; }

	//fontDef���f�t�H���g�t�H���g��
	fontDef.SetDefaultFont();

	//�؂�ւ���ʗp
	//eyeAbove.LoadImageMem(".\\image\\change\\EyeAbove.png");
	//eyeBelow.LoadImageMem(".\\image\\change\\EyeBelow.png");

	return TRUE;
}

VOID GameInit(VOID)
{
	//��ʐ؂�ւ��̉摜�̈ʒu
	eyeAbove.SetImage(0, -GAME_HEIGHT);
	eyeBelow.SetImage(0, GAME_HEIGHT);
}

VOID GameDelete(VOID)
{
	//�؂�ւ���ʗp
	eyeAbove.~IMAGE();
	eyeBelow.~IMAGE();
}


//=========================================================
//  ��ʐ؂�ւ��̊֐�
//=========================================================

/// <summary>
/// �؂�ւ����
/// </summary>
VOID Change()
{
	ChangeProc();
	ChangeDraw();
}

/// <summary>
/// �؂�ւ���ʂ̏���
/// </summary>
VOID ChangeProc()
{

	//�A�C�C��
	if (isEyeIn)
	{
		if (eyeInOutCnt > eyeInOutCntInit)
		{
			eyeInOutCnt--;
			//�摜���ړ�
			eyeAbove.MoveImage(0, -(GAME_HEIGHT / eyeInOutCntMax));
			eyeBelow.MoveImage(0, GAME_HEIGHT / eyeInOutCntMax);
		}
		else
		{
			isEyeIn = FALSE;
		}
	}

	//�A�C�A�E�g
	if (isEyeOut)
	{
		if (eyeInOutCnt < eyeInOutCntMax)
		{
			eyeInOutCnt++;
			//�摜���ړ�
			eyeAbove.MoveImage(0, GAME_HEIGHT / eyeInOutCntMax);
			eyeBelow.MoveImage(0, -(GAME_HEIGHT / eyeInOutCntMax));
		}
		else
		{
			isEyeOut = FALSE;
			isEyeIn = TRUE;
		}
	}

	//�؂�ւ����I��
	if (!isEyeOut && !isEyeIn)
	{
		//���̃Q�[���V�[���ɉ�����������
		switch (NextGameScreen)
		{
		case GAME_SCREEN::TITLE://�^�C�g�����
			//GameInit_Title();
			break;
		default:
			break;
		}

		OldGameScreen = GameScreen;  //�ȑO�̃Q�[���V�[�����X�V
		GameScreen = NextGameScreen; //���̃Q�[���V�[���ɐ؂�ւ�
		NextGameScreen = GAME_SCREEN::CHANGE; //�؂�ւ���ʂ�}��
	}

	return;
}

/// <summary>
/// �؂�ւ���ʂ̕`��
/// </summary>
VOID ChangeDraw()
{
	//�ȑO�̃V�[����`��
	if (isEyeOut)
	{
		switch (OldGameScreen)
		{
		case GAME_SCREEN::TITLE://�^�C�g�����
			Title_Draw();
			break;
		default:
			break;
		}
	}
	else if (isEyeIn)
	{
		switch (NextGameScreen)
		{
		case GAME_SCREEN::TITLE://�^�C�g�����
			Title_Draw();
			break;
		default:
			break;
		}
	}

	//�A�C�C���E�A�E�g
	eyeAbove.DrawImage();
	eyeBelow.DrawImage();

	return;
}

/// <summary>
/// ��ʂ̐؂�ւ�
/// </summary>
/// <param name="gameScreen">�؂�ւ���̃Q�[���V�[��</param>
VOID ChangeScreen(GAME_SCREEN gameScreen)
{
	OldGameScreen = GameScreen;
	GameScreen = NextGameScreen;
	NextGameScreen = gameScreen;
	isEyeOut = TRUE;
}