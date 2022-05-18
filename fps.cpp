#include "fps.h"
//FPS�Ɋւ���֐��������Ă��܂�

//=========================================================
//  �O���[�o���ϐ�
//=========================================================

//fps�̊Ǘ�
FPS fps;

//=========================================================
//  �N���X�֐�
//=========================================================

/// <summary>
/// FPS�l�̌v���A�l�̍X�V
/// </summary>
/// <param name=""></param>
VOID FPS::FPSUpdate(VOID)
{
	//��ԍŏ��̏���
	if (!fps.isInitFlg)
	{
		//����J�n�������}�C�N���b�P�ʂŎ擾
		fps.startTime = GetNowHiPerformanceCount();	//Windows���N�����Ă���o�߂�������(�}�C�N���b)
	}

	//���݂̎������}�C�N���b�P�ʂŎ擾
	fps.nowTime = GetNowHiPerformanceCount();

	//��ԍŏ�����
	if (!fps.isInitFlg) { fps.oldTime = fps.nowTime; }	//�ȑO�̎��� = ���݂̎���

	//�O��擾�������Ԃ���̌o�ߎ��Ԃ�b(����)�ɕϊ����Ă���Z�b�g
	fps.deltaTime = (fps.nowTime - fps.oldTime) / 1000000.0f;

	//����擾�������Ԃ�ۑ�
	fps.oldTime = fps.nowTime;

	//��ԍŏ������t���OON
	if (!fps.isInitFlg) { fps.isInitFlg = TRUE; }

	//�P�t���[���ځ`FPS�ݒ�l�܂ł́A�J�E���g�A�b�v
	if (fps.count < fps.sampleRate)
	{
		//�J�E���^�𑝂₷
		fps.count++;
	}
	else
	{
		//FPS�ݒ�l�̃t���[���ŁA����FPS���v�Z

		//���݂̎�������A0�t���[���ڂ̎��Ԃ������AFPS�̐��l�Ŋ���
		//���݂̕���FPS�l���o��
		fps.drawValue = 1000000.f / ((fps.nowTime - fps.startTime) / (float)fps.sampleRate);

		//����J�n�������}�C�N���b�P�ʂŎ擾
		fps.startTime = GetNowHiPerformanceCount();	//Windows���N�����Ă���o�߂�������(�}�C�N���b)

		//�J�E���^������
		fps.count = 1;
	}

	//�Q�[�������ԃJ�E���g�A�b�v
	fps.gameTime += fps.deltaTime;

	//���ݓ��t�������擾
	GetDateTime(&fps.nowDataTime);

	return;
}

/// <summary>
/// ����FPS�l�̕`��
/// </summary>
/// <param name=""></param>
VOID FPS::FPSDraw(VOID)
{
	//������̕`��
	if (GAME_DEBUG) DrawFormatString(0, 0, GetColor(0, 0, 0), "FPS:%.1f", fps.drawValue);

	return;
}

/// <summary>
/// FPS�ŏ�����҂�
/// </summary>
/// <param name=""></param>
VOID FPS::FPSWait(VOID)
{
	//���݂̎���-�ŏ��̎����ŁA���݂������Ă��鎞�����擾����
	LONGLONG resultTime = fps.nowTime - fps.startTime;

	//�҂ׂ��~���b���@(1�b/FPS�l * ���݂̃t���[����)����A���݂������Ă��鎞��������
	int waitTime = (int)(1000000.0f / fps.value * fps.count - resultTime);

	//�}�C�N���b����~���b�ɕϊ�
	waitTime /= 1000;

	//����������������A������҂�
	if (waitTime > 0)
	{
		WaitTimer(waitTime);	//�����~���b�҂�
	}

	//����������OFF�ɂ��Ă��邩�H
	if (!GetWaitVSyncFlag())
	{
		//FPS�ő�l�ł͂Ȃ��Ƃ�
		if (fps.value < GAME_FPS_MAX)
		{
			//�P�b����FPS�l�����A�҂��Ԃ��������Ƃ��́A������FPS�l���グ�Ă��ǂ�
			//�҂��� 10�~���@<= 1�b/60FPS = 16.6666�~���@�������������ł���
			if (waitTime > 0
				&& waitTime <= 1000.0f / fps.value)
			{
				//fps.Count++;
				fps.value++;
			}
			else
			{
				//FPS�l���ǂ����Ă��炸�A�x���Ƃ��́AFPS�l��������
				if (fps.value > GAME_FPS_MIN)
				{
					fps.value--;
				}
			}
		}
	}

	return;
}

/// <summary>
/// �Q�[�������Ԃ̃��Z�b�g
/// </summary>
/// <param name=""></param>
VOID FPS::ReseGameTime(VOID)
{
	fps.gameTime = 0;
	return;
}

/// <summary>
/// �Q�[�������Ԃ��擾
/// </summary>
/// <param name=""></param>
/// <returns>�Q�[��������(�����^)</returns>
float FPS::GetGameTime(VOID)
{
	return fps.gameTime;
}