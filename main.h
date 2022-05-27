#pragma once
#include "DxLib.h"
#include <iostream>
#include <vector>
#include <math.h>	//���w�n
#include <string.h>	//������n
#include <time.h>	//���Ԍn

using namespace std;

//�Q�[���̊�b�I�ȃf�[�^�������Ă��܂�

//=========================================================
// �}�N����`
//=========================================================

//�Q�[���ݒ�

#define GAME_TITLE "Hung Out"			//�Q�[���^�C�g��
#define GAME_WIDTH	1280				//�Q�[����ʂ̕�
#define GAME_HEIGHT	720					//�Q�[����ʂ̍���
#define GAME_COLOR  32					//�Q�[���̐F��

#define GAME_ICON_ID	333				//�Q�[����ICON��ID

#define GAME_WINDOW_BAR	0				//�E�B���h�E�o�[�̎��

#define GAME_DEBUG	TRUE				//�f�o�b�O���[�h

#define PATH_MAX	255					//�p�X�̒���
#define STR_MAX		255					//�����̒���
#define IMGDIV_MAX	128					//�n���h���̍ő吔(�C��)

//�^�C�g����ʂŎg������
#define HikkaduwaPresen_SIZE	2		//�v���C�����摜����ꂽ�z��̗v�f����(�q�b�J�h�D�A)
#define TruNblePresen_SIZE	2			//�v���C�����摜����ꂽ�z��̗v�f����(�^���u�[��)

//=========================================================
// �񋓌^�iC+�{ver�j
//=========================================================

//�Q�[���V�[��
enum class GAME_SCREEN : int
{
	DREAM1,
	DREAM2,
	DREAM3,
	DREAM4,
	DREAM5,
	DREAM6,
	TITLE,
	DAYTIME,
	RECORD,
	CHANGE
};

enum class PLAYTYPE : int
{
	NONE,
	//���y
	BGM = DX_PLAYTYPE_LOOP,	//���[�v����
	SE = DX_PLAYTYPE_BACK,	//���[�v�����Ȃ�
	//����
	LOOP,					//���[�v����
	NOMAL					//���[�v�����Ȃ�

};


//�L�����̌���
enum class CHARA_DIR : int
{
	NONE,
	ABOVE,
	ABOVE_RIGHT,
	ABOVE_LEFT,
	RIGHT,
	LEFT,
	BELOW,
	BELOW_RIGHT,
	BELOW_LEFT
};

//�l�̎��
enum class VALUE : int
{
	X,
	Y,
	WIDTH,
	HEIGHT,
	ISDRAW
};

//=========================================================
// �N���X
//=========================================================

//�p���̊֌W
//
//  ���`(�p�X�ƃn���h�������������Ă���)
//  ������������
//  ���y      �摜�֌W�̐��`
//            ����������
//           �摜    ����
//            ��
//          �A���摜

//���`
class TEMPLATE
{
public:
	int handle;			//�n���h���i�Ǘ��ԍ��j
	char path[PATH_MAX];//�p�X�@�@�i�ꏊ�j

	TEMPLATE(const char* path = "\0");
	virtual ~TEMPLATE() {};
};

//���y
class SOUND : public TEMPLATE
{
private:
	int volume;
	PLAYTYPE playtype;
public:
	SOUND(int v = 0, int pt = (int)PLAYTYPE::NONE) :volume(v), playtype((PLAYTYPE)pt) {};
	BOOL LordSound(const char* pathCopy, int volumeCopy, PLAYTYPE playTipeCopy); //���y�t�@�C���̓ǂݍ���
	VOID MyPlaySound(VOID);				//���y�̍Đ�
	VOID ChangeSoundVolume(int vCopy);	//���ʂ̕ύX
	VOID MyStopSound(VOID);				//���y�̒�~
	~SOUND();							//�R�R�ŉ��y�t�@�C���̍폜
};

