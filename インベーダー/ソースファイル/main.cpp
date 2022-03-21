/*project2 筒井杏二*/

#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include <time.h>
#include "DxLib.h"
#include "main.h"

/**********************  変数宣伝  ****************************/
//システム
SCENE_ID sceneID;                            //ゲームのシーン
int gameCounter;                             //ゲームループカウンタ
int spaceKeyBack;                            //スペースの１フレーム前の状態
int spaceKeyTriggerKeyDown;                  //スペースキーのトリガー（押されたとき）
int spaceKeyTriggerKeyUp;                    //スペースキーのトリガー（話されたとき）
bool Female;                                 //キャラ選択（女）
bool Male;                                   //キャラ選択（男）
bool pushA;                                  //Aが押されたら
bool pushD;                                  //Dが押されたら
int backImage;                               //グラフィックハンドル（タイトル）
int game_overImage;                          //グラフィックハンドル（ゲームオーバー）
int ArrowLRImage;                            //グラフィックハンドル(矢印左右)
int ArrowUPImgae;                            //グラフィックハンドル(矢印上)
int startCounter;                            //ゲームが始まってからの経過時間
int clearCounter;                            //ゲームクリアしてからの時間
int win_se;                                  //ゲームクリアの効果音ハンドル
int ANIME;                                   //プレイヤーのアニメーション(タイトル)
int sunImage;                                //グラフィックハンドル(太陽)
double en;                                   //回転用変数

//背景関連
int bgImage;                                 //グラフィックハンドル（背景）
double bgPosX1;                              //背景座標X1
double bgPosX2;                              //背景座標X2

//プレイヤー関連
int playerImage1[DIR_MAX][ANIM_MAX];          //グラフィックハンドル（男）
int playerImage2[DIR_MAX][ANIM_MAX];          //グラフィックハンドル（女）
int playerPosX;                              //自機の座標X
int playerPosY;                              //自機の座標Y
int playerSpeed;                             //自機の移動量
bool playerAlive;                            //生存証明（プレイヤー）
int playerLife;                              //自機の残機
int playerAnime;                             //プレイヤーのアニメーション(ゲーム)
int playerdir;                               //プレイヤーの向き
int Pushtime;                                //ボタンカウント
int player_se1;                              //効果音ハンドル(男)
int player_se2;                              //効果音ハンドル(女)

//敵関連
int enemyImage[ENEMY_TYPE_MAX][DIR_MAX][ANIM_MAX];       //グラフィックハンドル（敵）
int enemyPosX[ENEMY_COUNT_Y][ENEMY_COUNT_X];             //敵(団体)の座標X
int enemyPosY[ENEMY_COUNT_Y][ENEMY_COUNT_X];             //敵(団体)の座標Y
int EnemyPosX;                                           //敵(個体)の座標X
int EnemyPosY;                                           //敵(個体)の座標Y
bool enemyAlive[ENEMY_COUNT_Y][ENEMY_COUNT_X];           //生存証明（敵（団体））
bool EnemyAlive;                                         //生存証明（敵（個体））
int enemySpeed;                                          //敵の移動量
int enemyAnime;                                          //敵のアニメーション
int enemydir;                                            //敵の向き(団体)
int Enemydir;                                            //敵の向き(個体)
int enemyCount;                                          //敵の残り数
int enemy_se;                                            //効果音ハンドル(敵（団体）)
int Enemy_se;                                            //効果音ハンドル(敵（個体）)
MOVE_LR EnemyMove;                                       //敵（個体）の左右移動管理
MOVE_LR enemyMoveFlagX;                                  //敵（団体）の左右移動管理
MOVE_MODE enemyMoveMode;                                 //敵（団体）の移動モード管理
                                                                                                                                                                               
//弾関連（P）
int pShotImage;                        //グラフィックハンドル(P弾)
int pShotSpeed;                        //弾の速さ（P）
int pShotPosX;                         //弾のX（P）
int pShotPosY;                         //弾のY（P）
bool pShotAlive;                       //弾（P）の表示：非表示

//弾関連（E）
int eShotImage;                                                                  //グラフィックハンドル（E弾）
int eShotPosX[ENEMY_COUNT_Y][ENEMY_COUNT_X];                                     //弾のX（E）
int eShotPosY[ENEMY_COUNT_Y][ENEMY_COUNT_X];                                     //弾のY（E）
int eShotSpeed;                                                                  //弾の速さ（E）
bool eShotAlive[ENEMY_COUNT_Y][ENEMY_COUNT_X];                                   //弾（E）の表示：非表示

