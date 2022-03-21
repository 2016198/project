/*project2 ����Ǔ�*/

#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include <time.h>
#include "DxLib.h"
#include "main.h"

/**********************  �ϐ���`  ****************************/
//�V�X�e��
SCENE_ID sceneID;                            //�Q�[���̃V�[��
int gameCounter;                             //�Q�[�����[�v�J�E���^
int spaceKeyBack;                            //�X�y�[�X�̂P�t���[���O�̏��
int spaceKeyTriggerKeyDown;                  //�X�y�[�X�L�[�̃g���K�[�i�����ꂽ�Ƃ��j
int spaceKeyTriggerKeyUp;                    //�X�y�[�X�L�[�̃g���K�[�i�b���ꂽ�Ƃ��j
bool Female;                                 //�L�����I���i���j
bool Male;                                   //�L�����I���i�j�j
bool pushA;                                  //A�������ꂽ��
bool pushD;                                  //D�������ꂽ��
int backImage;                               //�O���t�B�b�N�n���h���i�^�C�g���j
int game_overImage;                          //�O���t�B�b�N�n���h���i�Q�[���I�[�o�[�j
int ArrowLRImage;                            //�O���t�B�b�N�n���h��(��󍶉E)
int ArrowUPImgae;                            //�O���t�B�b�N�n���h��(����)
int startCounter;                            //�Q�[�����n�܂��Ă���̌o�ߎ���
int clearCounter;                            //�Q�[���N���A���Ă���̎���
int win_se;                                  //�Q�[���N���A�̌��ʉ��n���h��
int ANIME;                                   //�v���C���[�̃A�j���[�V����(�^�C�g��)
int sunImage;                                //�O���t�B�b�N�n���h��(���z)
double en;                                   //��]�p�ϐ�

//�w�i�֘A
int bgImage;                                 //�O���t�B�b�N�n���h���i�w�i�j
double bgPosX1;                              //�w�i���WX1
double bgPosX2;                              //�w�i���WX2

//�v���C���[�֘A
int playerImage1[DIR_MAX][ANIM_MAX];          //�O���t�B�b�N�n���h���i�j�j
int playerImage2[DIR_MAX][ANIM_MAX];          //�O���t�B�b�N�n���h���i���j
int playerPosX;                              //���@�̍��WX
int playerPosY;                              //���@�̍��WY
int playerSpeed;                             //���@�̈ړ���
bool playerAlive;                            //�����ؖ��i�v���C���[�j
int playerLife;                              //���@�̎c�@
int playerAnime;                             //�v���C���[�̃A�j���[�V����(�Q�[��)
int playerdir;                               //�v���C���[�̌���
int Pushtime;                                //�{�^���J�E���g
int player_se1;                              //���ʉ��n���h��(�j)
int player_se2;                              //���ʉ��n���h��(��)

//�G�֘A
int enemyImage[ENEMY_TYPE_MAX][DIR_MAX][ANIM_MAX];       //�O���t�B�b�N�n���h���i�G�j
int enemyPosX[ENEMY_COUNT_Y][ENEMY_COUNT_X];             //�G(�c��)�̍��WX
int enemyPosY[ENEMY_COUNT_Y][ENEMY_COUNT_X];             //�G(�c��)�̍��WY
int EnemyPosX;                                           //�G(��)�̍��WX
int EnemyPosY;                                           //�G(��)�̍��WY
bool enemyAlive[ENEMY_COUNT_Y][ENEMY_COUNT_X];           //�����ؖ��i�G�i�c�́j�j
bool EnemyAlive;                                         //�����ؖ��i�G�i�́j�j
int enemySpeed;                                          //�G�̈ړ���
int enemyAnime;                                          //�G�̃A�j���[�V����
int enemydir;                                            //�G�̌���(�c��)
int Enemydir;                                            //�G�̌���(��)
int enemyCount;                                          //�G�̎c�萔
int enemy_se;                                            //���ʉ��n���h��(�G�i�c�́j)
int Enemy_se;                                            //���ʉ��n���h��(�G�i�́j)
MOVE_LR EnemyMove;                                       //�G�i�́j�̍��E�ړ��Ǘ�
MOVE_LR enemyMoveFlagX;                                  //�G�i�c�́j�̍��E�ړ��Ǘ�
MOVE_MODE enemyMoveMode;                                 //�G�i�c�́j�̈ړ����[�h�Ǘ�
                                                                                                                                                                               
