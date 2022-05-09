#include <dxlib.h>
#include <cmath>
#include "Geometry.h"
#include "resource.h"

unsigned int color[2] = {
	0xffffaa,
	0xffaaff
};

int imgX, imgY, offset;

//ヒントになると思って、色々と関数を用意しておりますが
//別にこの関数を使わなければいけないわけでも、これに沿わなければいけないわけでも
//ありません。レイトレーシングができていれば構いません。

//反射ベクトルを返す関数
//入射ベクトル
//物体表面の法線ベクトル
//反射ベクトル
Vector3 ReflectVector(const Vector3& InVec, const Vector3& N) {
	//反射ベクトルをR、入射ベクトルをI、法線ベクトルをNとすると
	//R=I-2(I・N)N
	//ただし、法線ベクトルは「正規化済み」であること
	//課題：反射ベクトルを作ってください
	//ただし、根遺跡はDot関数を使う
	//さらにスカラー * ベクトル関数はなく
	//ベクトル * スカラー(1次元)の関数はあるため
	//実装したければ、スカラー*ベクトルを
	//オペレーターを作ってもいい
	auto dot = 2.0f * (Dot(InVec, N));
	Vector3 R = InVec - N * dot;
	return R;
	//return Vector3();
}

float Clamp(float value, float minVal = 0.0f, float maxVal = 1.0f) {
	return min(max(value, minVal), maxVal);
}

///レイ(光線)と球体の当たり判定
///@param ray (視点からスクリーンピクセルへのベクトル)
///@param plane 平面
///@param t[out] 交点までの距離(参照)
///@hint レイは正規化して渡してください
//bool IsHitRayAndObject(const Position3& eye, const Vector3& ray, const Plane& plane, float& t) {
//	//ratもplane.Nも正規化されてるとすると…？
//	//ヒントは内積
//	float dot = Dot(ray, plane.N);
//	bool hit = dot < 0.0f;
//	if (hit) {
//		t = (Dot(eye, plane.N) - plane.distance) / Dot(-ray, plane.N);
//	}
//	return hit;
//}
//
/////レイ(光線)と球体の当たり判定
/////@param ray (視点からスクリーンピクセルへのベクトル)
/////@param sphere 球
/////@param t[out] 交点までの距離(参照)
/////@hint レイは正規化しといたほうが使いやすいだろう
//bool IsHitRayAndObject(const Position3& eye, const Vector3& ray, const Sphere& sphere, float& t) {
//	//レイが正規化済みである前提で…
//	
//	//視点から球体中心へのベクトル(視線)を作ります
//	auto center = sphere.pos - eye;
//	//中心から視線への内積をとります＝＞ベクトル長
//	auto dot = Dot(center, ray);
//	//視線ベクトルとベクトル長をかけて、中心からの垂線下した点を求めます
//	auto iray = ray * dot;
//	//交点までの距離tを求める手順
//	//①垂線の長さを求める
//	auto v = iray - center;
//	//②垂線の長さが半径を超えているならfalseを返す
//	if (Dot(v,v) > sphere.radius * sphere.radius) return false;
//	//③半径と垂線の長さから、垂線をおろしたところから
//	// 交点までの距離wを測る(三平行の定理 w^2=r^2-v^2)
//	float w = sqrtf(sphere.radius * sphere.radius - Dot(v,v));
//	//④射影距離-wが交点までの距離となるので、それを
//	// tに代入する
//	t = dot - w;
//	//※ヒント　Dot(v,v)のように同一ベクトルを内積すると
//	// 大きさの２乗になるゾ
//	//return (iray - center).Magnitude() <= sp.radius;
//	return true;
//
//}

typedef Vector3 Color_t;
//usingでもinじゃねーの？

Color_t
GetFloorColor(const Position3& pos, const int img) {

	auto offsetPos = pos;

	offsetPos.x = abs(offsetPos.x);
	offsetPos.z = abs(offsetPos.z);

	offsetPos.x += offset;
	offsetPos.z += offset;

	int r, g, b, a;
	GetPixelSoftImage(img, (int)(offsetPos.x) % imgX, (int)(offsetPos.z) % imgY, &r, &g, &b, &a);
	if (a != 0) {
		float fr, fg, fb;
		//0～255から0.0f～1.0fへ変更
		fr = r / 255.0f;
		fg = g / 255.0f;
		fb = b / 255.0f;
		return{ fr, fg, fb };
	}
	else {
		//アルファ値がsyamu(0)ならば白を返す
		return { 0.0f, 0.0f, 1.0f };
	}
}