//得点関連
int score;                                                                        //得点
int highScore;                                                                    //最高得点
int scorePosX;                                                                    //得点(団体)表示座標X
int scorePosY;                                                                    //得点(団体)表示座標Y
bool scoreAlive;                                                                  //得点（団体）の表示：非表示
int ScorePosX;                                                                    //得点(個体)表示座標X
int ScorePosY;                                                                    //得点(個体)表示座標Y
bool ScoreAlive;                                                                  //得点（個体）の表示：非表示
int scoreTime;                                                                    //スコアの表示時間
int ScoreTime;                                                                    //スコア(ボーナス)の表示時間
int font;                                                                         //スコアのサイズ
int fonthigh;                                                                     //ハイスコアのサイズ
bool newRecord;                                                                   //ハイスコアを更新したかのチェック

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//初期化処理
	if (SysInit() == false) //引数と戻り値
	{
		TRACE("初期化失敗");
		return false;
	}
	/*ゲームループ*/
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		gameCounter++;
		//敵の表示処理
		_dbgStartDraw();
		KeyCheck();              // キートリガーチェックの関数

		switch (sceneID)
		{
		case SCENE_ID_INIT:
			InitScene();
			break;
		case SCENE_ID_TITLE:
			Gamestart();
			break;
		case SCENE_ID_GAME:
			Gamescene();
			break;
		case SCENE_ID_LOSE:
			Gameover();
			break;
		default:
			break;
		}
		//if (sceneID == SCENE_ID_TITLE) //タイトルシーン
		//{
		//	Gamestart();
		//}
		////ゲームシーン
		//if (sceneID == SCENE_ID_GAME)
		//{
		//	Gamescene();
		//}
		////ゲームクリアシーン
		//else if (sceneID == SCENE_ID_WIN)
		//{
		//	Gameclear();
		//}
		////ゲームオーバーシーン
		//else if (sceneID == SCENE_ID_LOSE)
		//{
		//	Gameover();
		//}
	}
	DxLib_End();
	return 0;
}

void KeyCheck(void)   //キートリガーチェックの関数
{
	if (spaceKeyBack == 0) //フレイム前の状態
	{
		TRACE("前　off");
	}
	else
	{
		TRACE("前 on");
	}
	if (CheckHitKey(KEY_INPUT_SPACE))  //フレイム後の状態
	{
		TRACE(" 今　on");
		if (CheckHitKey(KEY_INPUT_SPACE) == 1 && spaceKeyBack == 0)  //トリガー処理
		{
			TRACE("----KEY_DOWN");
			spaceKeyTriggerKeyDown = 1;
		}
		else
		{
			spaceKeyTriggerKeyDown = 0;
		}
	}
	else
	{
		TRACE(" 今　off");
		if (CheckHitKey(KEY_INPUT_SPACE) == 0 && spaceKeyBack == 1)  //トリガー処理
		{
			TRACE("----KEY_UP");
			spaceKeyTriggerKeyUp = 1;
		}
		else
		{
			spaceKeyTriggerKeyUp = 0;
		}
	}
	spaceKeyBack = CheckHitKey(KEY_INPUT_SPACE);
	TRACE("  Down = %d : Up = %d", spaceKeyTriggerKeyDown, spaceKeyTriggerKeyUp);
	TRACE("\n");
}

void Enemy(void)  //敵の処理
{
	if (enemyMoveMode == MOVE_MODE_DOWN)//敵の集団下移動処理
	{
		for (int y = 0; y < ENEMY_COUNT_Y; y++)
		{
			for (int x = 0; x < ENEMY_COUNT_X; x++)
			{
				enemyPosY[y][x] += ENEMY_SIZE_Y;
			}
		}
		enemyMoveMode = MOVE_MODE_LR;

	}
	else
	{
		for (int Y = 0; Y < ENEMY_COUNT_Y; Y++)
		{
			for (int X = 0; X < ENEMY_COUNT_X; X++) //敵の移動処理
			{
				if (enemyMoveFlagX == MOVE_RIGHT)
				{
					enemyPosX[Y][X] += enemySpeed;
				}
				else
				{
					enemyPosX[Y][X] -= enemySpeed;
				}
			}
		}
	}
	for (int y = 0; y < ENEMY_COUNT_Y; y++)
	{
		for (int x = 0; x < ENEMY_COUNT_X; x++) //敵の移動処理
		{
			if (enemyAlive[y][x] == true)
			{
				if (enemyPosY[y][x] + ENEMY_SIZE_Y > playerPosY)
				{
					PlayerDeathProcess();
					for (int y = 0; y < ENEMY_COUNT_Y; y++)                   //敵の座標をリセット
					{
						for (int x = 0; x < ENEMY_COUNT_X; x++)            
						{
							enemyPosX[y][x] = GET_ENEMY_POS_X(x);
							enemyPosY[y][x] = GET_ENEMY_POS_Y(y);
						}
					}
					InitShot();   	     	//弾を消す(敵)(自機) 
					return;
				}
			}
		}
	}
	if ((startCounter / (30 - enemySpeed * 3)) % 4 == 0) //敵のアニメーション処理
	{
		enemyAnime = 1;
	}
	if ((startCounter / (30 - enemySpeed * 3)) % 4 == 1)
	{
		enemyAnime = 2;
	}
	if ((startCounter / (30 - enemySpeed * 3)) % 4 == 2)
	{
		enemyAnime = 1;
	}
	if ((startCounter / (30 - enemySpeed * 3)) % 4 == 3)
	{
		enemyAnime = 0;
	}
	if (enemyCount < 21 && enemyCount > 10 )            //敵の数が減るとスピードアップ
	{
		enemySpeed = 2;                                 //敵が20体以下11体以上だとenemySpeed  =  2になる
	}
	if (enemyCount < 11 && enemyCount > 3)
	{
		enemySpeed = 3;                                 //敵が10体以下4体以上だとenemySpeed  =  3になる 
	}
	if (enemyCount < 4)
	{
		enemySpeed = 4;                                 //敵が3体以下だとenemySpeed  =  4になる
	}

	//敵（個体）の処理
	if ((rand() % 600) == 0 && EnemyAlive == false && enemyCount > 0)   //ランダムの確率でUFOが出現
	{
		EnemyPosX = GAME_SCREEN_SIZE_X - ENEMY_SIZE_X;
		EnemyPosY = 0;
		EnemyAlive = true;
	}
	if (EnemyAlive == true)
	{
		if (EnemyMove == MOVE_LEFT)
		{
			EnemyPosX -= 3;
		}
		else
		{
			EnemyPosX += 3;
		}
		if (EnemyPosX < 0)
		{
			EnemyMove = MOVE_RIGHT;
			Enemydir = DIR_RIGHT;
		}
		if (EnemyPosX > GAME_SCREEN_SIZE_X - ENEMY_SIZE_X)
		{
			EnemyMove = MOVE_LEFT;
			Enemydir = DIR_LEFT;
		}
	}
	else
	{
		EnemyPosX = -40;
		EnemyPosY = -40;
	}
	CheckEnemyMoveLR();  //敵の左右チェック関数
}