//�e�֘A�iP�j
int pShotImage;                        //�O���t�B�b�N�n���h��(P�e)
int pShotSpeed;                        //�e�̑����iP�j
int pShotPosX;                         //�e��X�iP�j
int pShotPosY;                         //�e��Y�iP�j
bool pShotAlive;                       //�e�iP�j�̕\���F��\��

//�e�֘A�iE�j
int eShotImage;                                                                  //�O���t�B�b�N�n���h���iE�e�j
int eShotPosX[ENEMY_COUNT_Y][ENEMY_COUNT_X];                                     //�e��X�iE�j
int eShotPosY[ENEMY_COUNT_Y][ENEMY_COUNT_X];                                     //�e��Y�iE�j
int eShotSpeed;                                                                  //�e�̑����iE�j
bool eShotAlive[ENEMY_COUNT_Y][ENEMY_COUNT_X];                                   //�e�iE�j�̕\���F��\��

//���_�֘A
int score;                                                                        //���_
int highScore;                                                                    //�ō����_
int scorePosX;                                                                    //���_(�c��)�\�����WX
int scorePosY;                                                                    //���_(�c��)�\�����WY
bool scoreAlive;                                                                  //���_�i�c�́j�̕\���F��\��
int ScorePosX;                                                                    //���_(��)�\�����WX
int ScorePosY;                                                                    //���_(��)�\�����WY
bool ScoreAlive;                                                                  //���_�i�́j�̕\���F��\��
int scoreTime;                                                                    //�X�R�A�̕\������
int ScoreTime;                                                                    //�X�R�A(�{�[�i�X)�̕\������
int font;                                                                         //�X�R�A�̃T�C�Y
int fonthigh;                                                                     //�n�C�X�R�A�̃T�C�Y
bool newRecord;                                                                   //�n�C�X�R�A���X�V�������̃`�F�b�N

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//����������
	if (SysInit() == false) //�����Ɩ߂�l
	{
		TRACE("���������s");
		return false;
	}
	/*�Q�[�����[�v*/
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		gameCounter++;
		//�G�̕\������
		_dbgStartDraw();
		KeyCheck();              // �L�[�g���K�[�`�F�b�N�̊֐�

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
		//if (sceneID == SCENE_ID_TITLE) //�^�C�g���V�[��
		//{
		//	Gamestart();
		//}
		////�Q�[���V�[��
		//if (sceneID == SCENE_ID_GAME)
		//{
		//	Gamescene();
		//}
		////�Q�[���N���A�V�[��
		//else if (sceneID == SCENE_ID_WIN)
		//{
		//	Gameclear();
		//}
		////�Q�[���I�[�o�[�V�[��
		//else if (sceneID == SCENE_ID_LOSE)
		//{
		//	Gameover();
		//}
	}
	DxLib_End();
	return 0;
}

