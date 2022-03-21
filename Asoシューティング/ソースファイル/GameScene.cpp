#include "GameScene.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool GameScene::Init(void)
{
	//各初期化処理
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
	//各種メイン処理
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
		//①shot2.Setup(player2.pos.x, player2.pos.y);

		//②Vector2 playerPos;
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

	if (enemy2.IsShot())          //敵が弾を発射したら
	{
		for (int s = 0; s < SHOT_MAX; s++)
		{
			if (!eshot[s].GetAlive())  
			{
				pPos = player2.GetPos();   
				ePos = enemy2.GetPos();
				eshot[s].Setup(enemy2.GetPos());  //敵の座標を敵のショットに与える
				shotAdd[s].X = (pPos.x - ePos.x); //自機の座標X－敵の座標X
				shotAdd[s].Y = (pPos.y - ePos.y); //自機の座標Y－敵の座標Y
				if (shotAdd[s].X < 0)             //演算結果を絶対値にする
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
					shotAdd[s].X * shotAdd[s].Y > 0)   //両方の演算結果がマイナスだったら
				{
					if (shotAdd2[s].Y >= shotAdd2[s].X) //XとYの比率
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
						shotAdd[s].X * shotAdd[s].Y > 0)  //両方の演算結果がプラスだったら
				{
					if (shotAdd2[s].Y >= shotAdd2[s].X)//XとYの比率
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
				else if(shotAdd[s].X > shotAdd[s].Y)  //演算結果のX座標がプラスで、Y座標がマイナスだったら
				{
					if (shotAdd2[s].Y >= shotAdd2[s].X)//XとYの比率
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
				else if (shotAdd[s].X < shotAdd[s].Y)  //演算結果のY座標がプラスで、X座標がマイナスだったら
				{
					if (shotAdd2[s].Y >= shotAdd2[s].X)//XとYの比率
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

	//Player2.shotFlagがtrueになったら弾を発射

	//弾の移動処理
	if (player2.GetAlive() && enemy2.GetAlive())
	{
		pPos = player2.GetPos();
		ePos = enemy2.GetPos();
		if (ePos.x < pPos.x + PLAYER_SIZE_X &&     //敵の左とプレイヤーの右が当たったら
			ePos.x + ENEMY_SIZE_X > pPos.x &&      //敵の右とプレイヤーの左が当たったら
			ePos.y < pPos.y + PLAYER_SIZE_Y &&     //敵の上とプレイヤーの下が当たったら
			ePos.y + ENEMY_SIZE_Y > pPos.y)        //敵の下とプレイヤーの上が当たったら
		{
			//TRACE("ゲームオーバー\n");
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
			if (pPos.y + PLAYER_SIZE_Y >= SPos[s].Y &&    //自機の下と弾の上が当たったら
				pPos.y <= SPos[s].Y + E_SHOT_SIZE_Y &&    //自機の上と弾の下が当たったら
				pPos.x <= SPos[s].X + E_SHOT_SIZE_X &&    //自機の左と弾の右が当たったら
				pPos.x + PLAYER_SIZE_X >= SPos[s].X)      //自機の右と弾の左が当たったら
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
		if (pPos.y + PLAYER_SIZE_Y >= bPos.y &&    //自機の下とbossの上が当たったら
			pPos.y <= bPos.y + BOSS_SIZE_Y &&      //自機の上とbossの下が当たったら
			pPos.x <= bPos.x + BOSS_SIZE_X &&      //自機の左とbossの右が当たったら
			pPos.x + PLAYER_SIZE_X >= bPos.x)      //自機の右とbossの左が当たったら
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
				if (bPos.y + BOSS_SIZE_Y >= sPos[s][a].y &&   //boss敵の下と弾の上が当たったら
					bPos.y <= sPos[s][a].y + P_SHOT_SIZE_Y && //boss敵の上と弾の下が当たったら
					bPos.x <= sPos[s][a].x + P_SHOT_SIZE_X && //boss敵の左と弾の右が当たったら
					bPos.x + BOSS_SIZE_X >= sPos[s][a].x)     //boss敵の右と弾の左が当たったら
				{
					shot2[s][a].DeleteShot();
					if (boss.IsStay() == 0)
					{
						fontType = 3;
						for (int m = 0; m < FONT_MAX; m++)  //スコアの表示
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

	if (getItem == true && itemCount <= 180) //アイテムの継続時間
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
				if (ePos.y + ENEMY_SIZE_Y >= sPos[s][a].y &&  //敵の下と弾の上が当たったら
					ePos.y <= sPos[s][a].y + P_SHOT_SIZE_Y && //敵の上と弾の下が当たったら
					ePos.x <= sPos[s][a].x + P_SHOT_SIZE_X && //敵の左と弾の右が当たったら
					ePos.x + ENEMY_SIZE_X >= sPos[s][a].x)    //敵の右と弾の左が当たったら
				{
					if (rand() % 5 == 0 && !item2.GetAlive() && getItem == false)
					{
						item2.SetItem(enemy2.GetPos());
					}
					TRACE("当たり\n");
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
					for (int m = 0; m < FONT_MAX; m++)  //スコアの表示
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

		if (iPos.y + ITEM_SIZE_Y >= pPos.y &&      //アイテムの下と自機の上が当たったら
			iPos.y <= pPos.y + PLAYER_SIZE_Y &&    //アイテムの上と自機の下があたったら
			iPos.x <= pPos.x + PLAYER_SIZE_X &&    //アイテムの左と自機の右が当たったら
			iPos.x + ITEM_SIZE_Y >= pPos.x)        //アイテムの右と自機の左が当たったら
		{
			fontType = 1;
			item2.DeleteItem();
			getItem = true;
			score[0].AddScore(fontType);
			for (int m = 0; m < FONT_MAX; m++)  //スコアの表示
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
		if (push <= SHOT_TIME) //スペースキーを押してる時間
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
	//各種描画処理
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
	//各削除処理
	//	Initとは反対の順版に消していく
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
	//ゲームオーバー条件
	if (player2.Death())
	{
		gamecounter = 0;
		return true;
	}
	return false;

}

bool GameScene::GameClear(void)
{
	//ゲームクリアー条件
	if (boss.Death())
	{
		gamecounter = 0;
		return true;
	}
	return false;
}

bool GameScene::GameInit(void)
{
	//各ゲームオーバーかゲームクリアーになってリセットする処理
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