///レイトレーシング
///@param eye 視点座標
///@param sphere 球オブジェクト(そのうち複数にする)

void RayTracing(const Position3& eye, const Sphere& sphere, const Plane& plane, const int img) {
	Vector3 lightVec(1, -1, -1); //L:光の方向ベクトル
	for (int y = 0; y < screen_height; ++y) {//スクリーン縦方向
		for (int x = 0; x < screen_width; ++x) {//スクリーン横方向
			//①視点とスクリーン座標から視線ベクトルを作る
			Vector3 ray = Position3((float)(x - screen_width / 2), (float)(screen_height / 2 - y), 0.0f) - eye;
			//②正規化しとく
			ray.Normalize();
			//③IsHitRay関数がTrueだったら白く塗りつぶす
			//※塗りつぶしはDrawPixelという関数を使う。
			//Position3  testEye = Position3(x - screen_width / 2, screen_height / 2 - y, eye.z);
			float t = 0.0f;
			//if (IsHitRayAndObject(eye, ray, sphere, t)) {
			Ray rray = { eye, ray };
			Vector3 N = {};
			if (sphere.IshitRay(rray, t, N)) {
				//まずテストとして、tの値で色(濃淡)を変えれるように
				//してみよう
				//float bright = (400.0f - t) / 100.0f;//およそ0～1の範囲になる
				//bright = Clamp(bright);
				float diffuse = 1.0f;
				//交点までの距離がわかっているので
				//法線ベクトルのNはray*t-(sp.pos-eye)になる
				//ただし、Nは正規化をしておくこと
				//①法線ベクトルNを求めましょう
				Vector3 N = ray * t - (sphere.pos - eye);
				N.Normalize();
				//②ライトのベクトルLを正規化しておきましょう
				lightVec.Normalize();
				//③明るさをN・(-L)の内積で求めます
				//※光の方向ベクトルは、内積の際に、
				//反転しておかないとcosθの値が逆方向に向くので、
				//実際には明るさ = N・(-L)としましょう。
				constexpr float ambient = 0.2f;
				diffuse = max(Dot(N, -lightVec), ambient);
				//④ただし、マイナスに対応するためにClamp関数で
				// 制限しましょう→結果をbrightに書き込む
				//もともとの球体の色にかけてあげよう


				diffuse = Clamp(diffuse);
				//float color = 255.0f * bright;
				//DrawPixel(x, y, GetColor((int)color, (int)color, (int)color));

				//スペキュラ反射の計算を行い
				//最終的な結果に足してください
				//ただし、スペキュラは基本的に入射光を
				//そのまま反射するので色を付けないように注意しましょう

				//①ライトと法線Nから反射ベクトルRを作る
				//②Rと視線逆ベクトルの内積を使う
				//③②の決結果をn乗する(20乗くらい)
				//この結果を最終的な色に足す(白色)
				//反射ベクトル(さっきの関数)
				//ひとまずPhoneの方法で計算
				//auto R = ReflectVector(lightVec,N);
				//auto specular = powf(Clamp(Dot(R, -ray)), 20.0f);

				//Blinnだと
				auto H = -(lightVec + ray).Normalized();	//ハーフベクトル
				auto specular = pow(Clamp(Dot(H, N)), 50);
				//specular += pow(1.0f - Dot(-ray, N), 2.0f);
				//if (Dot(-ray, N) < 0.4f) { specular = 2.0f; }
				//原点にして頂点

				//①視線の反射ベクトルを作る
				Vector3 pos2 = eye + ray * t;
				//②球体の衝突交点を始点とする
				Vector3 Rray = ReflectVector(ray, N);
				//③①②の情報からまたレイトレースする
				//レイトレースというか床との当たり判定
				Color_t floorColor = { 1.0f, 1.0f, 1.0f };
				//if (IsHitRayAndObject(pos2, Rray, plane, t)) {
				Ray pray = {pos2, Rray};
				if (plane.IshitRay(pray, t, N)) {
					//④床と当たってたら床の色を取得しておく
					floorColor = GetFloorColor(pos2 + Rray * t, img);
				}
				//⑤得られた色を球の色(ディフューズ)と乗算する

				Color_t color = { 1.0f,1.0f,1.0f };
				color *= diffuse;
				color *= floorColor;

				auto Red = min(color.x + specular, 1.0f);
				auto Green = min(color.y + specular, 1.0f);
				auto Blue = min(color.z + specular, 1.0f);
				//auto Red = 255 * Clamp(diffuse + specular);
				//auto Green = 255 * Clamp(diffuse + specular);
				//auto Blue = 255 * Clamp(diffuse + specular);

				DrawPixel(x, y, GetColor(Red * 255.0f, Green * 255.0f, Blue * 255.0f));

				//      F            F		16進数
				// 1  1  1  1   1  1  1  1   2進数
				//128 64 32 16  8  4  2  1
				//128 + 64 + 32 + 16 + 8 + 4 + 2 + 1
				//192 + 48 + 12 + 3
				//240 + 15
				//255
			}
			else {
				//if (IsHitRayAndObject(eye, ray, plane, t)) {
				Ray pray = { eye, ray };
				if (plane.IshitRay(pray, t, N)) {
					auto pos = eye + ray * t;

					auto col = GetFloorColor(pos, img);
					//ここ(pos)から光の方向を見る
					//光ベクトルはlightVecですが、
					//光源ベクトル場合には逆ベクトルになる
					//このposとlightVecでまたレイトレーシング
					//球体と当たり判定をとる

					//if (IsHitRayAndObject(pos, -lightVec, sphere, t)) {
					Ray rray = {pos, -lightVec};
					if (sphere.IshitRay(rray, t, N)) {
						//この時は影なのでカラー値(col)を
						//半分にする
						col /= 2.0f;
					}

					col *= 255.0f;

					DrawPixel(x, y, GetColor(col.x, col.y, col.z));
					//pos.x = abs(pos.x);
					//pos.z = abs(pos.z);

					//pos.x += offset;
					//pos.z += offset;

					//int r, g, b, a;
					//GetPixelSoftImage(img, (int)(pos.x) % imgX, (int)(pos.z) % imgY, &r, &g, &b, &a);
					///*if (((int)(pos.x) / 40 + (int)(pos.z) / 40) % 2 == 0) {
					//	DrawPixel(x, y, color[1]);
					//}
					//else {
					//	DrawPixel(x, y, color[0]);
					//}*/
					//if (a != 0) {
					//	DrawPixel(x, y, GetColor(r, g, b));
					//}
					//else {
					//	DrawPixel(x, y, 0xffffff);
					//}
				}
				else {
					if ((x / 40 + y / 40) % 2 == 0) {
						DrawPixel(x, y, GetColor(66, 255, 66));
					}
				}
			}
		}
	}
}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR , _In_ int) {
	SetOutApplicationLogValidFlag(false);
	SetWindowIconID(101);
	ChangeWindowMode(true);
	SetGraphMode(screen_width, screen_height, 32);
	SetMainWindowText(L"2016198_筒井杏二");

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	Sphere sphere = Sphere(100.0f, Position3(0.0f, 0.0f, -100.0f));
	Plane plane = Plane(Vector3(0.0f, 1.0f, 0.0f), -100.0f);

	int image = LoadSoftImage(L"apple.png");
	int screen = MakeScreen(screen_width, screen_height);
	char keyState[256];
	GetSoftImageSize(image, &imgX, &imgY);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawScreen(screen);
		ClearDrawScreen();

		GetHitKeyStateAll(keyState);
		if (keyState[KEY_INPUT_LEFT]) {
			sphere.pos.x -= 5;
		}
		if (keyState[KEY_INPUT_RIGHT]) {
			sphere.pos.x += 5;
		}
		if (keyState[KEY_INPUT_UP]) {
			sphere.pos.y += 5;
		}
		if (keyState[KEY_INPUT_DOWN]) {
			sphere.pos.y -= 5;
		}

		//眼の座標、球体（半径、中心座標）
		RayTracing(Vector3(0, 0, 300), sphere, plane, image);
		DrawFormatString(0, 0, 0xffffff, L"%.2f", GetFPS());

		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawBox(0, 0, screen_width, screen_height, 0xffffff, true);
		SetDrawBlendMode(DX_BLENDMODE_MUL, 0);
		DrawGraph(0, 0, screen, false);
		ScreenFlip();

		auto index = color[0];
		color[0] = color[1];
		color[1] = index;

		offset++;
	}

	DeleteSoftImage(image);
	DxLib_End();
	return 0;
}