void KeyCheck(void)   //�L�[�g���K�[�`�F�b�N�̊֐�
{
	if (spaceKeyBack == 0) //�t���C���O�̏��
	{
		TRACE("�O�@off");
	}
	else
	{
		TRACE("�O on");
	}
	if (CheckHitKey(KEY_INPUT_SPACE))  //�t���C����̏��
	{
		TRACE(" ���@on");
		if (CheckHitKey(KEY_INPUT_SPACE) == 1 && spaceKeyBack == 0)  //�g���K�[����
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
		TRACE(" ���@off");
		if (CheckHitKey(KEY_INPUT_SPACE) == 0 && spaceKeyBack == 1)  //�g���K�[����
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

void Enemy(void)  //�G�̏���
{
	if (enemyMoveMode == MOVE_MODE_DOWN)//�G�̏W�c���ړ�����
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
			for (int X = 0; X < ENEMY_COUNT_X; X++) //�G�̈ړ�����
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
		for (int x = 0; x < ENEMY_COUNT_X; x++) //�G�̈ړ�����
		{
			if (enemyAlive[y][x] == true)
			{
				if (enemyPosY[y][x] + ENEMY_SIZE_Y > playerPosY)
				{
					PlayerDeathProcess();
					for (int y = 0; y < ENEMY_COUNT_Y; y++)                   //�G�̍��W�����Z�b�g
					{
						for (int x = 0; x < ENEMY_COUNT_X; x++)            
						{
							enemyPosX[y][x] = GET_ENEMY_POS_X(x);
							enemyPosY[y][x] = GET_ENEMY_POS_Y(y);
						}
					}
					InitShot();   	     	//�e������(�G)(���@) 
					return;
				}
			}
		}
	}
	if ((startCounter / (30 - enemySpeed * 3)) % 4 == 0) //�G�̃A�j���[�V��������
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
	if (enemyCount < 21 && enemyCount > 10 )            //�G�̐�������ƃX�s�[�h�A�b�v
	{
		enemySpeed = 2;                                 //�G��20�̈ȉ�11�̈ȏゾ��enemySpeed  =  2�ɂȂ�
	}
	if (enemyCount < 11 && enemyCount > 3)
	{
		enemySpeed = 3;                                 //�G��10�̈ȉ�4�̈ȏゾ��enemySpeed  =  3�ɂȂ� 
	}
	if (enemyCount < 4)
	{
		enemySpeed = 4;                                 //�G��3�̈ȉ�����enemySpeed  =  4�ɂȂ�
	}

	//�G�i�́j�̏���
	if ((rand() % 600) == 0 && EnemyAlive == false && enemyCount > 0)   //�����_���̊m����UFO���o��
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
	CheckEnemyMoveLR();  //�G�̍��E�`�F�b�N�֐�
}

void Score(void)   //�X�R�A�̏���
{
	if (score > SCORE_MAX)   //�X�R�A�̃J���X�g�h�~����
	{
		score = SCORE_MAX;
	}
	else
	{
		score = score;
	}
	//score = (score > SCORE_MAX) ? SCORE_MAX : score;
	if (score >= highScore) //�n�C�X�R�A�X�V�̎���
	{
		highScore = score;
		newRecord = true;
	}
	if (scoreAlive == true) //�X�R�A�̕\��
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
	if (ScoreAlive == true) //�X�R�A(�{�[�i�X)�̕\��
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

void Draw(void)   //�G�揈��
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	DrawBox(GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_SIZE_X + GAME_SCREEN_X, GAME_SCREEN_SIZE_Y + GAME_SCREEN_Y, GetColor(40, 40, 40), true);
	//�w�i�̉摜���Q�[����ʂ̑傫���ɂ��킹��B
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
	SetFontSize(20); //�����̑傫���̐ݒ�
	font = GetDrawFormatStringWidth("%d", score);
	fonthigh = GetDrawFormatStringWidth("%d", highScore);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "gameCounter = %d", gameCounter);
	DrawString(GAME_SCREEN_SIZE_X + GAME_SCREEN_X, GAME_SCREEN_Y + 60, "�X�R�A", GetColor(255, 0, 0));
	DrawString(GAME_SCREEN_SIZE_X + GAME_SCREEN_X, GAME_SCREEN_Y, "�n�C�X�R�A", GetColor(255, 0, 0));
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
	DrawFormatString(SCREEN_SIZE_X - 60, SCREEN_SIZE_Y - 120, GetColor(255, 0, 0), "�c�@%d", playerLife);
	DrawFormatString(0, 0, GetColor(0, 255, 0), "\nplayer���W\n  %d %d", playerPosX, playerPosY);
	DrawFormatString(110, 0, GetColor(0, 255, 0), "\n�c��\n  %d", enemyCount);
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
	ScreenFlip();         //����ʂ�\��ʂɃR�s�[
}