void Score(void)   //スコアの処理
{
	if (score > SCORE_MAX)   //スコアのカンスト防止処理
	{
		score = SCORE_MAX;
	}
	else
	{
		score = score;
	}
	//score = (score > SCORE_MAX) ? SCORE_MAX : score;
	if (score >= highScore) //ハイスコア更新の時よ
	{
		highScore = score;
		newRecord = true;
	}
	if (scoreAlive == true) //スコアの表示
	{
		if (scoreTime <= SCORE_TIME)
		{
			scoreTime++;
		}
		else
		{
			scoreAlive = false;
			scoreTime = 0;
		}
	}
	if (ScoreAlive == true) //スコア(ボーナス)の表示
	{
		if (ScoreTime <= SCORE_TIME)
		{
			ScoreTime++;
		}
		else
		{
			ScoreAlive = false;
			ScoreTime = 0;
		}
	}
}

void Draw(void)   //絵画処理
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	DrawBox(GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_SIZE_X + GAME_SCREEN_X, GAME_SCREEN_SIZE_Y + GAME_SCREEN_Y, GetColor(40, 40, 40), true);
	//背景の画像をゲーム画面の大きさにあわせる。
	DrawExtendGraph(bgPosX1 + GAME_SCREEN_X, GAME_SCREEN_Y, bgPosX1 + GAME_SCREEN_SIZE_X + GAME_SCREEN_X, GAME_SCREEN_SIZE_Y + GAME_SCREEN_Y, bgImage, true);  
	DrawExtendGraph(bgPosX2 + GAME_SCREEN_X, GAME_SCREEN_Y, bgPosX2 + GAME_SCREEN_SIZE_X + GAME_SCREEN_X, GAME_SCREEN_SIZE_Y + GAME_SCREEN_Y, bgImage, true);
	DrawBox(0, GAME_SCREEN_Y, GAME_SCREEN_X, GAME_SCREEN_SIZE_Y + GAME_SCREEN_Y, GetColor(0, 0, 0), true);
	DrawBox(GAME_SCREEN_SIZE_X + GAME_SCREEN_X, GAME_SCREEN_Y, SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y + GAME_SCREEN_Y, GetColor(0, 0, 0), true);
	for (int y = 0; y < ENEMY_COUNT_Y; y++)
	{
		for (int x = 0; x < ENEMY_COUNT_X; x++)
		{
			if (enemyAlive[y][x] == true)
			{
				DrawGraph(enemyPosX[y][x] + GAME_SCREEN_X, enemyPosY[y][x] + GAME_SCREEN_Y, enemyImage[y % (ENEMY_TYPE_MAX - 1)][enemydir][enemyAnime], true);
			}
		}
	}
	if (EnemyAlive == true)
	{
		DrawGraph(EnemyPosX + GAME_SCREEN_X, EnemyPosY + GAME_SCREEN_Y, enemyImage[ENEMY_TYPE_UFO][Enemydir][ANIME], true);
	}
	if (pShotAlive == true)
	{
		DrawGraph(pShotPosX + GAME_SCREEN_X, pShotPosY + GAME_SCREEN_Y, pShotImage, true);
	}
	for (int c = 0; c < ENEMY_COUNT_Y; c++)
	{
		for (int d = 0; d < ENEMY_COUNT_X; d++)
		{
			if (eShotAlive[c][d] == true)
			{
				DrawGraph(eShotPosX[c][d] + GAME_SCREEN_X, eShotPosY[c][d] + GAME_SCREEN_Y, eShotImage, true);
			}
		}
	}

	if (Male == true)
	{
		if (playerAlive == true)
		{
			DrawGraph(GAME_SCREEN_X + playerPosX, GAME_SCREEN_Y + playerPosY, playerImage1[playerdir][playerAnime], true);
			for (int p = 0; p < playerLife - 1; p++)
			{
				DrawGraph(GAME_SCREEN_SIZE_X + GAME_SCREEN_X + PLAYER_SIZE_X * (p % 3), (SCREEN_SIZE_Y - 90) + (PLAYER_SIZE_Y * (p / 3)), playerImage1[DIR_DOWN][ANIME], true);
			}
		}
	}
	if (Female == true)
	{
		if (playerAlive == true)
		{
			DrawGraph(GAME_SCREEN_X + playerPosX, GAME_SCREEN_Y + playerPosY, playerImage2[playerdir][playerAnime], true);
			for (int p = 0; p < playerLife - 1; p++)
			{
				DrawGraph(GAME_SCREEN_SIZE_X + GAME_SCREEN_X + PLAYER_SIZE_X * (p % 3), (SCREEN_SIZE_Y - 90) + (PLAYER_SIZE_Y * (p / 3)), playerImage2[DIR_DOWN][ANIME], true);
			}
		}
	}
	//DrawLine(GAME_SCREEN_SIZE_X + GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_X, GAME_SCREEN_SIZE_Y + GAME_SCREEN_Y, GetColor(255, 255, 255), true);
	//DrawLine(GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_SIZE_X + GAME_SCREEN_X, GAME_SCREEN_SIZE_Y + GAME_SCREEN_Y, GetColor(255, 255, 255), true);
	SetFontSize(20); //文字の大きさの設定
	font = GetDrawFormatStringWidth("%d", score);
	fonthigh = GetDrawFormatStringWidth("%d", highScore);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "gameCounter = %d", gameCounter);
	DrawString(GAME_SCREEN_SIZE_X + GAME_SCREEN_X, GAME_SCREEN_Y + 60, "スコア", GetColor(255, 0, 0));
	DrawString(GAME_SCREEN_SIZE_X + GAME_SCREEN_X, GAME_SCREEN_Y, "ハイスコア", GetColor(255, 0, 0));
	DrawFormatString(SCREEN_SIZE_X - font, GAME_SCREEN_Y + 60 , GetColor(255, 0, 0), "\n%d", score);
	DrawFormatString(SCREEN_SIZE_X - fonthigh, GAME_SCREEN_Y, GetColor(255, 0, 0), "\n%d", highScore);
	if (scoreAlive == true)
	{
		DrawFormatString(GAME_SCREEN_X + scorePosX, GAME_SCREEN_Y + scorePosY, GetColor(0, 0, 255), "%d", ENEMY_POINT);
	}
	if (ScoreAlive == true)
	{
		DrawFormatString(GAME_SCREEN_X + ScorePosX, GAME_SCREEN_Y + ScorePosY, GetColor(255, 255, 0), "%d", ENEMY_POINT * ENEMY_BONUS);
	}
	DrawFormatString(SCREEN_SIZE_X - 60, SCREEN_SIZE_Y - 120, GetColor(255, 0, 0), "残機%d", playerLife);
	DrawFormatString(0, 0, GetColor(0, 255, 0), "\nplayer座標\n  %d %d", playerPosX, playerPosY);
	DrawFormatString(110, 0, GetColor(0, 255, 0), "\n残り\n  %d", enemyCount);
	if (startCounter <= 100)
	{
		DrawTurnGraph(playerPosX + GAME_SCREEN_X - PLAYER_SIZE_Y - 30, playerPosY + GAME_SCREEN_Y, ArrowLRImage, true);
		DrawGraph(playerPosX + GAME_SCREEN_X + PLAYER_SIZE_X + 30, playerPosY + GAME_SCREEN_Y, ArrowLRImage, true);
		DrawGraph(playerPosX + GAME_SCREEN_X, playerPosY + GAME_SCREEN_Y - PLAYER_SIZE_Y - 20, ArrowUPImgae, true);
	}
	if (enemyCount <= 0)
	{
		SetFontSize(60);
		DrawString((GAME_SCREEN_SIZE_X + GAME_SCREEN_X) / 2 - 40, (GAME_SCREEN_Y + GAME_SCREEN_SIZE_Y) / 2, "1000",GetColor(255, 255, 255));
		SetFontSize(20);
	}
	startCounter++;
	_dbgAddDraw();
	ScreenFlip();         //裏画面を表画面にコピー
}

