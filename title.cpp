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

//===タイトルの処理で使用　（関数）===

//PushEnterを点滅させる時に使う関数
int PushEnterCnt = 0;				//カウンタ
const int PushEnterCntMAX = 100;	//カウンタMAX値
BOOL PushEnterBrink = FALSE;		//点滅しているか？

//===ファイル素材（クラス）===

//動画
MOVIE OpeningMOVIE;				//オープニングムービー

//音楽
SOUND TitleBGM;					//タイトルのBGM

//画像
IMAGE TitleIMAGE;				//タイトルの背景
IMAGE TitleEnterIMAGE;			//PushEnter

IMAGE HikkaduwaPresenIMAGE[HikkaduwaPresen_SIZE];	//ヒッカドゥアのプレイ説明の画像を入れた配列
IMAGE TrublePresenIMAGE[TruNblePresen_SIZE];		//タンブールのプレイ説明の画像を入れた配列

//タイトル素材ロード
BOOL GameLoad_Title()
{
	//画像の読み込み
	if (TitleIMAGE.LoadImageMem(".\\image\\title\\タイトル画面.png") == FALSE) return FALSE;				//タイトル背景画像
	if (TitleEnterIMAGE.LoadImageMem(".\\image\\title\\TitlePushEnter.png") == FALSE) return FALSE;				//タイトル背景画像

	if (HikkaduwaPresenIMAGE[0].LoadImageMem(".\\image\\title\\ヒッカドゥア説明1.png") == FALSE) return FALSE;	//ヒッカドゥアプレイ説明画像①
	if (HikkaduwaPresenIMAGE[1].LoadImageMem(".\\image\\title\\ヒッカドゥア説明2.png") == FALSE) return FALSE;	//ヒッカドゥアプレイ説明画像②
	if (TrublePresenIMAGE[0].LoadImageMem(".\\image\\title\\タンブール説明1.png") == FALSE) return FALSE;		//タンブールプレイ説明画像①
	if (TrublePresenIMAGE[1].LoadImageMem(".\\image\\title\\タンブール説明2.png") == FALSE) return FALSE;		//タンブールプレイ説明画像①

	//音楽の読み込み
	//if (TitleBGM.LordSound(".\\audio\\title\\harpohikunezumi.mp3", 100, PLAYTYPE::BGM) == FALSE) return FALSE;

	//動画の読み込み
	if (OpeningMOVIE.LoadMOVIE(".\\movie\\オープニング.mp4",0,PLAYTYPE::NOMAL) == FALSE) return FALSE;		//オープニングムービー

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

	//画像の位置を設定
	TitleIMAGE.SetImage(0, 0);					//背景画像
	HikkaduwaPresenIMAGE[0].SetImage(0,0);		//ヒッカドゥアの説明画像①
	HikkaduwaPresenIMAGE[1].SetImage(0,0);		//ヒッカドゥアの説明画像②
	TrublePresenIMAGE[0].SetImage(0,0);			//タンブールの説明画像①
	TrublePresenIMAGE[1].SetImage(0,0);			//タンブールの説明画像②
	
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
VOID Title_Proc(){



	return;
}

//タイトル描画
VOID Title_Draw()
{

	//OpeningMOVIE.MyPlayMOVIE();

	//タイトル画面_背景
	TitleIMAGE.DrawImage();

	//PushEnterを点滅させる
	if (PushEnterCnt < PushEnterCntMAX) { PushEnterCnt++; }
	else
	{
		if (PushEnterBrink == TRUE)PushEnterBrink = FALSE;
		else if (PushEnterBrink == FALSE)PushEnterBrink = TRUE;

		PushEnterCnt = 0;	//カウンタを初期化
	}

	if (PushEnterBrink == TRUE)
	{
		//半透明にする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)PushEnterCnt / PushEnterCntMAX) * 255);

		//PushEnterの描画
		TitleEnterIMAGE.DrawImage();

		//半透明終了
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (PushEnterBrink == FALSE)
	{
		//半透明にする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)(PushEnterCntMAX - PushEnterCnt) / PushEnterCntMAX) * 255);

		//PushEnterの描画
		TitleEnterIMAGE.DrawImage();

		//半透明終了
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//ヒッカドゥアの説明画像を表示
	//HikkaduwaPresenIMAGE[0].DrawImage();
	//HikkaduwaPresenIMAGE[1].DrawImage();

	//タンブールの説明画像を表示
	//TrublePresenIMAGE[0].DrawImage();
	//TrublePresenIMAGE[1].DrawImage();




	return;
}



