#include "main.h"
#include "font.h"
#include "fps.h"
#include "keyboard.h"
#include "scene.h"


//=========================================================
//  シーン関係のグローバル変数
// 
// CTRL+G 155 コメントアウト
//=========================================================

//シーン管理の変数
GAME_SCREEN GameScreen;		//現在のゲームシーン
GAME_SCREEN OldGameScreen;	//一つ前ゲームシーン
GAME_SCREEN NextGameScreen;	//次のゲームシーン

//===画面の切り替え===
//今回は全部のスクリーン遷移でイン・アウトどっちも使う
IMAGE eyeAbove; //切り替え画面用その1
IMAGE eyeBelow; //切り替え画面用その2

BOOL isEyeIn  = FALSE;
BOOL isEyeOut = FALSE;

int eyeTimeMilli = 500; //切り替えにかける時間(ミリ秒)
int eyeTimeMax = eyeTimeMilli * 60 / 1000;

//アイインアウト
int eyeInOutCntInit = 0;
int eyeInOutCnt = eyeInOutCntInit;
int eyeInOutCntMax = eyeTimeMax;

//=========================================================
//  ゲームシーンごとの関数
//=========================================================

BOOL GameLoad(VOID);		//データを読込

VOID GameInit(VOID);		//データの初期化

VOID GameDelete(VOID);		//データの削除

VOID Title(VOID);		//タイトル画面
VOID TitleProc(VOID);	//タイトル画面(処理)
VOID TitleDraw(VOID);	//タイトル画面(描画)

VOID Change(VOID);		//切り替え画面
VOID ChangeProc(VOID);	//切り替え画面(処理)
VOID ChangeDraw(VOID);	//切り替え画面(描画)

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//Log.txtを出力しない
	ChangeWindowMode(TRUE);								//ウィンドウモードにする
	SetMainWindowText(GAME_TITLE);						//タイトルをウィンドウの左上に表示
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//ウィンドウの解像度を設定
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);				//ウィンドウの大きさを設定
	SetBackgroundColor(255, 255, 255);					//背景色を設定
	SetWindowIconID(GAME_ICON_ID);						//アイコンファイルを読込
	SetWindowStyleMode(GAME_WINDOW_BAR);				//ウィンドウバーの状態
	SetWaitVSyncFlag(TRUE);								//ディスプレイの垂直同期を有効にする
	SetAlwaysRunFlag(TRUE);								//ウィンドウをずっとアクティブにする

	//DXライブラリの初期化処理(エラーが起きたら直ちに終了)
	if (DxLib_Init()) return -1;

	//ダブルバッファリングを有効化
	SetDrawScreen(DX_SCREEN_BACK);

	//最初のシーンはタイトル画面から
	GameScreen = GAME_SCREEN::TITLE;

	//シーン遷移では必ず切り替えが入るので前後は切り替え画面
	NextGameScreen = GAME_SCREEN::CHANGE;
	OldGameScreen = GAME_SCREEN::CHANGE;

	//フォントを追加&ここにフォントのクラス変数をぶち込む暴挙に出る
	if (!FontAdd()) return FALSE;
	
	//ゲームの読み込み(失敗時はデータを消して異常終了)
	if (!GameLoad())
	{
		DxLib_End();
		return -1;
	}

	//ゲーム内情報を初期化
	GameInit();

	while (1)
	{
		if (ProcessMessage()) break;  //メッセージを受け取り続ける
		if (ClearDrawScreen()) break; //メッセージを受け取り続ける

		//キーボードの入力更新
		keyboard.AllKeyUpdate();

		//FPS値の更新
		fps.FPSUpdate();

		//ESCキーで強制終了
		if (keyboard.KeyClick(KEY_INPUT_ESCAPE) == TRUE) { break; }

		switch (GameScreen)
		{
		case GAME_SCREEN::TITLE://タイトル画面
			Title();
			break;
		case GAME_SCREEN::CHANGE://切り替え画面
			Change();
			break;
		default:
			break;
		}

		//FPS値を描画
		fps.FPSDraw();

		//FPS値を待つ
		fps.FPSWait();

		ScreenFlip();			//ダブルバッファリングした画面を描画
	}

	GameDelete();	//データ(ハンドル)を削除

	FontRemove();	//フォントを削除

	DxLib_End();	//DXライブラリの終了処理

	return 0;		//ソフトの終了
}


