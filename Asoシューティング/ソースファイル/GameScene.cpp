#include "GameScene.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool GameScene::Init(void)
{
	//�e����������
	gamecounter = 0;
	push = 0;
	itemCount = 0;
	playerInit.x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	playerInit.y = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
	for (int s = 0; s < SHOT_MAX; s++)
	{
		shotAdd[s].x = 0;
		shotAdd[s].y = 0;
		shotAdd[s].X = 0;
		shotAdd[s].Y = 0;
		shotAdd[s].Xx = 0;
		shotAdd[s].Yy = 0;
	}
	if (!player2.Init(playerInit)) return false;
	if (!enemy2.Init()) return false;
	if (!boss.Init()) return false;
	if (!item2.Init()) return false;
	for (int a = 0; a < 3; a++)
	{
		for (int s = 0; s < SHOT_MAX; s++)
		{
			if (!shot2[s][a].Init()) return false;
		}
	}
	for (int s = 0; s < SHOT_MAX; s++)
	{
		if (!eshot[s].Init()) return false;
	}
	if (!bg2.Init()) return false;
	for (int s = 0; s < BLAST_MAX; s++)
	{
		if (!blast2[s].Init()) return false;
	}
	if (!lifeP.Init()) return false;
	for (int m = 0; m < FONT_MAX; m++)
	{
		if (!score[m].Init()) return false;
	}
	return true;
}

