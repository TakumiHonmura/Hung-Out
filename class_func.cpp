#include "main.h"
#include "fps.h"

//クラス内の関数処理

//=========================================================
//  雛形
//=========================================================

TEMPLATE::TEMPLATE(const char* pathCopy)
{
	handle = -1;
	strcpyDx(path, pathCopy);
}


//=========================================================
//  画像の雛形
//=========================================================

TEMPLATE_IMAGE::TEMPLATE_IMAGE(int xCopy, int yCopy, int widthCopy, int heightCopy)
{
	x = xCopy;
	y = yCopy;

	width = widthCopy;
	height = heightCopy;
}


//=========================================================
//  画像
//=========================================================

IMAGE::IMAGE()
{
	isDraw = FALSE;
	CollisionUpdate();
}

/// <summary>
/// 画像の読み込み
/// </summary>
/// <param name="pathCopy">画像のパス</param>
/// <returns>読み込めた・TRUE｜エラー・FALSE</returns>
BOOL IMAGE::LoadImageMem(const char* pathCopy)
{
	//画像の読み込み
	strcpyDx(path, pathCopy);		//パスのコピー
	handle = LoadGraph(&path[0]);	//画像の読み込み

	//読み込めなかったらエラー表示
	if (handle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//メインのウィンドウハンドル
			path,					//メッセージ本文
			"画像読み込みエラー",	//メッセージタイトル
			MB_OK					//ボタン
		);
		return FALSE;	//読み込み失敗
	}

	//画像の幅と高さを取得
	GetGraphSize(handle, &width, &height);

	//画像の位置を初期化
	x = 0; y = 0;

	//当たり判定の更新
	CollisionUpdate();

	//画像を描画する
	isDraw = TRUE;

	return TRUE;
}

/// <summary>
/// 当たり判定の更新
/// </summary>
VOID IMAGE::CollisionUpdate(VOID)
{
	collision.left   = x;
	collision.top    = y;
	collision.right  = x + width;
	collision.bottom = y + height;

	return;
}

/// <summary>
/// 画像の描画
/// </summary>
VOID IMAGE::DrawImage(VOID)
{
	//描画できるなら描画
	if (isDraw) DrawGraph(x, y, handle, TRUE);

	//デバッグモードで当たり判定を表示
	if (GAME_DEBUG) DrawBox(collision.left, collision.top, collision.right, collision.bottom, GetColor(255, 255, 255), FALSE);

	return;
}

/// <summary>
/// 画像の位置決め
/// </summary>
/// <param name="xS">X座標の位置</param>
/// <param name="yS">Y座標の位置</param>
VOID IMAGE::SetImage(int xS, int yS)
{
	x = xS;
	y = yS;

	CollisionUpdate();

	return;
}

/// <summary>
/// 引数の当たり判定を基準に画像の位置決め
/// </summary>
/// <param name="xColl"></param>
VOID IMAGE::SetImageOnCollision(RECT xColl)
{
	x = xColl.left;
	y = xColl.top;

	CollisionUpdate();

	return;
}

/// <summary>
/// 画像の移動
/// </summary>
/// <param name="xM">X座標の移動距離</param>
/// <param name="yM">Y座標の移動距離</param>
VOID IMAGE::MoveImage(int xM, int yM)
{
	x += xM;
	y += yM;

	CollisionUpdate();

	return;
}

/// <summary>
/// クラスの値を取得
/// </summary>
/// <returns>引数に応じた値/どれにも当てはまらい時は-1</returns>
INT IMAGE::GetValue(VALUE valueK)
{
	switch (valueK)
	{
	case VALUE::X:
		return x;
		break;
	case VALUE::Y:
		return y;
		break;
	case VALUE::WIDTH:
		return width;
		break;
	case VALUE::HEIGHT:
		return height;
		break;
	case VALUE::ISDRAW:
		if (isDraw) return TRUE;
		else return FALSE;
	default:
		return -1;
		break;
	}
}

/// <summary>
/// 画像の当たり判定を取得
/// </summary>
/// <param name="">RECT構造体</param>
/// <returns></returns>
RECT IMAGE::GetColl(VOID)
{
	return collision;
}

/// <summary>
/// 画像の表示・非表示を設定
/// </summary>
/// <param name="Active">設定したい表示状態</param>
VOID IMAGE::SetActiveImage(BOOL Active)
{
	isDraw = Active;

	return;
}

IMAGE::~IMAGE()
{
	//画像ハンドルを解放
	DeleteGraph(handle);
}


//=========================================================
//  分割画像
//=========================================================

