#pragma once
#include "DxLib.h"
#include <iostream>
#include <vector>
#include <math.h>	//数学系
#include <string.h>	//文字列系
#include <time.h>	//時間系

using namespace std;

//ゲームの基礎的なデータが入っています

//=========================================================
// マクロ定義
//=========================================================

//ゲーム設定

#define GAME_TITLE "Hung Out"			//ゲームタイトル
#define GAME_WIDTH	1280				//ゲーム画面の幅
#define GAME_HEIGHT	720					//ゲーム画面の高さ
#define GAME_COLOR  32					//ゲームの色域

#define GAME_ICON_ID	333				//ゲームのICONのID

#define GAME_WINDOW_BAR	0				//ウィンドウバーの種類

#define GAME_DEBUG	TRUE				//デバッグモード

#define PATH_MAX	255					//パスの長さ
#define STR_MAX		255					//文字の長さ
#define IMGDIV_MAX	128					//ハンドルの最大数(任意)

//タイトル画面で使うもの
#define HikkaduwaPresen_SIZE	2		//プレイ説明画像を入れた配列の要素する(ヒッカドゥア)
#define TruNblePresen_SIZE	2			//プレイ説明画像を入れた配列の要素する(タンブール)

//=========================================================
// 列挙型（C+＋ver）
//=========================================================

//ゲームシーン
enum class GAME_SCREEN : int
{
	DREAM1,
	DREAM2,
	DREAM3,
	DREAM4,
	DREAM5,
	DREAM6,
	TITLE,
	DAYTIME,
	RECORD,
	CHANGE
};

enum class PLAYTYPE : int
{
	NONE,
	//音楽
	BGM = DX_PLAYTYPE_LOOP,	//ループする
	SE = DX_PLAYTYPE_BACK,	//ループさせない
	//動画
	LOOP,					//ループする
	NOMAL					//ループさせない

};


//キャラの向き
enum class CHARA_DIR : int
{
	NONE,
	ABOVE,
	ABOVE_RIGHT,
	ABOVE_LEFT,
	RIGHT,
	LEFT,
	BELOW,
	BELOW_RIGHT,
	BELOW_LEFT
};

//値の種類
enum class VALUE : int
{
	X,
	Y,
	WIDTH,
	HEIGHT,
	ISDRAW
};

//=========================================================
// クラス
//=========================================================

//継承の関係
//
//  雛形(パスとハンドルだけが入っている)
//  ↑←←←←┐
//  音楽      画像関係の雛形
//            ↑←←←┐
//           画像    動画
//            ↑
//          連続画像

//雛形
class TEMPLATE
{
public:
	int handle;			//ハンドル（管理番号）
	char path[PATH_MAX];//パス　　（場所）

	TEMPLATE(const char* path = "\0");
	virtual ~TEMPLATE() {};
};

//音楽
class SOUND : public TEMPLATE
{
private:
	int volume;
	PLAYTYPE playtype;
public:
	SOUND(int v = 0, int pt = (int)PLAYTYPE::NONE) :volume(v), playtype((PLAYTYPE)pt) {};
	BOOL LordSound(const char* pathCopy, int volumeCopy, PLAYTYPE playTipeCopy); //音楽ファイルの読み込み
	VOID MyPlaySound(VOID);				//音楽の再生
	VOID ChangeSoundVolume(int vCopy);	//音量の変更
	VOID MyStopSound(VOID);				//音楽の停止
	~SOUND();							//ココで音楽ファイルの削除
};

//動画
class MOVIE : public TEMPLATE
{
private:
	int volume;
	PLAYTYPE playtype;
public:
	MOVIE(int v = 0, int pt = (int)PLAYTYPE::NONE) :volume(v), playtype((PLAYTYPE)pt) {};
	BOOL LoadMOVIE(const char* pathCopy, int volumeCopy, PLAYTYPE playTipeCopy); //動画ファイルの読み込み
	VOID MyPlayMOVIE(VOID);				//動画の再生
	VOID ChangeMOVIEVolume(int vCopy);	//動画の変更
	VOID MyStopMOVIE(VOID);				//動画の停止
	~MOVIE();							//ココで動画ファイルの削除
};

//画像関係の雛形
class TEMPLATE_IMAGE : public TEMPLATE
{
protected:
	int x;
	int y;
	int width;
	int height;
public:
	TEMPLATE_IMAGE(int xCopy = 0, int yCopy = 0, int widthCopy = 0, int heightCopy = 0);
};

//画像
class IMAGE : public TEMPLATE_IMAGE
{
protected:
	RECT collision;
	BOOL isDraw;
public:
	IMAGE();
	virtual BOOL LoadImageMem(const char* pathCopy = "\0");//画像の読み込み
	VOID CollisionUpdate(VOID);			//当たり判定の更新
	virtual VOID DrawImage(VOID);		//画像の描画
	VOID SetImage(int xS, int yS);		//画像の位置決め
	VOID SetImageOnCollision(RECT xColl);//引数の当たり判定を基準に画像の位置決め
	VOID MoveImage(int xM, int yM);		//画像の移動
	INT GetValue(VALUE valueK);			//クラスの値を取得
	RECT GetColl(VOID);					//クラスの当たり判定を取得
	VOID SetActiveImage(BOOL Active);	//画像の表示・非表示
	~IMAGE();							//ココで削除

	//コピーコンストラクタ
	IMAGE(const IMAGE& Cimage)
	{
		handle = Cimage.handle;
		strcpy_s(path, PATH_MAX, Cimage.path);
		x = Cimage.x;
		y = Cimage.y;
		width = Cimage.width;
		height = Cimage.height;
		collision = Cimage.collision;
		isDraw = Cimage.isDraw;
	}
	//代入演算子のオーバーロード
	virtual IMAGE& operator= (const IMAGE& Cimage)
	{
		handle = Cimage.handle;
		strcpy_s(path, PATH_MAX, Cimage.path);
		x = Cimage.x;
		y = Cimage.y;
		width = Cimage.width;
		height = Cimage.height;
		collision = Cimage.collision;
		isDraw = Cimage.isDraw;
		return *this;
	}
};

//連続画像
class DIVIMAGE : public IMAGE
{
private:
	int divNum;					//分割数
	int divHandle[IMGDIV_MAX] = { 0 };//画像のハンドル
	int nowIndex;				//現在のハンドル配列の要素番号

	int divSide;		//横の分割数
	int divVertical;	//縦の分割数

	int animCnt;		//アニメーションカウンタ
	int animCntMax;		//アニメーションカウンタ(最大)
	BOOL IsAnimLoop;	//ループの有無
public:
	DIVIMAGE(int divsideCopy = 0,
		int divverticalCopy = 0,
		int animcntCopy = 0,
		BOOL isanimloopCopy = FALSE) :
		divSide(divsideCopy), divVertical(divverticalCopy),
		animCntMax(animcntCopy), IsAnimLoop(isanimloopCopy),
		divNum(0), nowIndex(0), animCnt(0) {};
	BOOL LoadImageMem(const char* pathCopy, int divSideCopy, int divVerticalCopy, float animCntCopy);
	VOID DrawImage(VOID);
	~DIVIMAGE();
};