void BgMove(void)
{
	bgPosX1 += 0.5;                     //背景を右にスクロール
	bgPosX2 += 0.5;
	if (bgPosX1 >= GAME_SCREEN_SIZE_X)  //背景が端っこまで行ったら左のほうへ動かす。
	{
		bgPosX1 = -GAME_SCREEN_SIZE_X;
	}
	if (bgPosX2 >= GAME_SCREEN_SIZE_X)
	{
		bgPosX2 = -GAME_SCREEN_SIZE_X;
	}
}

void Gamestart(void)      //スタート画面処理
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1.5f, en * (gameCounter % 360), sunImage, true);
	if (CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_D) || pushA == true)  //Aを押してるときキャラ（女）に設定(このときDを押しても反応しない)
	{
		DrawCircle((SCREEN_SIZE_X / 3) + (PLAYER_SIZE_X / 2), (SCREEN_SIZE_Y / 2) + (PLAYER_SIZE_Y / 2), (PLAYER_SIZE_X + PLAYER_SIZE_Y) / 4 + 2, GetColor(0, 200, 0), 0);    // キャラクターの周りに円を描く
		pushA = true;
		pushD = false;
		Female = true;
		Male = false;
	}
	if (CheckHitKey(KEY_INPUT_D) && !CheckHitKey(KEY_INPUT_A) || pushD == true) //Dを押してるときキャラ（男）に設定(このときAを押しても反応しない)
	{
		DrawCircle((SCREEN_SIZE_X / 1.5) + (PLAYER_SIZE_X / 2), (SCREEN_SIZE_Y / 2) + (PLAYER_SIZE_Y / 2), (PLAYER_SIZE_X + PLAYER_SIZE_Y) / 4 + 2, GetColor(0, 200, 0), 0);  //キャラクターの周りに円を描く
		pushA = false;
		pushD = true;
		Female = false;
		Male = true;
	}
	if ((gameCounter / 20) % 4 == 0) //キャラクターのアニメーション処理
	{
		ANIME = 1;
	}
	if ((gameCounter / 20) % 4 == 1)
	{
		ANIME = 2;
	}
	if ((gameCounter / 20) % 4 == 2)
	{
		ANIME = 1;
	}
	if ((gameCounter / 20) % 4 == 3)
	{
		ANIME = 0;
	}
	SetFontSize(20);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "gameCounter = %d",gameCounter);
	SetFontSize(16);
	DrawGraph((SCREEN_SIZE_X - TITLE_SIZE_X) / 2, 0, backImage, true);
	DrawGraph(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2, playerImage2[DIR_DOWN][ANIME], true);
	DrawGraph(SCREEN_SIZE_X / 1.5, SCREEN_SIZE_Y / 2, playerImage1[DIR_DOWN][ANIME], true);
	DrawString(SCREEN_SIZE_X / 3, (SCREEN_SIZE_Y / 2) - 20, "Aを押せ", GetColor(255, 255, 0));
	DrawString(SCREEN_SIZE_X / 1.5, (SCREEN_SIZE_Y / 2) - 20, "Dを押せ", GetColor(255, 255, 0));
	if ((gameCounter / 30) % 2 == 0)	//ゲームが始まって0.5秒経過したら矢印を消す
	{
		DrawString(SCREEN_SIZE_X / 2 - 30, (SCREEN_SIZE_Y / 2) + 60, "←　→\n 移動\n\n SPACE\nショット", GetColor(200, 0, 100));
		SetFontSize(30);
		DrawString(SCREEN_SIZE_X / 2 - 80, (SCREEN_SIZE_Y - 30) - 60, "spaceキーで\n スタート", GetColor(255, 255, 0));
	}
	if (CheckHitKey(KEY_INPUT_SPACE) && Female == false && Male == false)
	{
		SetFontSize(40);
		DrawString(SCREEN_SIZE_X / 2 - 300, (SCREEN_SIZE_Y / 2) - 70, "キャラクターを選択してください！", GetColor(200, 0, 0));
	}
	if (spaceKeyTriggerKeyDown == 1 && (Female == true || Male == true))
	{
		SetFontSize(20);
		sceneID = SCENE_ID_GAME;
	}
	_dbgAddDraw();
	ScreenFlip();         //裏画面を表画面にコピー
}