void BgMove(void)
{
	bgPosX1 += 0.5;                     //�w�i���E�ɃX�N���[��
	bgPosX2 += 0.5;
	if (bgPosX1 >= GAME_SCREEN_SIZE_X)  //�w�i���[�����܂ōs�����獶�̂ق��֓������B
	{
		bgPosX1 = -GAME_SCREEN_SIZE_X;
	}
	if (bgPosX2 >= GAME_SCREEN_SIZE_X)
	{
		bgPosX2 = -GAME_SCREEN_SIZE_X;
	}
}

void Gamestart(void)      //�X�^�[�g��ʏ���
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1.5f, en * (gameCounter % 360), sunImage, true);
	if (CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_D) || pushA == true)  //A�������Ă�Ƃ��L�����i���j�ɐݒ�(���̂Ƃ�D�������Ă��������Ȃ�)
	{
		DrawCircle((SCREEN_SIZE_X / 3) + (PLAYER_SIZE_X / 2), (SCREEN_SIZE_Y / 2) + (PLAYER_SIZE_Y / 2), (PLAYER_SIZE_X + PLAYER_SIZE_Y) / 4 + 2, GetColor(0, 200, 0), 0);    // �L�����N�^�[�̎���ɉ~��`��
		pushA = true;
		pushD = false;
		Female = true;
		Male = false;
	}
	if (CheckHitKey(KEY_INPUT_D) && !CheckHitKey(KEY_INPUT_A) || pushD == true) //D�������Ă�Ƃ��L�����i�j�j�ɐݒ�(���̂Ƃ�A�������Ă��������Ȃ�)
	{
		DrawCircle((SCREEN_SIZE_X / 1.5) + (PLAYER_SIZE_X / 2), (SCREEN_SIZE_Y / 2) + (PLAYER_SIZE_Y / 2), (PLAYER_SIZE_X + PLAYER_SIZE_Y) / 4 + 2, GetColor(0, 200, 0), 0);  //�L�����N�^�[�̎���ɉ~��`��
		pushA = false;
		pushD = true;
		Female = false;
		Male = true;
	}
	if ((gameCounter / 20) % 4 == 0) //�L�����N�^�[�̃A�j���[�V��������
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
	DrawString(SCREEN_SIZE_X / 3, (SCREEN_SIZE_Y / 2) - 20, "A������", GetColor(255, 255, 0));
	DrawString(SCREEN_SIZE_X / 1.5, (SCREEN_SIZE_Y / 2) - 20, "D������", GetColor(255, 255, 0));
	if ((gameCounter / 30) % 2 == 0)	//�Q�[�����n�܂���0.5�b�o�߂������������
	{
		DrawString(SCREEN_SIZE_X / 2 - 30, (SCREEN_SIZE_Y / 2) + 60, "���@��\n �ړ�\n\n SPACE\n�V���b�g", GetColor(200, 0, 100));
		SetFontSize(30);
		DrawString(SCREEN_SIZE_X / 2 - 80, (SCREEN_SIZE_Y - 30) - 60, "space�L�[��\n �X�^�[�g", GetColor(255, 255, 0));
	}
	if (CheckHitKey(KEY_INPUT_SPACE) && Female == false && Male == false)
	{
		SetFontSize(40);
		DrawString(SCREEN_SIZE_X / 2 - 300, (SCREEN_SIZE_Y / 2) - 70, "�L�����N�^�[��I�����Ă��������I", GetColor(200, 0, 0));
	}
	if (spaceKeyTriggerKeyDown == 1 && (Female == true || Male == true))
	{
		SetFontSize(20);
		sceneID = SCENE_ID_GAME;
	}
	_dbgAddDraw();
	ScreenFlip();         //����ʂ�\��ʂɃR�s�[
}

