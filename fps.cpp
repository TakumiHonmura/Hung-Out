#include "fps.h"
//FPSに関する関数が入っています

//=========================================================
//  グローバル変数
//=========================================================

//fpsの管理
FPS fps;

//=========================================================
//  クラス関数
//=========================================================

/// <summary>
/// FPS値の計測、値の更新
/// </summary>
/// <param name=""></param>
VOID FPS::FPSUpdate(VOID)
{
	//一番最初の処理
	if (!fps.isInitFlg)
	{
		//測定開始時刻をマイクロ秒単位で取得
		fps.startTime = GetNowHiPerformanceCount();	//Windowsが起動してから経過した時間(マイクロ秒)
	}

	//現在の時刻をマイクロ秒単位で取得
	fps.nowTime = GetNowHiPerformanceCount();

	//一番最初だけ
	if (!fps.isInitFlg) { fps.oldTime = fps.nowTime; }	//以前の時間 = 現在の時間

	//前回取得した時間からの経過時間を秒(小数)に変換してからセット
	fps.deltaTime = (fps.nowTime - fps.oldTime) / 1000000.0f;

	//今回取得した時間を保存
	fps.oldTime = fps.nowTime;

	//一番最初だけフラグON
	if (!fps.isInitFlg) { fps.isInitFlg = TRUE; }

	//１フレーム目～FPS設定値までは、カウントアップ
	if (fps.count < fps.sampleRate)
	{
		//カウンタを増やす
		fps.count++;
	}
	else
	{
		//FPS設定値のフレームで、平均FPSを計算

		//現在の時刻から、0フレーム目の時間を引き、FPSの数値で割る
		//現在の平均FPS値が出る
		fps.drawValue = 1000000.f / ((fps.nowTime - fps.startTime) / (float)fps.sampleRate);

		//測定開始時刻をマイクロ秒単位で取得
		fps.startTime = GetNowHiPerformanceCount();	//Windowsが起動してから経過した時間(マイクロ秒)

		//カウンタ初期化
		fps.count = 1;
	}

	//ゲーム内時間カウントアップ
	fps.gameTime += fps.deltaTime;

	//現在日付時刻を取得
	GetDateTime(&fps.nowDataTime);

	return;
}

/// <summary>
/// 平均FPS値の描画
/// </summary>
/// <param name=""></param>
VOID FPS::FPSDraw(VOID)
{
	//文字列の描画
	if (GAME_DEBUG) DrawFormatString(0, 0, GetColor(0, 0, 0), "FPS:%.1f", fps.drawValue);

	return;
}

/// <summary>
/// FPSで処理を待つ
/// </summary>
/// <param name=""></param>
VOID FPS::FPSWait(VOID)
{
	//現在の時刻-最初の時刻で、現在かかっている時刻を取得する
	LONGLONG resultTime = fps.nowTime - fps.startTime;

	//待つべきミリ秒数　(1秒/FPS値 * 現在のフレーム数)から、現在かかっている時刻を引く
	int waitTime = (int)(1000000.0f / fps.value * fps.count - resultTime);

	//マイクロ秒からミリ秒に変換
	waitTime /= 1000;

	//処理が早かったら、処理を待つ
	if (waitTime > 0)
	{
		WaitTimer(waitTime);	//引数ミリ秒待つ
	}

	//垂直同期をOFFにしているか？
	if (!GetWaitVSyncFlag())
	{
		//FPS最大値ではないとき
		if (fps.value < GAME_FPS_MAX)
		{
			//１秒毎のFPS値よりも、待つ時間が小さいときは、もっとFPS値を上げても良い
			//待つ時間 10ミリ　<= 1秒/60FPS = 16.6666ミリ　もう少し早くできる
			if (waitTime > 0
				&& waitTime <= 1000.0f / fps.value)
			{
				//fps.Count++;
				fps.value++;
			}
			else
			{
				//FPS値が追いついておらず、遅いときは、FPS値を下げる
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
/// ゲーム内時間のリセット
/// </summary>
/// <param name=""></param>
VOID FPS::ReseGameTime(VOID)
{
	fps.gameTime = 0;
	return;
}

/// <summary>
/// ゲーム内時間を取得
/// </summary>
/// <param name=""></param>
/// <returns>ゲーム内時間(実数型)</returns>
float FPS::GetGameTime(VOID)
{
	return fps.gameTime;
}