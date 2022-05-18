#pragma once
#include "main.h"
#include "font.h"		//フォント使用目的
#include "keyboard.h"	//キー入力目的

//シーンに関する関数が入っています

extern VOID Title(VOID);		//タイトル画面
extern VOID TitleProc(VOID);	//タイトル画面(処理)
extern VOID TitleDraw(VOID);	//タイトル画面(描画)

extern VOID ChangeScreen(GAME_SCREEN gameScreen); //シーンを切り替える