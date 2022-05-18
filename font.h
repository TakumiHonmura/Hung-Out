#pragma once
#include "main.h"

//===================================================================
// マクロ定義
//===================================================================

//パスと名前
#define FONT_WORK_PATH	TEXT(".\\font\\work.ttf")
#define FONT_WORK_NAME	TEXT("仕事メモ書き")

//MS ゴシック
#define FONT_MSGOTH_NAME	TEXT("MS ゴシック")

//デフォルトのフォント設定
#define DEF_FONT_NAME	FONT_WORK_NAME
#define DEF_FONT_SIZE	24
#define DEF_FONT_THINCK	1
#define DEF_FONT_TYPE	DX_FONTTYPE_ANTIALIASING

//エラーメッセージ
#define FONT_INSTALL_ERR_TITLE  TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE   TEXT("フォント作成エラー")

//===================================================================
// フォントクラス
//===================================================================

/// <summary>
/// フォントのクラス
/// </summary>
class FONT
{
private:
	int handle;			//ハンドル
	int size;			//サイズ
	int thinck;			//太さ
	int type;			//タイプ
	char name[STR_MAX];	//名前
public:
	FONT(const char* fname = "\0", int fsize = 0, int fthinck = 0, int ftype = 0);
	BOOL FontCreateHandle(VOID);	//フォントハンドルを作成
	VOID SetDefaultFont(VOID);		//フォントを全体に反映させる
	INT GetHandle(VOID);			//ハンドルの値を取得
	~FONT();
};

//===================================================================
// 外部のグローバル変数
//===================================================================

extern FONT fontDef;		//デフォルトのフォント
extern FONT fontDef_h1ver;	//デフォルトのフォント h1版
extern FONT fontDef_h2ver;	//デフォルトのフォント h2版
extern FONT fontDef_h3ver;	//デフォルトのフォント h3版
extern FONT fontDef_h4ver;	//デフォルトのフォント h4版

/*
h1 48-72
h2 36-60
h3 24-48
h4 16-36
p  8 -24（デフォルト）
*/

//===================================================================
//プロトタイプ宣言
//===================================================================

extern BOOL FontAdd(VOID);		//フォントの読み込み
extern VOID FontRemove(VOID);	//フォントの削除