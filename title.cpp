#include "scene.h"

//FPS
const int fadeTimeMill = 3000;						//切り替えミリ秒
const int fadeTimeMax = fadeTimeMill / 1000 * 60;	//ミリ秒をフレーム秒に変換

//フェードアウト
const int fadeOutInCntInit = 0;				//初期値
int fadeOutInCnt = fadeOutInCntInit;		//フェードアウトのカウンタ
const int fadeOutInCntMax = fadeTimeMax;	//フェードアウトのカウンタMAX

BOOL isTitleEyeIn = FALSE;

const int titleEyeTimeMilli = 500; //切り替えにかける時間(ミリ秒)
const int titleEyeTimeMax = titleEyeTimeMilli * 60 / 1000;

//アイイン
const int titleEyeInCntInit = 0;
int titleEyeInCnt = titleEyeInCntInit;
const int titleEyeInCntMax = titleEyeTimeMax;

//===タイトルの処理で使用===


//===ファイル素材（クラス）===

SOUND TitleBGM;					//タイトルのBGM
IMAGE TitleIMAGE;				//タイトルの背景
IMAGE HikkaduwaPresenIMAGE[2];	//ヒッカドゥアのプレイ説明の画像を入れた配列
IMAGE TrublePresenIMAGE[2];	//ヒッカドゥアのプレイ説明の画像を入れた配列


//タイトル素材ロード
BOOL GameLoad_Title()
{
	//if (TitleBGM.LordSound(".\\audio\\title\\harpohikunezumi.mp3", 100, PLAYTYPE::BGM) == FALSE) return FALSE;

	return TRUE;
}

//タイトル初期化
VOID GameInit_Title()
{
	//フェードアウト
	fadeOutInCnt = fadeOutInCntInit;		//フェードアウトのカウンタ
	isTitleEyeIn = FALSE;
	//アイイン
	titleEyeInCnt = titleEyeInCntInit;
}

//タイトル削除
VOID GameDelete_Title(VOID)
{
	TitleBGM.~SOUND();
}

VOID Title()
{
	Title_Proc();
	Title_Draw();

	return;
}

//タイトル処理
VOID Title_Proc()
{

	return;
}

//タイトル描画
VOID Title_Draw()
{

	return;
}