//=========================================================
//  ゲームデータに関わる関数
//=========================================================

BOOL GameLoad(VOID)
{
	//フォントのハンドルを取得
	if (fontDef.FontCreateHandle() == FALSE) { return FALSE; }
	if (fontDef_h1ver.FontCreateHandle() == FALSE) { return FALSE; }
	if (fontDef_h2ver.FontCreateHandle() == FALSE) { return FALSE; }
	if (fontDef_h3ver.FontCreateHandle() == FALSE) { return FALSE; }
	if (fontDef_h4ver.FontCreateHandle() == FALSE) { return FALSE; }

	//fontDefをデフォルトフォントへ
	fontDef.SetDefaultFont();

	//切り替え画面用
	//eyeAbove.LoadImageMem(".\\image\\change\\EyeAbove.png");
	//eyeBelow.LoadImageMem(".\\image\\change\\EyeBelow.png");

	return TRUE;
}

VOID GameInit(VOID)
{
	//画面切り替えの画像の位置
	eyeAbove.SetImage(0, -GAME_HEIGHT);
	eyeBelow.SetImage(0, GAME_HEIGHT);
}

VOID GameDelete(VOID)
{
	//切り替え画面用
	eyeAbove.~IMAGE();
	eyeBelow.~IMAGE();
}


//=========================================================
//  画面切り替えの関数
//=========================================================

/// <summary>
/// 切り替え画面
/// </summary>
VOID Change()
{
	ChangeProc();
	ChangeDraw();
}

/// <summary>
/// 切り替え画面の処理
/// </summary>
VOID ChangeProc()
{

	//アイイン
	if (isEyeIn)
	{
		if (eyeInOutCnt > eyeInOutCntInit)
		{
			eyeInOutCnt--;
			//画像を移動
			eyeAbove.MoveImage(0, -(GAME_HEIGHT / eyeInOutCntMax));
			eyeBelow.MoveImage(0, GAME_HEIGHT / eyeInOutCntMax);
		}
		else
		{
			isEyeIn = FALSE;
		}
	}

	//アイアウト
	if (isEyeOut)
	{
		if (eyeInOutCnt < eyeInOutCntMax)
		{
			eyeInOutCnt++;
			//画像を移動
			eyeAbove.MoveImage(0, GAME_HEIGHT / eyeInOutCntMax);
			eyeBelow.MoveImage(0, -(GAME_HEIGHT / eyeInOutCntMax));
		}
		else
		{
			isEyeOut = FALSE;
			isEyeIn = TRUE;
		}
	}

	//切り替えを終了
	if (!isEyeOut && !isEyeIn)
	{
		//次のゲームシーンに応じた初期化
		switch (NextGameScreen)
		{
		case GAME_SCREEN::TITLE://タイトル画面
			//GameInit_Title();
			break;
		default:
			break;
		}

		OldGameScreen = GameScreen;  //以前のゲームシーンを更新
		GameScreen = NextGameScreen; //次のゲームシーンに切り替え
		NextGameScreen = GAME_SCREEN::CHANGE; //切り替え画面を挿入
	}

	return;
}

/// <summary>
/// 切り替え画面の描画
/// </summary>
VOID ChangeDraw()
{
	//以前のシーンを描画
	if (isEyeOut)
	{
		switch (OldGameScreen)
		{
		case GAME_SCREEN::TITLE://タイトル画面
			Title_Draw();
			break;
		default:
			break;
		}
	}
	else if (isEyeIn)
	{
		switch (NextGameScreen)
		{
		case GAME_SCREEN::TITLE://タイトル画面
			Title_Draw();
			break;
		default:
			break;
		}
	}

	//アイイン・アウト
	eyeAbove.DrawImage();
	eyeBelow.DrawImage();

	return;
}

/// <summary>
/// 画面の切り替え
/// </summary>
/// <param name="gameScreen">切り替え先のゲームシーン</param>
VOID ChangeScreen(GAME_SCREEN gameScreen)
{
	OldGameScreen = GameScreen;
	GameScreen = NextGameScreen;
	NextGameScreen = gameScreen;
	isEyeOut = TRUE;
}