#pragma once
#include "main.h"

//===================================================================
// �}�N����`
//===================================================================

//�p�X�Ɩ��O
#define FONT_WORK_PATH	TEXT(".\\font\\work.ttf")
#define FONT_WORK_NAME	TEXT("�d����������")

//MS �S�V�b�N
#define FONT_MSGOTH_NAME	TEXT("MS �S�V�b�N")

//�f�t�H���g�̃t�H���g�ݒ�
#define DEF_FONT_NAME	FONT_WORK_NAME
#define DEF_FONT_SIZE	24
#define DEF_FONT_THINCK	1
#define DEF_FONT_TYPE	DX_FONTTYPE_ANTIALIASING

//�G���[���b�Z�[�W
#define FONT_INSTALL_ERR_TITLE  TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE   TEXT("�t�H���g�쐬�G���[")

//===================================================================
// �t�H���g�N���X
//===================================================================

/// <summary>
/// �t�H���g�̃N���X
/// </summary>
class FONT
{
private:
	int handle;			//�n���h��
	int size;			//�T�C�Y
	int thinck;			//����
	int type;			//�^�C�v
	char name[STR_MAX];	//���O
public:
	FONT(const char* fname = "\0", int fsize = 0, int fthinck = 0, int ftype = 0);
	BOOL FontCreateHandle(VOID);	//�t�H���g�n���h�����쐬
	VOID SetDefaultFont(VOID);		//�t�H���g��S�̂ɔ��f������
	INT GetHandle(VOID);			//�n���h���̒l���擾
	~FONT();
};

//===================================================================
// �O���̃O���[�o���ϐ�
//===================================================================

extern FONT fontDef;		//�f�t�H���g�̃t�H���g
extern FONT fontDef_h1ver;	//�f�t�H���g�̃t�H���g h1��
extern FONT fontDef_h2ver;	//�f�t�H���g�̃t�H���g h2��
extern FONT fontDef_h3ver;	//�f�t�H���g�̃t�H���g h3��
extern FONT fontDef_h4ver;	//�f�t�H���g�̃t�H���g h4��

/*
h1 48-72
h2 36-60
h3 24-48
h4 16-36
p  8 -24�i�f�t�H���g�j
*/

//===================================================================
//�v���g�^�C�v�錾
//===================================================================

extern BOOL FontAdd(VOID);		//�t�H���g�̓ǂݍ���
extern VOID FontRemove(VOID);	//�t�H���g�̍폜