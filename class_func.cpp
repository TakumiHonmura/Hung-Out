#include "main.h"
#include "fps.h"

//�N���X���̊֐�����

//=========================================================
//  ���`
//=========================================================

TEMPLATE::TEMPLATE(const char* pathCopy)
{
	handle = -1;
	strcpyDx(path, pathCopy);
}


//=========================================================
//  �摜�̐��`
//=========================================================

TEMPLATE_IMAGE::TEMPLATE_IMAGE(int xCopy, int yCopy, int widthCopy, int heightCopy)
{
	x = xCopy;
	y = yCopy;

	width = widthCopy;
	height = heightCopy;
}


//=========================================================
//  �摜
//=========================================================

IMAGE::IMAGE()
{
	isDraw = FALSE;
	CollisionUpdate();
}

/// <summary>
/// �摜�̓ǂݍ���
/// </summary>
/// <param name="pathCopy">�摜�̃p�X</param>
/// <returns>�ǂݍ��߂��ETRUE�b�G���[�EFALSE</returns>
BOOL IMAGE::LoadImageMem(const char* pathCopy)
{
	//�摜�̓ǂݍ���
	strcpyDx(path, pathCopy);		//�p�X�̃R�s�[
	handle = LoadGraph(&path[0]);	//�摜�̓ǂݍ���

	//�ǂݍ��߂Ȃ�������G���[�\��
	if (handle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//���C���̃E�B���h�E�n���h��
			path,					//���b�Z�[�W�{��
			"�摜�ǂݍ��݃G���[",	//���b�Z�[�W�^�C�g��
			MB_OK					//�{�^��
		);
		return FALSE;	//�ǂݍ��ݎ��s
	}

	//�摜�̕��ƍ������擾
	GetGraphSize(handle, &width, &height);

	//�摜�̈ʒu��������
	x = 0; y = 0;

	//�����蔻��̍X�V
	CollisionUpdate();

	//�摜��`�悷��
	isDraw = TRUE;

	return TRUE;
}

/// <summary>
/// �����蔻��̍X�V
/// </summary>
VOID IMAGE::CollisionUpdate(VOID)
{
	collision.left   = x;
	collision.top    = y;
	collision.right  = x + width;
	collision.bottom = y + height;

	return;
}

/// <summary>
/// �摜�̕`��
/// </summary>
VOID IMAGE::DrawImage(VOID)
{
	//�`��ł���Ȃ�`��
	if (isDraw) DrawGraph(x, y, handle, TRUE);

	//�f�o�b�O���[�h�œ����蔻���\��
	if (GAME_DEBUG) DrawBox(collision.left, collision.top, collision.right, collision.bottom, GetColor(255, 255, 255), FALSE);

	return;
}

/// <summary>
/// �摜�̈ʒu����
/// </summary>
/// <param name="xS">X���W�̈ʒu</param>
/// <param name="yS">Y���W�̈ʒu</param>
VOID IMAGE::SetImage(int xS, int yS)
{
	x = xS;
	y = yS;

	CollisionUpdate();

	return;
}

/// <summary>
/// �����̓����蔻�����ɉ摜�̈ʒu����
/// </summary>
/// <param name="xColl"></param>
VOID IMAGE::SetImageOnCollision(RECT xColl)
{
	x = xColl.left;
	y = xColl.top;

	CollisionUpdate();

	return;
}

/// <summary>
/// �摜�̈ړ�
/// </summary>
/// <param name="xM">X���W�̈ړ�����</param>
/// <param name="yM">Y���W�̈ړ�����</param>
VOID IMAGE::MoveImage(int xM, int yM)
{
	x += xM;
	y += yM;

	CollisionUpdate();

	return;
}

/// <summary>
/// �N���X�̒l���擾
/// </summary>
/// <returns>�����ɉ������l/�ǂ�ɂ����Ă͂܂炢����-1</returns>
INT IMAGE::GetValue(VALUE valueK)
{
	switch (valueK)
	{
	case VALUE::X:
		return x;
		break;
	case VALUE::Y:
		return y;
		break;
	case VALUE::WIDTH:
		return width;
		break;
	case VALUE::HEIGHT:
		return height;
		break;
	case VALUE::ISDRAW:
		if (isDraw) return TRUE;
		else return FALSE;
	default:
		return -1;
		break;
	}
}

