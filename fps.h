#pragma once
#include "main.h"

//===================================================================
// マクロ定義
//===================================================================

#define GAME_FPS		60	//FPS標準
#define GAME_FPS_MAX	240	//FPS最大
#define GAME_FPS_MIN	60	//FPS最小

//===================================================================
// FPSクラス
//===================================================================

/// <summary>
/// FPSクラス
/// </summary>
class FPS
{
private:
	BOOL isInitFlg;			//最初の測定開始フラグ
	LONGLONG startTime;		//測定開始時刻
	LONGLONG nowTime;		//現在の時刻
	LONGLONG oldTime;		//以前の時刻
	int value;				//FPSの値
	float deltaTime;		//0が5個 経過時間
	int count;				//現在のフレーム数
	float drawValue;		//計算結果を描画
	int sampleRate;			//平均を取るサンプル値
	float gameTime;			//ゲーム内時間
	DATEDATA nowDataTime;	//現在の日付時刻
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
// 変数の外部宣言
//===================================================================

//fpsの管理
extern FPS fps;