//����
class MOVIE : public TEMPLATE
{
private:
	int volume;
	PLAYTYPE playtype;
public:
	MOVIE(int v = 0, int pt = (int)PLAYTYPE::NONE) :volume(v), playtype((PLAYTYPE)pt) {};
	BOOL LoadMOVIE(const char* pathCopy, int volumeCopy, PLAYTYPE playTipeCopy); //����t�@�C���̓ǂݍ���
	VOID MyPlayMOVIE(VOID);				//����̍Đ�
	VOID ChangeMOVIEVolume(int vCopy);	//����̕ύX
	VOID MyStopMOVIE(VOID);				//����̒�~
	~MOVIE();							//�R�R�œ���t�@�C���̍폜
};

//�摜�֌W�̐��`
class TEMPLATE_IMAGE : public TEMPLATE
{
protected:
	int x;
	int y;
	int width;
	int height;
public:
	TEMPLATE_IMAGE(int xCopy = 0, int yCopy = 0, int widthCopy = 0, int heightCopy = 0);
};

//�摜
class IMAGE : public TEMPLATE_IMAGE
{
protected:
	RECT collision;
	BOOL isDraw;
public:
	IMAGE();
	virtual BOOL LoadImageMem(const char* pathCopy = "\0");//�摜�̓ǂݍ���
	VOID CollisionUpdate(VOID);			//�����蔻��̍X�V
	virtual VOID DrawImage(VOID);		//�摜�̕`��
	VOID SetImage(int xS, int yS);		//�摜�̈ʒu����
	VOID SetImageOnCollision(RECT xColl);//�����̓����蔻�����ɉ摜�̈ʒu����
	VOID MoveImage(int xM, int yM);		//�摜�̈ړ�
	INT GetValue(VALUE valueK);			//�N���X�̒l���擾
	RECT GetColl(VOID);					//�N���X�̓����蔻����擾
	VOID SetActiveImage(BOOL Active);	//�摜�̕\���E��\��
	~IMAGE();							//�R�R�ō폜

	//�R�s�[�R���X�g���N�^
	IMAGE(const IMAGE& Cimage)
	{
		handle = Cimage.handle;
		strcpy_s(path, PATH_MAX, Cimage.path);
		x = Cimage.x;
		y = Cimage.y;
		width = Cimage.width;
		height = Cimage.height;
		collision = Cimage.collision;
		isDraw = Cimage.isDraw;
	}
	//������Z�q�̃I�[�o�[���[�h
	virtual IMAGE& operator= (const IMAGE& Cimage)
	{
		handle = Cimage.handle;
		strcpy_s(path, PATH_MAX, Cimage.path);
		x = Cimage.x;
		y = Cimage.y;
		width = Cimage.width;
		height = Cimage.height;
		collision = Cimage.collision;
		isDraw = Cimage.isDraw;
		return *this;
	}
};

//�A���摜
class DIVIMAGE : public IMAGE
{
private:
	int divNum;					//������
	int divHandle[IMGDIV_MAX] = { 0 };//�摜�̃n���h��
	int nowIndex;				//���݂̃n���h���z��̗v�f�ԍ�

	int divSide;		//���̕�����
	int divVertical;	//�c�̕�����

	int animCnt;		//�A�j���[�V�����J�E���^
	int animCntMax;		//�A�j���[�V�����J�E���^(�ő�)
	BOOL IsAnimLoop;	//���[�v�̗L��
public:
	DIVIMAGE(int divsideCopy = 0,
		int divverticalCopy = 0,
		int animcntCopy = 0,
		BOOL isanimloopCopy = FALSE) :
		divSide(divsideCopy), divVertical(divverticalCopy),
		animCntMax(animcntCopy), IsAnimLoop(isanimloopCopy),
		divNum(0), nowIndex(0), animCnt(0) {};
	BOOL LoadImageMem(const char* pathCopy, int divSideCopy, int divVerticalCopy, float animCntCopy);
	VOID DrawImage(VOID);
	~DIVIMAGE();
};