/// <summary>
/// �摜�̓����蔻����擾
/// </summary>
/// <param name="">RECT�\����</param>
/// <returns></returns>
RECT IMAGE::GetColl(VOID)
{
	return collision;
}

/// <summary>
/// �摜�̕\���E��\����ݒ�
/// </summary>
/// <param name="Active">�ݒ肵�����\�����</param>
VOID IMAGE::SetActiveImage(BOOL Active)
{
	isDraw = Active;

	return;
}

IMAGE::~IMAGE()
{
	//�摜�n���h�������
	DeleteGraph(handle);
}


//=========================================================
//  �����摜
//=========================================================

/// <summary>
/// �摜�𕪊����ă������ɓǂݍ���
/// </summary>
/// <param name="pathCopy">�摜�̃p�X</param>
/// <param name="divSideCopy">���̕�����</param>
/// <param name="divVerticalCopy">�c�̕�����</param>
/// <param name="animCnt">�摜�؂�ւ��̕b��(s)</param>
/// <returns></returns>
BOOL DIVIMAGE::LoadImageMem(const char* pathCopy, int divSideCopy, int divVerticalCopy, float animCntCopy)
{
	//�摜�ǂݍ��݂̃t���O
	int isLoad = -1;

	//�ꎞ�I�ɉ摜�̃n���h����p�ӂ���
	int tempHandle = LoadGraph(pathCopy);

	//�ǂݍ��݃G���[����
	if (tempHandle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//���C���̃E�B���h�E�n���h��
			pathCopy,					//���b�Z�[�W�{��
			"�摜�ǂݍ��݃G���[",	//���b�Z�[�W�^�C�g��
			MB_OK					//�{�^��
		);
		return FALSE;
	}

	//�摜�̕��ƍ������擾
	int width2 = -1;
	int height2 = -1;
	GetGraphSize(tempHandle, &width2, &height2);

	isLoad = LoadDivGraph(
		pathCopy,										//�摜�̃p�X
		divSideCopy * divVerticalCopy,					//��������
		divSideCopy, divVerticalCopy,					//���Əc�̕���
		width2 / divSideCopy, height2 / divVerticalCopy,	//�摜����̕��ƍ���
		&divHandle[0]									//�A���ŊǗ�����z��̐擪�A�h���X
	);

	//�����G���[
	if (isLoad == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//���C���̃E�B���h�E�n���h��
			pathCopy,				//���b�Z�[�W�{��
			"�摜�����G���[",		//���b�Z�[�W�^�C�g��
			MB_OK					//�{�^��
		);
		return FALSE;
	}

	//����ݒ�
	divSide = divSideCopy;
	divVertical = divVerticalCopy;
	divNum = divSide * divVertical;
	x = 0;
	y = 0;
	GetGraphSize(divHandle[0], &width, &height);
	animCnt = 0;
	animCntMax = (int)(animCntCopy * GAME_FPS);
	IsAnimLoop = FALSE;
	nowIndex = 0;

	//�����蔻��̍X�V
	CollisionUpdate();

	//�摜�͕`�悷��
	isDraw = FALSE;

	//�ꎞ�I�ɓǂݍ��񂾃n���h�������
	DeleteGraph(tempHandle);

	return TRUE;
}

/// <summary>
/// �����摜�̕`��
/// </summary>
/// <param name=""></param>
VOID DIVIMAGE::DrawImage(VOID)
{
	//�摜���`��o���鎞�����`��
	if (isDraw)
	{
		DrawGraph(x, y, divHandle[nowIndex], TRUE);

		//�A�j���[�V�����̃J�E���g�A�b�v
		if (animCnt < animCntMax) { ++animCnt; }
		else
		{
			//�S�ẴA�j���[�V������`�悵�I������
			if (nowIndex == divNum - 1)
			{
				//�A�j���[�V�������J��Ԃ��Ȃ��Ȃ�`����~�߂�
				if (!IsAnimLoop) isDraw = FALSE;
				animCnt = 0;
				nowIndex = 0;
			}
			else if (nowIndex < divNum - 1)
			{//���̉摜������Ȃ玟��
				++nowIndex;
			}

			//�J�E���^���N���A
			animCnt = 0;
		}
	}

	//�f�o�b�O���[�h�̎��͓����蔻���`��
	if (GAME_DEBUG) DrawBox(collision.left, collision.top, collision.right, collision.bottom, GetColor(255, 255, 255), FALSE);

	return;
}

