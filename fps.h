#pragma once
#include "main.h"

//===================================================================
// �}�N����`
//===================================================================

#define GAME_FPS		60	//FPS�W��
#define GAME_FPS_MAX	240	//FPS�ő�
#define GAME_FPS_MIN	60	//FPS�ŏ�

//===================================================================
// FPS�N���X
//===================================================================

/// <summary>
/// FPS�N���X
/// </summary>
class FPS
{
private:
	BOOL isInitFlg;			//�ŏ��̑���J�n�t���O
	LONGLONG startTime;		//����J�n����
	LONGLONG nowTime;		//���݂̎���
	LONGLONG oldTime;		//�ȑO�̎���
	int value;				//FPS�̒l
	float deltaTime;		//0��5�� �o�ߎ���
	int count;				//���݂̃t���[����
	float drawValue;		//�v�Z���ʂ�`��
	int sampleRate;			//���ς����T���v���l
	float gameTime;			//�Q�[��������
	DATEDATA nowDataTime;	//���݂̓��t����
public:
	FPS() :isInitFlg(FALSE), startTime(0), nowTime(0), oldTime(0),
		value(GAME_FPS), deltaTime(0.000001f), count(1), drawValue(0.0f),
		sampleRate(GAME_FPS), gameTime(0.0f) {
		nowDataTime.Day = 0;
		nowDataTime.Hour = 0;
		nowDataTime.Min = 0;
		nowDataTime.Mon = 0;
		nowDataTime.Sec = 0;
		nowDataTime.Year = 0;
	};
	VOID FPSUpdate(VOID);
	VOID FPSDraw(VOID);
	VOID FPSWait(VOID);
	VOID ReseGameTime(VOID);
	float GetGameTime(VOID);
	~FPS() {};
};

//===================================================================
// �ϐ��̊O���錾
//===================================================================

//fps�̊Ǘ�
extern FPS fps;