void Gamescene(void)
{
	//------------メイン処理
	Enemy();    //敵の処理
	Player();   //プレイヤーの処理
	PShot();    //pショットの処理
	EShot();    //eショットの処理
	HitCheck(); //あたり判定処理
	Score();    //スコア処理
	BgMove();   //背景のスクロール処理
	Draw();     //描画処理
	if (enemyCount <= 0)
	{
		Gameclear();
	}
}

void Gameclear(void)  //ゲームクリア処理
{
	clearCounter++;
	if (clearCounter == 1)            //ゲームクリアしてから一回だけ処理する
	{
		PlaySoundMem(win_se, DX_PLAYTYPE_BACK);
		EnemyAlive = false;
		score += 1000;
	}
	if (clearCounter == 180)   //ゲームクリアしてから３秒経過したらリセットする
	{
		for (int y = 0; y < ENEMY_COUNT_Y; y++)
		{
			for (int x = 0; x < ENEMY_COUNT_X; x++)
			{
				enemyPosX[y][x] = GET_ENEMY_POS_X(x);
				enemyPosY[y][x] = GET_ENEMY_POS_Y(y);
				enemyAlive[y][x] = true;
			}
		}
		enemydir = DIR_RIGHT;
		enemyMoveFlagX = MOVE_RIGHT;
		enemyMoveMode = MOVE_MODE_LR;
		enemySpeed = 1;
		clearCounter = 0;
		enemyCount = ENEMY_COUNT_X * ENEMY_COUNT_Y;
	}
}

void Gameover(void)  //ゲームオーバー処理
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	DrawGraph((SCREEN_SIZE_X - GAMEOVER_SIZE_X) / 2, (SCREEN_SIZE_Y - GAMEOVER_SIZE_Y) / 2 - 30, game_overImage, true);
	if ((gameCounter / 30) % 2 == 0)     //ちかちか表示
	{
		DrawString(SCREEN_SIZE_X / 2 - 30, SCREEN_SIZE_Y / 2 + 50, "GIVE UP?\n Escキー", GetColor(255, 255, 255));
		DrawString(SCREEN_SIZE_X / 2 - 60, SCREEN_SIZE_Y / 2 + 100, "NEVER GIVE UP?\n   SPACEキー", GetColor(255, 255, 255));
	}
	if (newRecord == false)           //新記録達成処理
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 60, SCREEN_SIZE_Y / 2 + 160, GetColor(35, 75, 85), "score = %d", score);
		DrawFormatString(SCREEN_SIZE_X / 2 - 80, SCREEN_SIZE_Y / 2 + 160, GetColor(35, 75, 85), "\nhighScore = %d", highScore);
	}
	else
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 60, SCREEN_SIZE_Y / 2 + 160, GetColor(255, 0, 0), "score = %d", score);
		DrawFormatString(SCREEN_SIZE_X / 2 - 80, SCREEN_SIZE_Y / 2 + 160, GetColor(255, 0, 0), "\nhighScore = %d", highScore);
		DrawString(SCREEN_SIZE_X / 2 - 80, SCREEN_SIZE_Y / 2 + 160, "\n\n ハイスコア更新！", GetColor(255, 0, 0));
	}
	DrawFormatString(0, 0, GetColor(255, 255, 255), "gameCounter = %d", gameCounter);
	if (spaceKeyTriggerKeyDown == 1)
	{
		sceneID = SCENE_ID_INIT;     //初期化シーンからのタイトルシーンに戻る
	}
	_dbgAddDraw();
	ScreenFlip();         //裏画面を表画面にコピー
}

