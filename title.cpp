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

char MoviePlayCnt;

//===ファイル素材（クラス）===

MOVIE OpeningMOVIE;				//オープニングムービー

SOUND TitleBGM;					//タイトルのBGM
IMAGE TitleIMAGE;				//タイトルの背景

IMAGE HikkaduwaPresenIMAGE[HikkaduwaPresen_SIZE];	//ヒッカドゥアのプレイ説明の画像を入れた配列
IMAGE TrublePresenIMAGE[TruNblePresen_SIZE];		//タンブールのプレイ説明の画像を入れた配列

//タイトル素材ロード
BOOL GameLoad_Title()
{
	//画像の読み込み
	if (TitleIMAGE.LoadImageMem(".\\image\\title\\タイトル画面_背景.jpg") == FALSE) return FALSE;				//タイトル背景画像

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
	//関数の初期化
	MoviePlayCnt = 0;

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
	
	//画像のfalse・trueの表示を設定
	//HikkaduwaPresenIMAGE[0].SetActiveImage(false);		//ヒッカドゥアの説明画像①
	//HikkaduwaPresenIMAGE[1].SetActiveImage(false);		//ヒッカドゥアの説明画像②
	//TrublePresenIMAGE[0].SetActiveImage(false);			//タンブールの説明画像①
	//TrublePresenIMAGE[1].SetActiveImage(false);			//タンブールの説明画像②

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
	//動画を再生
	if (true)
	{

	}
	OpeningMOVIE.MyPlayMOVIE();

	MoviePlayCnt++;
	//動画再生が終わったら
	if (MoviePlayCnt == 1)
	{
		TitleIMAGE.DrawImage();	//タイトル画面背景
	}



	//ヒッカドゥアの説明画像を表示
	//HikkaduwaPresenIMAGE[0].DrawImage();
	//HikkaduwaPresenIMAGE[1].DrawImage();

	//タンブールの説明画像を表示
	//TrublePresenIMAGE[0].DrawImage();
	//TrublePresenIMAGE[1].DrawImage();




	return;
}