/// <summary>
/// 画像を分割してメモリに読み込み
/// </summary>
/// <param name="pathCopy">画像のパス</param>
/// <param name="divSideCopy">横の分割数</param>
/// <param name="divVerticalCopy">縦の分割数</param>
/// <param name="animCnt">画像切り替えの秒数(s)</param>
/// <returns></returns>
BOOL DIVIMAGE::LoadImageMem(const char* pathCopy, int divSideCopy, int divVerticalCopy, float animCntCopy)
{
	//画像読み込みのフラグ
	int isLoad = -1;

	//一時的に画像のハンドルを用意する
	int tempHandle = LoadGraph(pathCopy);

	//読み込みエラー処理
	if (tempHandle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//メインのウィンドウハンドル
			pathCopy,					//メッセージ本文
			"画像読み込みエラー",	//メッセージタイトル
			MB_OK					//ボタン
		);
		return FALSE;
	}

	//画像の幅と高さを取得
	int width2 = -1;
	int height2 = -1;
	GetGraphSize(tempHandle, &width2, &height2);

	isLoad = LoadDivGraph(
		pathCopy,										//画像のパス
		divSideCopy * divVerticalCopy,					//分割総数
		divSideCopy, divVerticalCopy,					//横と縦の分割
		width2 / divSideCopy, height2 / divVerticalCopy,	//画像一つ分の幅と高さ
		&divHandle[0]									//連続で管理する配列の先頭アドレス
	);

	//分割エラー
	if (isLoad == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//メインのウィンドウハンドル
			pathCopy,				//メッセージ本文
			"画像分割エラー",		//メッセージタイトル
			MB_OK					//ボタン
		);
		return FALSE;
	}

	//情報を設定
	divSide = divSideCopy;
	divVertical = divVerticalCopy;
	divNum = divSide * divVertical;
	x = 0;
	y = 0;
	GetGraphSize(divHandle[0], &width, &height);
	animCnt = 0;
	animCntMax = (int)(animCntCopy * GAME_FPS);
	IsAnimLoop = FALSE;
	nowIndex = 0;

	//当たり判定の更新
	CollisionUpdate();

	//画像は描画する
	isDraw = FALSE;

	//一時的に読み込んだハンドルを解放
	DeleteGraph(tempHandle);

	return TRUE;
}

/// <summary>
/// 分割画像の描画
/// </summary>
/// <param name=""></param>
VOID DIVIMAGE::DrawImage(VOID)
{
	//画像が描画出来る時だけ描画
	if (isDraw)
	{
		DrawGraph(x, y, divHandle[nowIndex], TRUE);

		//アニメーションのカウントアップ
		if (animCnt < animCntMax) { ++animCnt; }
		else
		{
			//全てのアニメーションを描画し終えたら
			if (nowIndex == divNum - 1)
			{
				//アニメーションを繰り返さないなら描画を止める
				if (!IsAnimLoop) isDraw = FALSE;
				animCnt = 0;
				nowIndex = 0;
			}
			else if (nowIndex < divNum - 1)
			{//次の画像があるなら次へ
				++nowIndex;
			}

			//カウンタをクリア
			animCnt = 0;
		}
	}

	//デバッグモードの時は当たり判定を描画
	if (GAME_DEBUG) DrawBox(collision.left, collision.top, collision.right, collision.bottom, GetColor(255, 255, 255), FALSE);

	return;
}

DIVIMAGE::~DIVIMAGE()
{
	//画像ハンドルを解放
	for (int i = 0; i < divNum; i++) DeleteGraph(divHandle[i]);
}

//=========================================================
//  音楽
//=========================================================

/// <summary>
/// 音楽ファイルの読み込み
/// </summary>
/// <param name="pathCopy">音楽ファイルのパス</param>
/// <param name="volumeCopy">音量</param>
/// <param name="playTipeCopy">プレイタイプ(単発orループ)</param>
/// <returns>成功：TRUE｜失敗：FALSE</returns>
BOOL SOUND::LordSound(const char* pathCopy, int volumeCopy, PLAYTYPE playTipeCopy)
{
	//音楽の読み込み
	strcpyDx(path, pathCopy);		//パスのコピー
	handle = LoadSoundMem(path);	//音楽の読み込み

	//音楽が読み込めなかったときは、エラー(-1)が入る
	if (handle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//メインのウィンドウハンドル
			path,					//メッセージ本文
			"音楽読み込みエラー！",	//メッセージタイトル
			MB_OK					//ボタン
		);

		return FALSE;	//読み込み失敗
	}

	//その他の設定
	volume = volumeCopy;
	playtype = playTipeCopy;

	return TRUE;
}

/// <summary>
/// 音楽の再生
/// </summary>
/// <param name=""></param>
VOID SOUND::MyPlaySound(VOID)
{
	//ループ再生でなければ、そのまま再生する
	if (playtype == PLAYTYPE::SE)
	{
		PlaySoundMem(handle, (int)playtype);//音楽の再生
	}
	//ループ再生のときは、音楽が再生されていなければ、再生する
	else if (playtype == PLAYTYPE::BGM)
	{
		if (CheckSoundMem(handle) == 0)
		{
			PlaySoundMem(handle, (int)playtype);//音楽の再生
		}
	}

	return;
}

/// <summary>
/// 音量の変更
/// </summary>
/// <param name="vCopy">設定したい音量(0~255)</param>
VOID SOUND::ChangeSoundVolume(int vCopy)
{
	//音量変更
	if (0 <= volume && volume <= 255)
	{
		volume += vCopy;
		ChangeVolumeSoundMem(volume, handle);
	}

	//音量が範囲外だったら範囲内に戻す
	if (0 > volume)
	{
		volume = 0;
		ChangeVolumeSoundMem(volume, handle);
	}

	if (volume >= 255)
	{
		volume = 255;
		ChangeVolumeSoundMem(volume, handle);
	}

	return;
}

/// <summary>
/// 音楽の停止
/// </summary>
/// <param name=""></param>
VOID SOUND::MyStopSound(VOID)
{
	StopSoundMem(handle);

	return;
}

SOUND::~SOUND()
{
	//音楽ファイルのハンドル解放
	DeleteMusicMem(handle);
}

/*
BOOL LordImageDivMem(const char* path, int divSideCopy, int divVerticalCopy);
VOID DrawImage(VOID);
VOID DrawImageChara(VOID);
~DIVIMAGE();
*/

/*
VOID DeleteSound(SOUND* sound);			//音楽ファイルの削除

TEMPLATE_IMAGE(int x = 0, int y = 0, int width = 0, int height = 0);
*/