void GameScene::UpDate(void)
{
	//�e�탁�C������
	gamecounter++;
	player2.Update();
	enemy2.UpDate(boss.GetAlive(),boss.IsHunt());
	boss.UpDate();
	item2.UpDate();

	for (int s = 0; s < BLAST_MAX; s++)
	{
		blast2[s].UpDate();
	}

	for (int m = 0; m < FONT_MAX; m++)
	{
		score[m].UpDate();
	}

	bg2.UpDate();

	if (player2.IsShot())
	{
		//�@shot2.Setup(player2.pos.x, player2.pos.y);

		//�AVector2 playerPos;
		//playerPos = player2.GetPos();
		//shot2.Setup(playerPos.x, playerPos.y);
		for (int s = 0; s < SHOT_MAX; s++)
		{
			if (!shot2[s][0].GetAlive() && push == 0)
			{
				shot2[s][0].Setup(player2.GetPos());
				break;
			}
		}

		if (getItem == true)
		{
			for (int s = 0; s < SHOT_MAX; s++)
			{
				if (!shot2[s][1].GetAlive() && push == 0)
				{
					shot2[s][1].Setup(player2.GetPos());
					break;
				}
			}
			for (int s = 0; s < SHOT_MAX; s++)
			{
				if (!shot2[s][2].GetAlive() && push == 0)
				{
					shot2[s][2].Setup(player2.GetPos());
					break;
				}
			}
		}
	}

	if (enemy2.IsShot())          //�G���e�𔭎˂�����
	{
		for (int s = 0; s < SHOT_MAX; s++)
		{
			if (!eshot[s].GetAlive())  
			{
				pPos = player2.GetPos();   
				ePos = enemy2.GetPos();
				eshot[s].Setup(enemy2.GetPos());  //�G�̍��W��G�̃V���b�g�ɗ^����
				shotAdd[s].X = (pPos.x - ePos.x); //���@�̍��WX�|�G�̍��WX
				shotAdd[s].Y = (pPos.y - ePos.y); //���@�̍��WY�|�G�̍��WY
				if (shotAdd[s].X < 0)             //���Z���ʂ��Βl�ɂ���
				{
					shotAdd2[s].X = -shotAdd[s].X;
				}
				else
				{
					shotAdd2[s].X = shotAdd[s].X;
				}
				if (shotAdd[s].Y < 0)
				{
					shotAdd2[s].Y = -shotAdd[s].Y;
				}
				else
				{
					shotAdd2[s].Y = shotAdd[s].Y;
				}
				if (shotAdd[s].X + shotAdd[s].Y < 0 &&
					shotAdd[s].X * shotAdd[s].Y > 0)   //�����̉��Z���ʂ��}�C�i�X��������
				{
					if (shotAdd2[s].Y >= shotAdd2[s].X) //X��Y�̔䗦
					{
						shotAdd[s].Xx = shotAdd2[s].X / -shotAdd2[s].Y;
						shotAdd[s].Yy = -1;
					}
					else
					{
						shotAdd[s].Yy = shotAdd2[s].Y / -shotAdd2[s].X;
						shotAdd[s].Xx = -1;
					}
				}
				else if(shotAdd[s].X + shotAdd[s].Y > 0 &&
						shotAdd[s].X * shotAdd[s].Y > 0)  //�����̉��Z���ʂ��v���X��������
				{
					if (shotAdd2[s].Y >= shotAdd2[s].X)//X��Y�̔䗦
					{
						shotAdd[s].Xx = shotAdd2[s].X / shotAdd2[s].Y;
						shotAdd[s].Yy = 1;
					}
					else
					{
						shotAdd[s].Yy = shotAdd2[s].Y / shotAdd2[s].X;
						shotAdd[s].Xx = 1;
					}
				}
				else if(shotAdd[s].X > shotAdd[s].Y)  //���Z���ʂ�X���W���v���X�ŁAY���W���}�C�i�X��������
				{
					if (shotAdd2[s].Y >= shotAdd2[s].X)//X��Y�̔䗦
					{
						shotAdd[s].Xx = shotAdd2[s].X / shotAdd2[s].Y;
						shotAdd[s].Yy = -1;
					}
					else
					{
						shotAdd[s].Yy = -shotAdd2[s].Y / shotAdd2[s].X;
						shotAdd[s].Xx = 1;
					}
				}
				else if (shotAdd[s].X < shotAdd[s].Y)  //���Z���ʂ�Y���W���v���X�ŁAX���W���}�C�i�X��������
				{
					if (shotAdd2[s].Y >= shotAdd2[s].X)//X��Y�̔䗦
					{
						shotAdd[s].Xx = shotAdd2[s].X / -shotAdd2[s].Y;
						shotAdd[s].Yy = 1;
					}
					else
					{
						shotAdd[s].Yy = shotAdd2[s].Y / shotAdd2[s].X;
						shotAdd[s].Xx = -1;
					}
				}
				break;
			}
		}
	}

	for (int s = 0; s < SHOT_MAX; s++)
	{
		shot2[s][0].UpDate(0);
		shot2[s][1].UpDate(-3);
		shot2[s][2].UpDate(3);
		eshot[s].UpDate(shotAdd[s]);
	}

	//Player2.shotFlag��true�ɂȂ�����e�𔭎�

	//�e�̈ړ�����
	if (player2.GetAlive() && enemy2.GetAlive())
	{
		pPos = player2.GetPos();
		ePos = enemy2.GetPos();
		if (ePos.x < pPos.x + PLAYER_SIZE_X &&     //�G�̍��ƃv���C���[�̉E������������
			ePos.x + ENEMY_SIZE_X > pPos.x &&      //�G�̉E�ƃv���C���[�̍�������������
			ePos.y < pPos.y + PLAYER_SIZE_Y &&     //�G�̏�ƃv���C���[�̉�������������
			ePos.y + ENEMY_SIZE_Y > pPos.y)        //�G�̉��ƃv���C���[�̏オ����������
		{
			//TRACE("�Q�[���I�[�o�[\n");
			if (getItem == false)
			{
				player2.DeletePlayer();
			}
			for (int s = 0; s < BLAST_MAX; s++)
			{
				if (!blast2[s].GetAlive())
				{
					blast2[s].Setup(enemy2.GetPos());
					break;
				}
			}
			enemy2.DeleteEnemy();
		}
	}
	for (int s = 0; s < SHOT_MAX; s++)
	{
		if (player2.GetAlive() && eshot[s].GetAlive())
		{
			pPos = player2.GetPos();
			SPos[s] = eshot[s].GetPos();
			if (pPos.y + PLAYER_SIZE_Y >= SPos[s].Y &&    //���@�̉��ƒe�̏オ����������
				pPos.y <= SPos[s].Y + E_SHOT_SIZE_Y &&    //���@�̏�ƒe�̉�������������
				pPos.x <= SPos[s].X + E_SHOT_SIZE_X &&    //���@�̍��ƒe�̉E������������
				pPos.x + PLAYER_SIZE_X >= SPos[s].X)      //���@�̉E�ƒe�̍�������������
			{
				eshot[s].DeleteShot();
				if (getItem == false)
				{
					player2.DeletePlayer();
					for (int s = 0; s < BLAST_MAX; s++)
					{
						if (!blast2[s].GetAlive())
						{
							blast2[s].Setup(player2.GetPos());
							break;
						}
					}
				}
			}
		}
	}

	if (player2.GetAlive() && boss.GetAlive())
	{
		pPos = player2.GetPos();
		bPos = boss.GetPos();
		if (pPos.y + PLAYER_SIZE_Y >= bPos.y &&    //���@�̉���boss�̏オ����������
			pPos.y <= bPos.y + BOSS_SIZE_Y &&      //���@�̏��boss�̉�������������
			pPos.x <= bPos.x + BOSS_SIZE_X &&      //���@�̍���boss�̉E������������
			pPos.x + PLAYER_SIZE_X >= bPos.x)      //���@�̉E��boss�̍�������������
		{
			if (getItem == false)
			{
				player2.DeletePlayer();
				for (int s = 0; s < BLAST_MAX; s++)
				{
					if (!blast2[s].GetAlive())
					{
						blast2[s].Setup(player2.GetPos());
						break;
					}
				}
			}
		}
	}

	for (int s = 0; s < SHOT_MAX; s++)
	{
		for (int a = 0; a < 3; a++)
		{
			if (boss.GetAlive() && shot2[s][a].GetAlive())
			{
				bPos = boss.GetPos();
				sPos[s][a] = shot2[s][a].GetPos();
				if (bPos.y + BOSS_SIZE_Y >= sPos[s][a].y &&   //boss�G�̉��ƒe�̏オ����������
					bPos.y <= sPos[s][a].y + P_SHOT_SIZE_Y && //boss�G�̏�ƒe�̉�������������
					bPos.x <= sPos[s][a].x + P_SHOT_SIZE_X && //boss�G�̍��ƒe�̉E������������
					bPos.x + BOSS_SIZE_X >= sPos[s][a].x)     //boss�G�̉E�ƒe�̍�������������
				{
					shot2[s][a].DeleteShot();
					if (boss.IsStay() == 0)
					{
						fontType = 3;
						for (int m = 0; m < FONT_MAX; m++)  //�X�R�A�̕\��
						{
							if (!score[m].GetAlive())
							{
								score[m].SetUp(boss.GetPos());
								break;
							}
						}
						if (boss.IsHit())
						{
							for (int s = 0; s < BLAST_MAX; s++)
							{
								if (!blast2[s].GetAlive())
								{
									blast2[s].Setup(boss.GetPos());
									break;
								}
							}
							score[0].AddScore(2);
							boss.DeleteBoss();
						}
					}
				}
			}
		}
	}

	if (getItem == true && itemCount <= 180) //�A�C�e���̌p������
	{
		itemCount++;
	}
	else
	{
		getItem = false;
		itemCount = 0;
	}

	for (int s = 0; s < SHOT_MAX; s++)
	{
		for (int a = 0; a < 3; a++)
		{
			if (enemy2.GetAlive() && shot2[s][a].GetAlive())
			{
				ePos = enemy2.GetPos();
				sPos[s][a] = shot2[s][a].GetPos();
				if (ePos.y + ENEMY_SIZE_Y >= sPos[s][a].y &&  //�G�̉��ƒe�̏オ����������
					ePos.y <= sPos[s][a].y + P_SHOT_SIZE_Y && //�G�̏�ƒe�̉�������������
					ePos.x <= sPos[s][a].x + P_SHOT_SIZE_X && //�G�̍��ƒe�̉E������������
					ePos.x + ENEMY_SIZE_X >= sPos[s][a].x)    //�G�̉E�ƒe�̍�������������
				{
					if (rand() % 5 == 0 && !item2.GetAlive() && getItem == false)
					{
						item2.SetItem(enemy2.GetPos());
					}
					TRACE("������\n");
					fontType = 0;
					shot2[s][a].DeleteShot();

					for (int s = 0; s < BLAST_MAX; s++)
					{
						if (!blast2[s].GetAlive())
						{
							blast2[s].Setup(enemy2.GetPos());
							break;
						}
					}
					for (int m = 0; m < FONT_MAX; m++)  //�X�R�A�̕\��
					{
						if (!score[m].GetAlive())
						{
							score[m].SetUp(enemy2.GetPos());
							break;
						}
					}
					score[0].AddScore(fontType);
					enemy2.DeleteEnemy();
				}                                    
			}
		}
	}
	if (player2.GetAlive() && item2.GetAlive())
	{
		iPos = item2.GetPos();
		pPos = player2.GetPos();

		if (iPos.y + ITEM_SIZE_Y >= pPos.y &&      //�A�C�e���̉��Ǝ��@�̏オ����������
			iPos.y <= pPos.y + PLAYER_SIZE_Y &&    //�A�C�e���̏�Ǝ��@�̉�������������
			iPos.x <= pPos.x + PLAYER_SIZE_X &&    //�A�C�e���̍��Ǝ��@�̉E������������
			iPos.x + ITEM_SIZE_Y >= pPos.x)        //�A�C�e���̉E�Ǝ��@�̍�������������
		{
			fontType = 1;
			item2.DeleteItem();
			getItem = true;
			score[0].AddScore(fontType);
			for (int m = 0; m < FONT_MAX; m++)  //�X�R�A�̕\��
			{
				if (!score[m].GetAlive())
				{
					score[m].SetUp(item2.GetPos());
					break;
				}
			}
		}
	}

	if (gamecounter == 800)
	{
		boss.InBoss();
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (push <= SHOT_TIME) //�X�y�[�X�L�[�������Ă鎞��
		{
			push++;
		}
		else
		{
			push = 0;
		}
	}
}