void Player(void)  //プレイヤーの処理
{
	if (CheckHitKey(KEY_INPUT_LEFT)) //右移動（プレイヤー）
	{
		if (0 < playerPosX)
		{
			playerPosX -= playerSpeed;
			Pushtime++;
			playerdir = DIR_LEFT;
		}
		else
		{
			playerPosX = 0;
		}
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) //左移動（プレイヤー）
	{
		if (GAME_SCREEN_SIZE_X > playerPosX + PLAYER_SIZE_X)
		{
			playerPosX += playerSpeed;
			Pushtime++;
			playerdir = DIR_RIGHT;
		}
		else
		{
			playerPosX = GAME_SCREEN_SIZE_X - PLAYER_SIZE_X;
		}
	}
	if ((Pushtime / 10) % 4 == 0)  //アニメションの処理
	{
		playerAnime = 1;
	}
	if ((Pushtime / 10) % 4 == 1)
	{
		playerAnime = 2;
	}
	if ((Pushtime / 10) % 4 == 2)
	{
		playerAnime = 1;
	}
	if ((Pushtime / 10) % 4 == 3)
	{
		playerAnime = 0;
	}
	if ((gameCounter / 20) % 4 == 0) //キャラクターのアニメーション処理
	{
		ANIME = 1;
	}
	if ((gameCounter / 20) % 4 == 1)
	{
		ANIME = 2;
	}
	if ((gameCounter / 20) % 4 == 2)
	{
		ANIME = 1;
	}
	if ((gameCounter / 20) % 4 == 3)
	{
		ANIME = 0;
	}
}