void Gamescene(void)
{
	//------------���C������
	Enemy();    //�G�̏���
	Player();   //�v���C���[�̏���
	PShot();    //p�V���b�g�̏���
	EShot();    //e�V���b�g�̏���
	HitCheck(); //�����蔻�菈��
	Score();    //�X�R�A����
	BgMove();   //�w�i�̃X�N���[������
	Draw();     //�`�揈��
	if (enemyCount <= 0)
	{
		Gameclear();
	}
}

void Gameclear(void)  //�Q�[���N���A����
{
	clearCounter++;
	if (clearCounter == 1)            //�Q�[���N���A���Ă����񂾂���������
	{
		PlaySoundMem(win_se, DX_PLAYTYPE_BACK);
		EnemyAlive = false;
		score += 1000;
	}
	if (clearCounter == 180)   //�Q�[���N���A���Ă���R�b�o�߂����烊�Z�b�g����
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

void Gameover(void)  //�Q�[���I�[�o�[����
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	DrawGraph((SCREEN_SIZE_X - GAMEOVER_SIZE_X) / 2, (SCREEN_SIZE_Y - GAMEOVER_SIZE_Y) / 2 - 30, game_overImage, true);
	if ((gameCounter / 30) % 2 == 0)     //���������\��
	{
		DrawString(SCREEN_SIZE_X / 2 - 30, SCREEN_SIZE_Y / 2 + 50, "GIVE UP?\n Esc�L�[", GetColor(255, 255, 255));
		DrawString(SCREEN_SIZE_X / 2 - 60, SCREEN_SIZE_Y / 2 + 100, "NEVER GIVE UP?\n   SPACE�L�[", GetColor(255, 255, 255));
	}
	if (newRecord == false)           //�V�L�^�B������
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 60, SCREEN_SIZE_Y / 2 + 160, GetColor(35, 75, 85), "score = %d", score);
		DrawFormatString(SCREEN_SIZE_X / 2 - 80, SCREEN_SIZE_Y / 2 + 160, GetColor(35, 75, 85), "\nhighScore = %d", highScore);
	}
	else
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 60, SCREEN_SIZE_Y / 2 + 160, GetColor(255, 0, 0), "score = %d", score);
		DrawFormatString(SCREEN_SIZE_X / 2 - 80, SCREEN_SIZE_Y / 2 + 160, GetColor(255, 0, 0), "\nhighScore = %d", highScore);
		DrawString(SCREEN_SIZE_X / 2 - 80, SCREEN_SIZE_Y / 2 + 160, "\n\n �n�C�X�R�A�X�V�I", GetColor(255, 0, 0));
	}
	DrawFormatString(0, 0, GetColor(255, 255, 255), "gameCounter = %d", gameCounter);
	if (spaceKeyTriggerKeyDown == 1)
	{
		sceneID = SCENE_ID_INIT;     //�������V�[������̃^�C�g���V�[���ɖ߂�
	}
	_dbgAddDraw();
	ScreenFlip();         //����ʂ�\��ʂɃR�s�[
}

