#pragma once
#include "main.h"

//===================================================================
// マクロ定義
//===================================================================

//キーの種類
#define KEY_KIND_MAX	256

//===================================================================
// キーボードクラス
//===================================================================

class KEYBOARD
{
private:
	char tempKeyState[KEY_KIND_MAX];	//入力状態を管理
	int allKeyState[KEY_KIND_MAX];		//全てのキーの入力時間を管理
	int oldAllKeyState[KEY_KIND_MAX];	//以前の全てのキーの入力時間を管理
public:
	KEYBOARD();
	VOID AllKeyUpdate(VOID);						//キーの入力状態を更新
	BOOL KeyDown(int KEY_INPUT_);					//キーコードでキーの入力を判断
	BOOL KeyUp(int KEY_INPUT_);						//キーコードでキーの押し上げを判断
	BOOL KeyClick(int KEY_INPUT_);					//キーコードでキーのクリックを判断
	BOOL KeyDownKeep(int KEY_INPUT_, int millTime);	//キーコードでキーの継続入力を判断
};

//=========================================================
// 変数の外部宣言
//=========================================================

//キーボードの管理
extern KEYBOARD keyboard;