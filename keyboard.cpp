#include "keyboard.h"
//キーボードに関する関数が入っています

//=========================================================
//  グローバル変数
//=========================================================

KEYBOARD keyboard;


//=========================================================
//  クラス関数
//=========================================================

KEYBOARD::KEYBOARD()
{
	for (int i = 0; i < KEY_KIND_MAX; ++i) tempKeyState[i] = '\0';
	for (int i = 0; i < KEY_KIND_MAX; ++i) allKeyState[i] = NULL;
	for (int i = 0; i < KEY_KIND_MAX; ++i) oldAllKeyState[i] = NULL;
}

/// <summary>
/// キーの入力状態を更新
/// </summary>
/// <param name=""></param>
VOID KEYBOARD::AllKeyUpdate(VOID)
{
	//直前のキー入力をとっておく
	for (int i = 0; i < KEY_KIND_MAX; ++i)
	{
		oldAllKeyState[i] = allKeyState[i];
	}

	//すべてのキーの入力状態を得る
	GetHitKeyStateAll(tempKeyState);

	//押されているキーの時間を更新する
	for (int i = 0; i < KEY_KIND_MAX; ++i)
	{
		//キーコードを押しているとき
		if (tempKeyState[i] != 0)
		{
			++allKeyState[i];	//押している時間を加算
		}
		else
		{
			allKeyState[i] = 0;	//押している時間を0に戻す
		}
	}

	return;
}

/// <summary>
/// キーコードでキーの入力を判断
/// </summary>
/// <param name="KEY_INPUT_">キーコード</param>
/// <returns></returns>
BOOL KEYBOARD::KeyDown(int KEY_INPUT_)
{
	if (allKeyState[KEY_INPUT_] != 0)	return TRUE;
	else								return FALSE;
}

/// <summary>
/// キーコードでキーの押し上げを判断
/// </summary>
/// <param name="KEY_INPUT_">キーコード</param>
/// <returns></returns>
BOOL KEYBOARD::KeyUp(int KEY_INPUT_)
{
	if (
		oldAllKeyState[KEY_INPUT_] != 0	//以前は押していた
		&& allKeyState[KEY_INPUT_] == 0	//現在は押していない
		)
	{
		 return TRUE;
	}
	else return FALSE;
}

/// <summary>
/// キーコードでキーのクリックを判断
/// </summary>
/// <param name="KEY_INPUT_">キーコード</param>
/// <returns></returns>
BOOL KEYBOARD::KeyClick(int KEY_INPUT_)
{
	if (
		oldAllKeyState[KEY_INPUT_] != 0	//以前は押していた
		&& allKeyState[KEY_INPUT_] == 0	//現在は押していない
		)
	{
		 return TRUE;
	}
	else return FALSE;
}

/// <summary>
/// キーコードでキーの継続入力を判断
/// </summary>
/// <param name="KEY_INPUT_">キーコード</param>
/// <param name="millSec">ミリ秒</param>
/// <returns></returns>
BOOL KEYBOARD::KeyDownKeep(int KEY_INPUT_, int millTime)
{
	//１秒は1000ミリ秒
	float MilliSec = 1000.0f;

	//押し続けている時間は、ミリ秒数×FPS値
	//例）1500ミリ秒押す/1000ミリ　→　1.5秒×60FPS = 90
	int UpdateTime = (millTime / (int)MilliSec) * 60;

	if (allKeyState[KEY_INPUT_] > UpdateTime)	return TRUE;	//押し続けている
	else										return FALSE;	//押し続けていない
}