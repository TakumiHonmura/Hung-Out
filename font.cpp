#include "font.h"
//フォントに関わる変数・関数が入っています

FONT fontDef(DEF_FONT_NAME, DEF_FONT_SIZE, DEF_FONT_THINCK, DEF_FONT_TYPE);	//デフォルトのフォント
FONT fontDef_h1ver(DEF_FONT_NAME, 72, DEF_FONT_THINCK, DEF_FONT_TYPE);	//デフォルトのフォント h1版
FONT fontDef_h2ver(DEF_FONT_NAME, 60, DEF_FONT_THINCK, DEF_FONT_TYPE);	//デフォルトのフォント h2版
FONT fontDef_h3ver(DEF_FONT_NAME, 48, DEF_FONT_THINCK, DEF_FONT_TYPE);	//デフォルトのフォント h3版
FONT fontDef_h4ver(DEF_FONT_NAME, 36, DEF_FONT_THINCK, DEF_FONT_TYPE);	//デフォルトのフォント h4版

//クラス内の関数処理

//===================================================================
//  クラスの関数本体
//===================================================================

/// <summary>
/// フォントクラスのコンストラクタ
/// </summary>
/// <param name="fname">名前</param>
/// <param name="fsize">サイズ</param>
/// <param name="fthinck">太さ</param>
/// <param name="ftype">タイプ</param>
FONT::FONT(const char* fname, int fsize, int fthinck, int ftype)
{
	//クラス内の変数をセットアップ
	strcpy_sDx(name, STR_MAX, fname);	//名前
	size   = fsize;						//サイズ
	thinck = fthinck;					//太さ
	type = ftype;						//タイプ

	//ハンドルを初期化
	handle = -1;
}

/// <summary>
/// フォントのハンドルを作成
/// </summary>
/// <returns>成功→TRUE｜失敗→FALSE</returns>
BOOL FONT::FontCreateHandle(VOID)
{
	handle = CreateFontToHandle(
		name,
		size,
		thinck,
		type
	);

	if (handle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//メインのウィンドウハンドル
			name,					//メッセージ本文
			FONT_CREATE_ERR_TITLE,	//メッセージタイトル
			MB_OK					//ボタン
		);
		return FALSE;
	}

	return TRUE;
}

/// <summary>
/// フォントを全体へ反映
/// </summary>
/// <param name=""></param>
VOID FONT::SetDefaultFont(VOID)
{
	ChangeFont(name);			//名前を設定
	SetFontSize(size);			//サイズを設定
	SetFontThickness(thinck);	//太さを設定
	ChangeFontType(type);		//タイプを設定

	return;
}

/// <summary>
/// フォントクラスのハンドルを取得
/// </summary>
/// <param name=""></param>
/// <returns>ハンドルの値</returns>
INT FONT::GetHandle(VOID)
{
	return handle;
}

FONT::~FONT()
{
	DeleteFontToHandle(handle);
}

//===================================================================
//  普通の関数
//===================================================================

/// <summary>
/// フォントの読み込み
/// </summary>
/// <param name=""></param>
/// <returns>成功→TRUE｜失敗→FALSE</returns>
BOOL FontAdd(VOID)
{
	//フォントを一時的に読み込み
	if (!AddFontResourceEx(FONT_WORK_PATH, FR_PRIVATE, NULL))
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), FONT_WORK_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID FontRemove(VOID)
{
	//一時的に読み込んだフォントを削除
	RemoveFontResourceEx(FONT_WORK_PATH, FR_PRIVATE, NULL);

	return;
}