DIVIMAGE::~DIVIMAGE()
{
	//�摜�n���h�������
	for (int i = 0; i < divNum; i++) DeleteGraph(divHandle[i]);
}

//=========================================================
//  ���y
//=========================================================

/// <summary>
/// ���y�t�@�C���̓ǂݍ���
/// </summary>
/// <param name="pathCopy">���y�t�@�C���̃p�X</param>
/// <param name="volumeCopy">����</param>
/// <param name="playTipeCopy">�v���C�^�C�v(�P��or���[�v)</param>
/// <returns>�����FTRUE�b���s�FFALSE</returns>
BOOL SOUND::LordSound(const char* pathCopy, int volumeCopy, PLAYTYPE playTipeCopy)
{
	//���y�̓ǂݍ���
	strcpyDx(path, pathCopy);		//�p�X�̃R�s�[
	handle = LoadSoundMem(path);	//���y�̓ǂݍ���

	//���y���ǂݍ��߂Ȃ������Ƃ��́A�G���[(-1)������
	if (handle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//���C���̃E�B���h�E�n���h��
			path,					//���b�Z�[�W�{��
			"���y�ǂݍ��݃G���[�I",	//���b�Z�[�W�^�C�g��
			MB_OK					//�{�^��
		);

		return FALSE;	//�ǂݍ��ݎ��s
	}

	//���̑��̐ݒ�
	volume = volumeCopy;
	playtype = playTipeCopy;

	return TRUE;
}

/// <summary>
/// ���y�̍Đ�
/// </summary>
/// <param name=""></param>
VOID SOUND::MyPlaySound(VOID)
{
	//���[�v�Đ��łȂ���΁A���̂܂܍Đ�����
	if (playtype == PLAYTYPE::SE)
	{
		PlaySoundMem(handle, (int)playtype);//���y�̍Đ�
	}
	//���[�v�Đ��̂Ƃ��́A���y���Đ�����Ă��Ȃ���΁A�Đ�����
	else if (playtype == PLAYTYPE::BGM)
	{
		if (CheckSoundMem(handle) == 0)
		{
			PlaySoundMem(handle, (int)playtype);//���y�̍Đ�
		}
	}

	return;
}

/// <summary>
/// ���ʂ̕ύX
/// </summary>
/// <param name="vCopy">�ݒ肵��������(0~255)</param>
VOID SOUND::ChangeSoundVolume(int vCopy)
{
	//���ʕύX
	if (0 <= volume && volume <= 255)
	{
		volume += vCopy;
		ChangeVolumeSoundMem(volume, handle);
	}

	//���ʂ��͈͊O��������͈͓��ɖ߂�
	if (0 > volume)
	{
		volume = 0;
		ChangeVolumeSoundMem(volume, handle);
	}

	if (volume >= 255)
	{
		volume = 255;
		ChangeVolumeSoundMem(volume, handle);
	}

	return;
}

/// <summary>
/// ���y�̒�~
/// </summary>
/// <param name=""></param>
VOID SOUND::MyStopSound(VOID)
{
	StopSoundMem(handle);

	return;
}

SOUND::~SOUND()
{
	//���y�t�@�C���̃n���h�����
	DeleteMusicMem(handle);
}

/*
BOOL LordImageDivMem(const char* path, int divSideCopy, int divVerticalCopy);
VOID DrawImage(VOID);
VOID DrawImageChara(VOID);
~DIVIMAGE();
*/

/*
VOID DeleteSound(SOUND* sound);			//���y�t�@�C���̍폜

TEMPLATE_IMAGE(int x = 0, int y = 0, int width = 0, int height = 0);
*/