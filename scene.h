#pragma once
#include "main.h"
#include "font.h"		//フォント使用目的
#include "keyboard.h"	//キー入力目的

//シーンに関する関数が入っています

//シーンの読み込み
BOOL GameLoad_Title(VOID);		//タイトルシーン読み込み
BOOL GameLoad_TrunblePlay(VOID);		//Trunbleプレイシーン読み込み

//シーンの初期化
VOID GameInit_Title(VOID);		//タイトルシーン初期化
VOID GameInit_TrunblePlay(VOID);		//Trunbleプレイシーン初期化

//シーンの削除
VOID GameDelete_Title(VOID);	//タイトルシーン削除
VOID GameDelete_TrunblePlay(VOID);	//Trunbleプレイシーン削除


extern VOID Title(VOID);		//タイトル画面
extern VOID Title_Proc(VOID);	//タイトル画面(処理)
extern VOID Title_Draw(VOID);	//タイトル画面(描画)

extern VOID Trunble_Play(VOID);		//Trunbleのプレイ画面
extern VOID Trunble_PlayProc(VOID);	//Trunbleのプレイ画面(処理)
extern VOID Trunble_PlayDraw(VOID);	//Trunbleのプレイ画面(描画)

extern VOID Hikkaduwa_Play(VOID);		//Hikkaduwaのプレイ画面
extern VOID Hikkaduwa_PlayProc(VOID);	//Hikkaduwaのプレイ画面(処理)
extern VOID Hikkaduwa_PlayDraw(VOID);	//Hikkaduwaのプレイ画面(描画)

extern VOID ChangeScreen(GAME_SCREEN gameScreen); //シーンを切り替える