void Player(void)  //�v���C���[�̏���
{
	if (CheckHitKey(KEY_INPUT_LEFT)) //�E�ړ��i�v���C���[�j
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
	if (CheckHitKey(KEY_INPUT_RIGHT)) //���ړ��i�v���C���[�j
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
	if ((Pushtime / 10) % 4 == 0)  //�A�j���V�����̏���
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
	if ((gameCounter / 20) % 4 == 0) //�L�����N�^�[�̃A�j���[�V��������
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

void PlayerDeathProcess(void) //�v���C���[�����ꂽ�Ƃ��̏���
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
	if (playerLife <= 0) //�U���G���h���ĂˁA�͂��A����ꂳ�܂ł������ĂˁB�̏���
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

void HitCheck(void)   //�����蔻��
{
	for (int c = 0; c < ENEMY_COUNT_Y; c++)
	{
		for (int d = 0; d < ENEMY_COUNT_X; d++)
		{
			if (eShotPosX[c][d] + E_SHOT_SIZE_X > playerPosX &&   //�e�̉E�Ǝ��@�̍�
				eShotPosX[c][d] < playerPosX + PLAYER_SIZE_X &&   //���@�̉E�ƒe�̍�
				eShotPosY[c][d] + E_SHOT_SIZE_Y > playerPosY &&   //���@�̏�ƒe�̉�
				eShotPosY[c][d] < playerPosY + PLAYER_SIZE_Y &&   //�e�̏�Ǝ��@�̉�
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
			if (enemyPosX[y][x] + ENEMY_SIZE_X > pShotPosX  &&  //�G�̉E�ƒe�̍�
				enemyPosX[y][x] < pShotPosX + P_SHOT_SIZE_X &&  //�e�̉E�ƓG�̍�
				enemyPosY[y][x] + ENEMY_SIZE_Y > pShotPosY  &&  //�e�̏�ƓG�̉�
				enemyPosY[y][x] < pShotPosY + P_SHOT_SIZE_Y &&  //�G�̏�ƒe�̉�
				enemyAlive[y][x] == true && pShotAlive == true) //�G�������Ă�Ƃ�
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
	if (EnemyPosX + ENEMY_SIZE_X > pShotPosX &&   //�G�̉E�ƒe�̍�
		EnemyPosX < pShotPosX + P_SHOT_SIZE_X &&  //�e�̉E�ƓG�̍�
		EnemyPosY + ENEMY_SIZE_Y > pShotPosY &&   //�e�̏�ƓG�̉�
		EnemyPosY < pShotPosY + P_SHOT_SIZE_Y &&  //�G�̏�ƒe�̉�
		EnemyAlive == true && pShotAlive == true) //�G�������Ă�Ƃ�
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

void PShot(void) //�e(P)�̏���
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

void EShot(void)  //�e(E)�̏���
{
	for (int c = 0; c < ENEMY_COUNT_Y; c++)
	{
		for (int d = 0; d < ENEMY_COUNT_X; d++)
		{
			if (eShotAlive[c][d] == false && enemyAlive[c][d] == true && rand() % (801 - enemySpeed * 200) == 0)  //�����_���ŋ����������
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

void InitShot(void)  //����������(�Q�[��)
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

void CheckEnemyMoveLR(void)   //�G�̍��E�ړ����[�h�`�F�b�N����
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
						//�E�[�ɓ��B�����Ƃ�
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
						//���[�ɓ��B�����Ƃ�
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
	//����������
	GameInit();
	sceneID = SCENE_ID_TITLE;
}

bool GameInit(void)
{
	//�V�X�e���̏�����
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

	//�v���C���[�̏�����
	playerPosX = (GAME_SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;    //���ꂽ��
	playerPosY = GAME_SCREEN_SIZE_Y - PLAYER_SIZE_Y;          //���ꂽ��
	playerSpeed = 3;
	playerAlive = true;
	playerAnime = 1;
	playerdir = DIR_DOWN;   //���ꂽ��
	Pushtime = 0;

	//�G�̏�����
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

	//�e�iP�j�̏�����
	pShotPosX = -100;
	pShotPosY = -100;
	pShotSpeed = 9;
	pShotAlive = false;

	//�e�iE�j�̏�����
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

	//���_�̏�����
	score = 0;
	scoreAlive = false;
	scorePosX = -10;
	scorePosY = -10;
	ScoreAlive = false;
	ScorePosX = -10;
	ScorePosY = -10;
	font = 0;
	newRecord = false;
	scoreTime = 0;            //�X�R�A(�c��)�̕\�����Ԃ̏�����(N/60�b)
	ScoreTime = 0;            //�X�R�A(��)�̕\�����Ԃ̏�����(N/60�b)

	return true;
}

bool SysInit(void)  //�v���g�^�C�v��`
{
	//-----------------�V�X�e������
	SetWindowText("�ۑ�2_2016198_����  �Ǔ�");
	//�V�X�e������
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return false;
	}
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 225);
	srand((unsigned int)time(NULL));
	//�摜�̓ǂݍ���
	//���z�摜�̓ǂݍ���
	if ((sunImage = LoadGraph("image/sun.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//�w�i�摜�̓ǂݍ���
	if ((bgImage = LoadGraph("image/World.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//�^�C�g���摜�̓ǂݍ���
	if ((backImage = LoadGraph("image/TitleLogo2.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//�Q�[���I�[�o�[�̉摜�̓ǂݍ���
	if ((game_overImage = LoadGraph("image/GameOver.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//���LR�摜�̓ǂݍ���
	if ((ArrowLRImage = LoadGraph("image/arrowR.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//���UP�摜�̓ǂݍ���
	if ((ArrowUPImgae = LoadGraph("image/arrowW.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//���@�̒e�̉摜�̓ǂݍ���
	if ((pShotImage = LoadGraph("image/pshot.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//�G�̒e�̓ǂݍ���
	if ((eShotImage = LoadGraph("image/eshot.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//�v���C���[�i�j�j�̉摜�̓ǂݍ���
	if (LoadDivGraph(
		"image/Male 05-1.png",
		DIR_MAX * ANIM_MAX,
		ANIM_MAX,
		DIR_MAX,
		PLAYER_SIZE_X,
		PLAYER_SIZE_Y,
		&playerImage1[0][0]) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
	    return  false;
	}
	//�v���C���[�i���j�̉摜�̓ǂݍ���
	if (LoadDivGraph(
		"image/Female 05-2.png",
		DIR_MAX * ANIM_MAX,
		ANIM_MAX,
		DIR_MAX,
		PLAYER_SIZE_X,
		PLAYER_SIZE_Y,
		&playerImage2[0][0]) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return  false;
	}
	//�G�̉摜�̓ǂݍ���
	const char* enemyFileName[ENEMY_TYPE_MAX] = {
		"image/Enemy 15-1.png",
		"image/Enemy 15-6.png",
		"image/Enemy 15-5.png",
		"image/Enemy 15-4.png",
		"image/Enemy 15-3.png",
		"image/Enemy 15-2.png",
		"image/Enemy 09-1.png"
	};
	//���ʉ��̓ǂݍ���
	//�e���v���C���[�i�j�j�ɓ����������̌��ʉ��̓ǂݍ���
	if ((player_se1 = LoadSoundMem("music/se_male.wav")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//�e���v���C���[�i���j�ɓ����������̌��ʉ��̓ǂݍ���
	if ((player_se2 = LoadSoundMem("music/se_female.wav")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//�e���G(�c��)�ɓ����������̌��ʉ��̓ǂݍ���
	if ((enemy_se = LoadSoundMem("music/se_teki.wav")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//�e���G(��)�ɓ����������̌��ʉ��̓ǂݍ���
	if ((Enemy_se = LoadSoundMem("music/se_ufo.wav")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//�G���S�ł����Ƃ��̌��ʉ��̓ǂݍ���
	if ((win_se = LoadSoundMem("music/se_win.wav")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	//�G�̉摜�̓ǂݍ���                                                                                                                                  
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
			TRACE("�ǂݍ��ݎ��s");
			return false;
		}
	}
	en = PI / 45;                                      //��]���x
	gameCounter = 0;                                   //�Q�[���J�E���^�[�̏�����
	sceneID = SCENE_ID_INIT;                           //�V�[���̏�����
	highScore = 1000;                                  //�n�C�X�R�A�̏�����
	fonthigh = 0;                                      //�n�C�X�R�A�T�C�Y�̏�����
	bgPosX1 = 0;                                       //�w�i���WX1�̏�����
	bgPosX2 = -GAME_SCREEN_SIZE_X;                     //�w�i���WX2�̏�����
	return true;
}
