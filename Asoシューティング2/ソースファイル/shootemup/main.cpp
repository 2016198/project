#include<DxLib.h>
#include<cmath>
#include <memory>
#include "HomingShot.h"
#include "Geometry.h"

///当たり判定関数
///@param posA Aの座標
///@param radiusA Aの半径
///@param posB Bの座標
///@param radiusB Bの半径
bool IsHit(const Position2& posA, float radiusA, const Position2& posB,  float radiusB) {
	//当たり判定を実装してください
	return false;
}

using namespace std;//ヘッダーではあんまり使わないほうが良い

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	ChangeWindowMode(true);
	SetMainWindowText("2016198_筒井杏二");
	if (DxLib_Init() != 0) {
		return -1;
	}

	//背景用
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/bullet.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);

	int arrowH = LoadGraph("img/arrow.png");
	int blastH = LoadGraph("img/blast.png");

	struct Bullet {
		Position2 pos;//座標
		Vector2 vel;//速度
		bool isActive = false;//生きてるか～？
	};

	//弾の半径
	float bulletRadius = 5.0f;

	//自機の半径
	float playerRadius = 10.0f;

	//適当に256個くらい作っとく
	Bullet bullets[256];

	HomingShot homingShots[20] = {};//プレイヤーのホーミング弾
	for (auto& shot : homingShots) {
		shot.trail.SetHandle(arrowH);
	}

	Position2 enemypos(320,25);//敵座標
	Position2 copypos;
	Position2 playerpos(320, 400);//自機座標

	unsigned int frame = 0;//フレーム管理用

	char keystate[256] = {};
	char lastKeyState[256] = {};
	bool isDebugMode = false;
	bool isRightHoming = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;
	int speed = 0, add = 1;
	int life = 255,wait = 60;
	bool game = false;
	bool IsRighting = false;
	constexpr float homingShotSpeed = 10.0f;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);

		GetHitKeyStateAll(keystate);
		if (game == true)
		{
			isDebugMode = keystate[KEY_INPUT_P];

			//背景
			DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
			bgidx = (bgidx + 1) % 32;

			//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			skyy = (skyy + 1) % 480;
			skyy2 = (skyy2 + 2) % 480;
			DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
			DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
			DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
			DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);


			//プレイヤー
			if (keystate[KEY_INPUT_RIGHT]) {
				playerpos.x = min(640, playerpos.x + 4);
			}
			else if (keystate[KEY_INPUT_LEFT]) {
				playerpos.x = max(0, playerpos.x - 4);
			}
			if (keystate[KEY_INPUT_UP]) {
				playerpos.y = max(0, playerpos.y - 4);
			}
			else if (keystate[KEY_INPUT_DOWN]) {
				playerpos.y = min(480, playerpos.y + 4);
			}
			if (keystate[KEY_INPUT_Z] && !lastKeyState[KEY_INPUT_Z]) {
				//ホーミング弾発射！
				//DrawString(0, 0, "発射", 0x000000);
				int count = 0;
				for (auto& hs : homingShots)
				{
					if (!hs.isActive)
					{
						hs.isActive = true;
						hs.pos = playerpos;
						hs.vel = { count == 0 ? homingShotSpeed : -homingShotSpeed , homingShotSpeed };
						hs.vel.Normalize();
						hs.vel *= homingShotSpeed;
						isRightHoming = !isRightHoming;
						if (++count > 1) {
							break;
						}
					}
				}
			}

			//プレイヤーのホーミング弾描画
			for (auto& pshot : homingShots)
			{
				if (!pshot.isActive)continue;
				if (frame % 2 == 0) {
					pshot.trail.Update();
				}
				pshot.pos += pshot.vel;
				pshot.trail.Draw();
				/*for (int i = 1; i < 5; ++i) {
					auto tallPos = pshot.pos - pshot.vel * static_cast<float>(i);
					auto thickness = static_cast<float>(6 - i);
					DrawLineAA(pshot.pos.x, pshot.pos.y,
						tallPos.x, tallPos.y,
						0xff0000, thickness * 4.0f);
				}*/
				//出来がイイゾ～これ
				//pshot.vel = (pshot.vel + (enemypos - pshot.pos).Normalized()).Normalized() * homingShotSpeed;

				////敵へのベクトル、および今の速度ベクトルの正規化
				auto nVelocity = pshot.vel.Normalized();
				auto nToEnemy = (enemypos - pshot.pos).Normalized();
				auto dot = Dot(nVelocity, nToEnemy);	//cosθが出る
				auto angle = acos(dot);		//角度が出る(0を中心とした線対称)
				angle = std::fminf(angle, DX_PI_F / 48.0f);
				float sign = Cross(nVelocity, nToEnemy) > 0.0f ? 1.0f : -1.0f;
				angle = atan2(pshot.vel.y, pshot.vel.x) + angle * sign;
				pshot.vel = Vector2(cos(angle), sin(angle)) * homingShotSpeed;

				DrawCircleAA(pshot.pos.x, pshot.pos.y,
					8.0f, 16, 0xff00ff);

				//敵に当たったら
					//弾を消す
				if (/*pshot.pos.x + 16 < 0 || pshot.pos.x - 16 > 640 ||
					pshot.pos.y + 24 < 0 || pshot.pos.y - 24 > 480 ||*/
					(enemypos - pshot.pos).SQMagnitude() < 810.0f) {
					pshot.isActive = false;
					pshot.trail.Clear();
					life -= 9;
				}
			}
			if (isDebugMode) {
				DrawCircleAA(enemypos.x, enemypos.y, 30.0f, 16, 0x00ff00, false);
			}

			int pidx = (frame / 4 % 2) * 5 + 3;
			DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], true);
			if (isDebugMode) {
				//自機の本体(当たり判定)
				DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
			}

			//弾発射
			if (frame % 12 == 0) {
				for (auto& b : bullets) {
					if (!b.isActive) {
						//b.pos = enemypos;
						//b.vel = Vector2(0, 5);
						//b.isActive = true;
						break;
					}
				}
			}

			//弾の更新および表示
			for (auto& b : bullets) {
				if (!b.isActive) {
					continue;
				}

				//弾の現在座標に弾の現在速度を加算してください

				float angle = 0.0f;
				//弾の角度をatan2で計算してください。angleに値を入れるんだよオゥ

				DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, angle, bulletH, true);

				if (isDebugMode) {
					//弾の本体(当たり判定)
					DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
				}
				//弾を殺す
				if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
					b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
					b.isActive = false;
				}

				//あたり！
				//↓のIsHitは実装を書いてません。自分で書いてください。
				if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
					//当たった反応を書いてください。
				}
			}

			//敵の表示
			enemypos.x = abs((int)((speed + 320) % 1280) - 640);
			int eidx = (frame / 4 % 2);
			SetDrawBright(255, life, life);
			if (life > 0)
			{
				DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx], true);
			}
			else
			{
				wait--;
			}
			SetDrawBright(255,255,255);

			if (isDebugMode) {
				//敵の本体(当たり判定)
				DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
			}

			auto drawCall = GetDrawCallCount();
			auto fps = GetFPS();
			DrawFormatString(30, 100, 0x000000, "DrawCall = %d", drawCall);
			DrawFormatString(31, 101, 0xffffff, "DrawCall = %d", drawCall);
			DrawFormatString(30, 140, 0x000000, "FPS = %f", fps);
			DrawFormatString(31, 141, 0xffffff, "FPS = %f", fps);
			if (life <= 0)
			{
				DrawRotaGraph(copypos.x, copypos.y, 0.1, 0.0, blastH, true);
			}
			else
			{
				copypos = enemypos;
			}
			if (wait <= 0)
			{
				wait = 60;
				life = 255;
				add += 3;
			}
			++frame;
			speed += add;
			copy(begin(keystate), end(keystate), begin(lastKeyState));//keystateの情報をlastkeystaetにコピー
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawExtendString(120, 180, 2.0, 2.0, "シューティングゲーム", 0xffffff);
			DrawExtendString(120, 180, 2.0, 2.0, "\nスペースキーでスタート", 0xffffff);
			DrawExtendString(150, 30, 1.0, 1.0, "          Zキーで発射", 0xffffff);

			if (keystate[KEY_INPUT_SPACE])
			{
				//PlayMusic("img/bgm.wav", DX_PLAYTYPE_LOOP);
				game = true;
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			}
		}
		ScreenFlip();
	}
	DxLib::InitGraph();
	DxLib::DxLib_End();

	return 0;
}