void PlayerDeathProcess(void) //プレイヤーがやられたときの処理
{
	playerLife--;
	playerPosX = (GAME_SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	playerPosY = GAME_SCREEN_SIZE_Y - PLAYER_SIZE_Y;
	if (Female == true)
	{
		PlaySoundMem(player_se2, DX_PLAYTYPE_BACK);
	}
	if (Male == true)
	{
		PlaySoundMem(player_se1, DX_PLAYTYPE_BACK);
	}
	if (playerLife <= 0) //ザ★エンドってね、はい、お疲れさまでしたってね。の処理
	{
		playerAlive = false;
		sceneID = SCENE_ID_LOSE;
	}
	for (int c = 0; c < ENEMY_COUNT_Y; c++)
	{
		for (int d = 0; d < ENEMY_COUNT_X; d++)
		{
			eShotPosX[c][d] = -100;
			eShotPosY[c][d] = -100;
			eShotAlive[c][d] = false;
		}
	}
}

void HitCheck(void)   //当たり判定
{
	for (int c = 0; c < ENEMY_COUNT_Y; c++)
	{
		for (int d = 0; d < ENEMY_COUNT_X; d++)
		{
			if (eShotPosX[c][d] + E_SHOT_SIZE_X > playerPosX &&   //弾の右と自機の左
				eShotPosX[c][d] < playerPosX + PLAYER_SIZE_X &&   //自機の右と弾の左
				eShotPosY[c][d] + E_SHOT_SIZE_Y > playerPosY &&   //自機の上と弾の下
				eShotPosY[c][d] < playerPosY + PLAYER_SIZE_Y &&   //弾の上と自機の下
				eShotAlive[c][d] == true && playerAlive == true)
			{
				pShotAlive = false;
				PlayerDeathProcess();
			}
		}
	}
	for (int y = 0; y < ENEMY_COUNT_Y; y++)
	{
		for (int x = 0; x < ENEMY_COUNT_X; x++)
		{
			if (enemyPosX[y][x] + ENEMY_SIZE_X > pShotPosX  &&  //敵の右と弾の左
				enemyPosX[y][x] < pShotPosX + P_SHOT_SIZE_X &&  //弾の右と敵の左
				enemyPosY[y][x] + ENEMY_SIZE_Y > pShotPosY  &&  //弾の上と敵の下
				enemyPosY[y][x] < pShotPosY + P_SHOT_SIZE_Y &&  //敵の上と弾の下
				enemyAlive[y][x] == true && pShotAlive == true) //敵が生きてるとき
			{
				scorePosX = enemyPosX[y][x];
				scorePosY = enemyPosY[y][x];
				pShotAlive = false;
				enemyAlive[y][x] = false;
				enemyCount--;
				scoreAlive = true;
				score += ENEMY_POINT;
				scoreTime = 0;
				PlaySoundMem(enemy_se, DX_PLAYTYPE_BACK);
			}
		}
	} 
	if (EnemyPosX + ENEMY_SIZE_X > pShotPosX &&   //敵の右と弾の左
		EnemyPosX < pShotPosX + P_SHOT_SIZE_X &&  //弾の右と敵の左
		EnemyPosY + ENEMY_SIZE_Y > pShotPosY &&   //弾の上と敵の下
		EnemyPosY < pShotPosY + P_SHOT_SIZE_Y &&  //敵の上と弾の下
		EnemyAlive == true && pShotAlive == true) //敵が生きてるとき
	{
		ScorePosX = EnemyPosX;
		ScorePosY = EnemyPosY;
		pShotAlive = false;
		EnemyAlive = false;
		score += ENEMY_POINT * ENEMY_BONUS;
		ScoreAlive = true;
		ScoreTime = 0;
		PlaySoundMem(Enemy_se, DX_PLAYTYPE_BACK);
	}
}

void PShot(void) //弾(P)の処理
{
	if (playerAlive == true)
	{
		if (enemyCount > 0)
		{
			if (pShotAlive == false && spaceKeyTriggerKeyDown == 1)
			{
				pShotPosX = playerPosX + (PLAYER_SIZE_X - P_SHOT_SIZE_X) / 2;
				pShotPosY = playerPosY;
				pShotAlive = true;
				playerdir = DIR_UP;
			}
			if (pShotAlive == true)
			{
				pShotPosY -= pShotSpeed;
				if (pShotPosY <= 0)
				{
					pShotAlive = false;
				}
			}
			
		}
	}
}

void EShot(void)  //弾(E)の処理
{
	for (int c = 0; c < ENEMY_COUNT_Y; c++)
	{
		for (int d = 0; d < ENEMY_COUNT_X; d++)
		{
			if (eShotAlive[c][d] == false && enemyAlive[c][d] == true && rand() % (801 - enemySpeed * 200) == 0)  //ランダムで球が撃たれる
			{
				eShotPosX[c][d] = enemyPosX[c][d] + (ENEMY_SIZE_X - E_SHOT_SIZE_X) / 2;
				eShotPosY[c][d] = enemyPosY[c][d];
				eShotAlive[c][d] = true;
			}
			if (eShotAlive[c][d] == true)
			{
				eShotPosY[c][d] += eShotSpeed;
				if (eShotPosY[c][d] >= GAME_SCREEN_SIZE_Y - E_SHOT_SIZE_Y)
				{
					eShotAlive[c][d] = false;
				}
			}
		}
	}
}

void InitShot(void)  //初期化処理(ゲーム)
{
	pShotAlive = false;
	enemyMoveFlagX = MOVE_RIGHT;
	enemydir = DIR_RIGHT;
	for (int c = 0; c < ENEMY_COUNT_Y; c++)
	{
		for (int d = 0; d < ENEMY_COUNT_X; d++)
		{
			eShotPosX[c][d] = -100;
			eShotPosY[c][d] = -100;
			eShotAlive[c][d] = false;
		}
	}
}

void CheckEnemyMoveLR(void)   //敵の左右移動モードチェック処理
{
	for (int Y = 0; Y < ENEMY_COUNT_Y; Y++)
	{
		for (int X = 0; X < ENEMY_COUNT_X; X++)
		{
			if (enemyAlive[Y][X] == true)
			{
				if (enemyMoveFlagX == MOVE_RIGHT)
				{
					if (enemyPosX[Y][X] >= GAME_SCREEN_SIZE_X  - ENEMY_SIZE_X)
					{
						//右端に到達したとき
						enemyMoveFlagX = MOVE_LEFT;
						enemyMoveMode = MOVE_MODE_DOWN;
						enemydir = DIR_LEFT;
						return;
					}
				}
				else
				{
					if (enemyPosX[Y][X] <= 0)
					{
						//左端に到達したとき
						enemyMoveFlagX = MOVE_RIGHT;
						enemyMoveMode = MOVE_MODE_DOWN;
						enemydir = DIR_RIGHT;
						return;
					}
				}
			}
		}
	}
}     

void InitScene(void)
{
	//初期化処理
	GameInit();
	sceneID = SCENE_ID_TITLE;
}

bool GameInit(void)
{
	//システムの初期化
	spaceKeyBack = 0;
	spaceKeyTriggerKeyDown = 0;
	spaceKeyTriggerKeyUp = 0;
	startCounter = 0;
	clearCounter = 0;
	Female = false;
	Male = false;
	pushA = false;
	pushD = false;
	enemyCount = ENEMY_COUNT_X * ENEMY_COUNT_Y;
	playerLife = PLAYER_LIFE;

	//プレイヤーの初期化
	playerPosX = (GAME_SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;    //やられた時
	playerPosY = GAME_SCREEN_SIZE_Y - PLAYER_SIZE_Y;          //やられた時
	playerSpeed = 3;
	playerAlive = true;
	playerAnime = 1;
	playerdir = DIR_DOWN;   //やられた時
	Pushtime = 0;

	//敵の初期化
	for (int y = 0; y < ENEMY_COUNT_Y; y++)
	{
		for (int x = 0; x < ENEMY_COUNT_X; x++)
		{
			enemyPosX[y][x] = GET_ENEMY_POS_X(x);
			enemyPosY[y][x] = GET_ENEMY_POS_Y(y);
			enemyAlive[y][x] = true;
		}
	}
	EnemyPosX = -10;
	EnemyPosY = -10;
	EnemyAlive = false;
	enemySpeed = 1;
	playerAnime = 1;
	EnemyMove = MOVE_LEFT;
	enemyMoveFlagX = MOVE_RIGHT;
	enemyMoveMode = MOVE_MODE_LR;
	enemydir = DIR_RIGHT;
	Enemydir = DIR_LEFT;

	//弾（P）の初期化
	pShotPosX = -100;
	pShotPosY = -100;
	pShotSpeed = 9;
	pShotAlive = false;

	//弾（E）の初期化
	for (int c = 0; c < ENEMY_COUNT_Y; c++)
	{
		for (int d = 0; d < ENEMY_COUNT_X; d++)
		{
			eShotPosX[c][d] = -100;
			eShotPosY[c][d] = -100;
			eShotAlive[c][d] = false;
		}
	}
	eShotSpeed = 3;

	//得点の初期化
	score = 0;
	scoreAlive = false;
	scorePosX = -10;
	scorePosY = -10;
	ScoreAlive = false;
	ScorePosX = -10;
	ScorePosY = -10;
	font = 0;
	newRecord = false;
	scoreTime = 0;            //スコア(団体)の表示時間の初期化(N/60秒)
	ScoreTime = 0;            //スコア(個体)の表示時間の初期化(N/60秒)

	return true;
}

bool SysInit(void)  //プロトタイプ宣伝
{
	//-----------------システム処理
	SetWindowText("課題2_2016198_筒井  杏二");
	//システム処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return false;
	}
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 225);
	srand((unsigned int)time(NULL));
	//画像の読み込み
	//太陽画像の読み込み
	if ((sunImage = LoadGraph("image/sun.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//背景画像の読み込み
	if ((bgImage = LoadGraph("image/World.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//タイトル画像の読み込み
	if ((backImage = LoadGraph("image/TitleLogo2.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//ゲームオーバーの画像の読み込み
	if ((game_overImage = LoadGraph("image/GameOver.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//矢印LR画像の読み込み
	if ((ArrowLRImage = LoadGraph("image/arrowR.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//矢印UP画像の読み込み
	if ((ArrowUPImgae = LoadGraph("image/arrowW.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//自機の弾の画像の読み込み
	if ((pShotImage = LoadGraph("image/pshot.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//敵の弾の読み込み
	if ((eShotImage = LoadGraph("image/eshot.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//プレイヤー（男）の画像の読み込み
	if (LoadDivGraph(
		"image/Male 05-1.png",
		DIR_MAX * ANIM_MAX,
		ANIM_MAX,
		DIR_MAX,
		PLAYER_SIZE_X,
		PLAYER_SIZE_Y,
		&playerImage1[0][0]) == -1)
	{
		TRACE("読み込み失敗");
	    return  false;
	}
	//プレイヤー（女）の画像の読み込み
	if (LoadDivGraph(
		"image/Female 05-2.png",
		DIR_MAX * ANIM_MAX,
		ANIM_MAX,
		DIR_MAX,
		PLAYER_SIZE_X,
		PLAYER_SIZE_Y,
		&playerImage2[0][0]) == -1)
	{
		TRACE("読み込み失敗");
		return  false;
	}
	//敵の画像の読み込み
	const char* enemyFileName[ENEMY_TYPE_MAX] = {
		"image/Enemy 15-1.png",
		"image/Enemy 15-6.png",
		"image/Enemy 15-5.png",
		"image/Enemy 15-4.png",
		"image/Enemy 15-3.png",
		"image/Enemy 15-2.png",
		"image/Enemy 09-1.png"
	};
	//効果音の読み込み
	//弾がプレイヤー（男）に当たった時の効果音の読み込み
	if ((player_se1 = LoadSoundMem("music/se_male.wav")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//弾がプレイヤー（女）に当たった時の効果音の読み込み
	if ((player_se2 = LoadSoundMem("music/se_female.wav")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//弾が敵(団体)に当たった時の効果音の読み込み
	if ((enemy_se = LoadSoundMem("music/se_teki.wav")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//弾が敵(個体)に当たった時の効果音の読み込み
	if ((Enemy_se = LoadSoundMem("music/se_ufo.wav")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//敵が全滅したときの効果音の読み込み
	if ((win_se = LoadSoundMem("music/se_win.wav")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	//敵の画像の読み込み                                                                                                                                  
	for (int j = 0; j < ENEMY_TYPE_MAX; j++) 
	{
		if (LoadDivGraph(
			enemyFileName[j],
			ANIM_MAX * DIR_MAX,
			ANIM_MAX,
			DIR_MAX,
			ENEMY_SIZE_X,
			ENEMY_SIZE_Y,
			&enemyImage[j][0][0]) == -1)
		{
			TRACE("読み込み失敗");
			return false;
		}
	}
	en = PI / 45;                                      //回転速度
	gameCounter = 0;                                   //ゲームカウンターの初期化
	sceneID = SCENE_ID_INIT;                           //シーンの初期化
	highScore = 1000;                                  //ハイスコアの初期化
	fonthigh = 0;                                      //ハイスコアサイズの初期化
	bgPosX1 = 0;                                       //背景座標X1の初期化
	bgPosX2 = -GAME_SCREEN_SIZE_X;                     //背景座標X2の初期化
	return true;
}