void GameScene::Draw(void)
{
	//�e��`�揈��
	bg2.Draw();
	for (int s = 0; s < SHOT_MAX; s++)
	{
		for (int a = 0; a < 3; a++)
		{
			shot2[s][a].Draw();
		}
		eshot[s].Draw();
	}
	if (getItem == true)
	{
		player2.Drawen();
	}
	player2.Draw();
	enemy2.Draw();
	boss.Draw();
	for (int s = 0; s < BLAST_MAX; s++)
	{
		blast2[s].Draw();
	}
	item2.Draw();
	for (int m = 0; m < FONT_MAX; m++)
	{
		score[m].PointDraw(fontType);
		if (boss.IsHunt())
		{
			score[m].PointDraw(2);
		}
	}
	lifeP.Draw(player2.GetLife());
	score[0].ScoreDraw();
}

bool GameScene::Release(void)
{
	//�e�폜����
	//	Init�Ƃ͔��΂̏��łɏ����Ă���
	if (!lifeP.Release()) return false;
	for (int s = 0; s < BLAST_MAX; s++)
	{
		if (!blast2[s].Release()) return false;
	}
	if (!bg2.Release()) return false;
	for (int s = 0; s < SHOT_MAX; s++)
	{
		if (!eshot[s].Release()) return false;
	}
	for (int a = 0; a < 3; a++)
	{
		for (int s = 0; s < SHOT_MAX; s++)
		{
			if (!shot2[s][a].Release()) return false;
		}
	}
	if (!item2.Release()) return false;
	if (!boss.Release()) return false;
	if (!enemy2.Release()) return false;
	if (!player2.Release()) return false;
	return true;
}

