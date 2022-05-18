#include "font.h"
//�t�H���g�Ɋւ��ϐ��E�֐��������Ă��܂�

FONT fontDef(DEF_FONT_NAME, DEF_FONT_SIZE, DEF_FONT_THINCK, DEF_FONT_TYPE);	//�f�t�H���g�̃t�H���g
FONT fontDef_h1ver(DEF_FONT_NAME, 72, DEF_FONT_THINCK, DEF_FONT_TYPE);	//�f�t�H���g�̃t�H���g h1��
FONT fontDef_h2ver(DEF_FONT_NAME, 60, DEF_FONT_THINCK, DEF_FONT_TYPE);	//�f�t�H���g�̃t�H���g h2��
FONT fontDef_h3ver(DEF_FONT_NAME, 48, DEF_FONT_THINCK, DEF_FONT_TYPE);	//�f�t�H���g�̃t�H���g h3��
FONT fontDef_h4ver(DEF_FONT_NAME, 36, DEF_FONT_THINCK, DEF_FONT_TYPE);	//�f�t�H���g�̃t�H���g h4��

//�N���X���̊֐�����

//===================================================================
//  �N���X�̊֐��{��
//===================================================================

/// <summary>
/// �t�H���g�N���X�̃R���X�g���N�^
/// </summary>
/// <param name="fname">���O</param>
/// <param name="fsize">�T�C�Y</param>
/// <param name="fthinck">����</param>
/// <param name="ftype">�^�C�v</param>
FONT::FONT(const char* fname, int fsize, int fthinck, int ftype)
{
	//�N���X���̕ϐ����Z�b�g�A�b�v
	strcpy_sDx(name, STR_MAX, fname);	//���O
	size   = fsize;						//�T�C�Y
	thinck = fthinck;					//����
	type = ftype;						//�^�C�v

	//�n���h����������
	handle = -1;
}

/// <summary>
/// �t�H���g�̃n���h�����쐬
/// </summary>
/// <returns>������TRUE�b���s��FALSE</returns>
BOOL FONT::FontCreateHandle(VOID)
{
	handle = CreateFontToHandle(
		name,
		size,
		thinck,
		type
	);

	if (handle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//���C���̃E�B���h�E�n���h��
			name,					//���b�Z�[�W�{��
			FONT_CREATE_ERR_TITLE,	//���b�Z�[�W�^�C�g��
			MB_OK					//�{�^��
		);
		return FALSE;
	}

	return TRUE;
}

/// <summary>
/// �t�H���g��S�̂֔��f
/// </summary>
/// <param name=""></param>
VOID FONT::SetDefaultFont(VOID)
{
	ChangeFont(name);			//���O��ݒ�
	SetFontSize(size);			//�T�C�Y��ݒ�
	SetFontThickness(thinck);	//������ݒ�
	ChangeFontType(type);		//�^�C�v��ݒ�

	return;
}

/// <summary>
/// �t�H���g�N���X�̃n���h�����擾
/// </summary>
/// <param name=""></param>
/// <returns>�n���h���̒l</returns>
INT FONT::GetHandle(VOID)
{
	return handle;
}

FONT::~FONT()
{
	DeleteFontToHandle(handle);
}

//===================================================================
//  ���ʂ̊֐�
//===================================================================

/// <summary>
/// �t�H���g�̓ǂݍ���
/// </summary>
/// <param name=""></param>
/// <returns>������TRUE�b���s��FALSE</returns>
BOOL FontAdd(VOID)
{
	//�t�H���g���ꎞ�I�ɓǂݍ���
	if (!AddFontResourceEx(FONT_WORK_PATH, FR_PRIVATE, NULL))
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), FONT_WORK_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID FontRemove(VOID)
{
	//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜
	RemoveFontResourceEx(FONT_WORK_PATH, FR_PRIVATE, NULL);

	return;
}