int GameScene::Score(void)
{
	point = score[0].GetScore();
	return point;
}

bool GameScene::GameOver(void)
{
	//�Q�[���I�[�o�[����
	if (player2.Death())
	{
		gamecounter = 0;
		return true;
	}
	return false;

}

bool GameScene::GameClear(void)
{
	//�Q�[���N���A�[����
	if (boss.Death())
	{
		gamecounter = 0;
		return true;
	}
	return false;
}

bool GameScene::GameInit(void)
{
	//�e�Q�[���I�[�o�[���Q�[���N���A�[�ɂȂ��ă��Z�b�g���鏈��
	push = 0;
	playerInit.x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	playerInit.y = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
	if (!player2.GameInit(playerInit)) return false;
	if (!enemy2.GameInit()) return false;
	if (!boss.GameInit()) return false;
	if (!item2.GameInit()) return false;
	for (int a = 0; a < 3; a++)
	{
		for (int s = 0; s < SHOT_MAX; s++)
		{
			if (!shot2[s][a].GameInit()) return false;
		}
	}
	for (int s = 0; s < SHOT_MAX; s++)
	{
		if (!eshot[s].GameInit()) return false;
	}
	if (!bg2.GameInit()) return false;
	for (int s = 0; s < BLAST_MAX; s++)
	{
		if (!blast2[s].GameInit()) return false;
	}
	if (!lifeP.GameInit()) return false;
	for (int m = 0; m < FONT_MAX; m++)
	{
		if (!score[m].GameInit()) return false;
	}
	return true;
}