#include <dxlib.h>
#include <cmath>
#include "Geometry.h"
#include "resource.h"

unsigned int color[2] = {
	0xffffaa,
	0xffaaff
};

int imgX, imgY, offset;

//�q���g�ɂȂ�Ǝv���āA�F�X�Ɗ֐���p�ӂ��Ă���܂���
//�ʂɂ��̊֐����g��Ȃ���΂����Ȃ��킯�ł��A����ɉ���Ȃ���΂����Ȃ��킯�ł�
//����܂���B���C�g���[�V���O���ł��Ă���΍\���܂���B

//���˃x�N�g����Ԃ��֐�
//���˃x�N�g��
//���̕\�ʂ̖@���x�N�g��
//���˃x�N�g��
Vector3 ReflectVector(const Vector3& InVec, const Vector3& N) {
	//���˃x�N�g����R�A���˃x�N�g����I�A�@���x�N�g����N�Ƃ����
	//R=I-2(I�EN)N
	//�������A�@���x�N�g���́u���K���ς݁v�ł��邱��
	//�ۑ�F���˃x�N�g��������Ă�������
	//�������A����Ղ�Dot�֐����g��
	//����ɃX�J���[ * �x�N�g���֐��͂Ȃ�
	//�x�N�g�� * �X�J���[(1����)�̊֐��͂��邽��
	//������������΁A�X�J���[*�x�N�g����
	//�I�y���[�^�[������Ă�����
	auto dot = 2.0f * (Dot(InVec, N));
	Vector3 R = InVec - N * dot;
	return R;
	//return Vector3();
}

float Clamp(float value, float minVal = 0.0f, float maxVal = 1.0f) {
	return min(max(value, minVal), maxVal);
}

///���C(����)�Ƌ��̂̓����蔻��
///@param ray (���_����X�N���[���s�N�Z���ւ̃x�N�g��)
///@param plane ����
///@param t[out] ��_�܂ł̋���(�Q��)
///@hint ���C�͐��K�����ēn���Ă�������
//bool IsHitRayAndObject(const Position3& eye, const Vector3& ray, const Plane& plane, float& t) {
//	//rat��plane.N�����K������Ă�Ƃ���Ɓc�H
//	//�q���g�͓���
//	float dot = Dot(ray, plane.N);
//	bool hit = dot < 0.0f;
//	if (hit) {
//		t = (Dot(eye, plane.N) - plane.distance) / Dot(-ray, plane.N);
//	}
//	return hit;
//}
//
/////���C(����)�Ƌ��̂̓����蔻��
/////@param ray (���_����X�N���[���s�N�Z���ւ̃x�N�g��)
/////@param sphere ��
/////@param t[out] ��_�܂ł̋���(�Q��)
/////@hint ���C�͐��K�����Ƃ����ق����g���₷�����낤
//bool IsHitRayAndObject(const Position3& eye, const Vector3& ray, const Sphere& sphere, float& t) {
//	//���C�����K���ς݂ł���O��Łc
//	
//	//���_���狅�̒��S�ւ̃x�N�g��(����)�����܂�
//	auto center = sphere.pos - eye;
//	//���S���王���ւ̓��ς��Ƃ�܂������x�N�g����
//	auto dot = Dot(center, ray);
//	//�����x�N�g���ƃx�N�g�����������āA���S����̐����������_�����߂܂�
//	auto iray = ray * dot;
//	//��_�܂ł̋���t�����߂�菇
//	//�@�����̒��������߂�
//	auto v = iray - center;
//	//�A�����̒��������a�𒴂��Ă���Ȃ�false��Ԃ�
//	if (Dot(v,v) > sphere.radius * sphere.radius) return false;
//	//�B���a�Ɛ����̒�������A���������낵���Ƃ��납��
//	// ��_�܂ł̋���w�𑪂�(�O���s�̒藝 w^2=r^2-v^2)
//	float w = sqrtf(sphere.radius * sphere.radius - Dot(v,v));
//	//�C�ˉe����-w����_�܂ł̋����ƂȂ�̂ŁA�����
//	// t�ɑ������
//	t = dot - w;
//	//���q���g�@Dot(v,v)�̂悤�ɓ���x�N�g������ς����
//	// �傫���̂Q��ɂȂ�]
//	//return (iray - center).Magnitude() <= sp.radius;
//	return true;
//
//}

typedef Vector3 Color_t;
//using�ł�in����ˁ[�́H

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
		//0�`255����0.0f�`1.0f�֕ύX
		fr = r / 255.0f;
		fg = g / 255.0f;
		fb = b / 255.0f;
		return{ fr, fg, fb };
	}
	else {
		//�A���t�@�l��syamu(0)�Ȃ�Δ���Ԃ�
		return { 0.0f, 0.0f, 1.0f };
	}
}

///���C�g���[�V���O
///@param eye ���_���W
///@param sphere ���I�u�W�F�N�g(���̂��������ɂ���)

void RayTracing(const Position3& eye, const Sphere& sphere, const Plane& plane, const int img) {
	Vector3 lightVec(1, -1, -1); //L:���̕����x�N�g��
	for (int y = 0; y < screen_height; ++y) {//�X�N���[���c����
		for (int x = 0; x < screen_width; ++x) {//�X�N���[��������
			//�@���_�ƃX�N���[�����W���王���x�N�g�������
			Vector3 ray = Position3((float)(x - screen_width / 2), (float)(screen_height / 2 - y), 0.0f) - eye;
			//�A���K�����Ƃ�
			ray.Normalize();
			//�BIsHitRay�֐���True�������甒���h��Ԃ�
			//���h��Ԃ���DrawPixel�Ƃ����֐����g���B
			//Position3  testEye = Position3(x - screen_width / 2, screen_height / 2 - y, eye.z);
			float t = 0.0f;
			//if (IsHitRayAndObject(eye, ray, sphere, t)) {
			Ray rray = { eye, ray };
			Vector3 N = {};
			if (sphere.IshitRay(rray, t, N)) {
				//�܂��e�X�g�Ƃ��āAt�̒l�ŐF(�Z�W)��ς����悤��
				//���Ă݂悤
				//float bright = (400.0f - t) / 100.0f;//���悻0�`1�͈̔͂ɂȂ�
				//bright = Clamp(bright);
				float diffuse = 1.0f;
				//��_�܂ł̋������킩���Ă���̂�
				//�@���x�N�g����N��ray*t-(sp.pos-eye)�ɂȂ�
				//�������AN�͐��K�������Ă�������
				//�@�@���x�N�g��N�����߂܂��傤
				Vector3 N = ray * t - (sphere.pos - eye);
				N.Normalize();
				//�A���C�g�̃x�N�g��L�𐳋K�����Ă����܂��傤
				lightVec.Normalize();
				//�B���邳��N�E(-L)�̓��ςŋ��߂܂�
				//�����̕����x�N�g���́A���ς̍ۂɁA
				//���]���Ă����Ȃ���cos�Ƃ̒l���t�����Ɍ����̂ŁA
				//���ۂɂ͖��邳 = N�E(-L)�Ƃ��܂��傤�B
				constexpr float ambient = 0.2f;
				diffuse = max(Dot(N, -lightVec), ambient);
				//�C�������A�}�C�i�X�ɑΉ����邽�߂�Clamp�֐���
				// �������܂��傤�����ʂ�bright�ɏ�������
				//���Ƃ��Ƃ̋��̂̐F�ɂ����Ă����悤


				diffuse = Clamp(diffuse);
				//float color = 255.0f * bright;
				//DrawPixel(x, y, GetColor((int)color, (int)color, (int)color));

				//�X�y�L�������˂̌v�Z���s��
				//�ŏI�I�Ȍ��ʂɑ����Ă�������
				//�������A�X�y�L�����͊�{�I�ɓ��ˌ���
				//���̂܂ܔ��˂���̂ŐF��t���Ȃ��悤�ɒ��ӂ��܂��傤

				//�@���C�g�Ɩ@��N���甽�˃x�N�g��R�����
				//�AR�Ǝ����t�x�N�g���̓��ς��g��
				//�B�A�̌����ʂ�n�悷��(20�悭�炢)
				//���̌��ʂ��ŏI�I�ȐF�ɑ���(���F)
				//���˃x�N�g��(�������̊֐�)
				//�ЂƂ܂�Phone�̕��@�Ōv�Z
				//auto R = ReflectVector(lightVec,N);
				//auto specular = powf(Clamp(Dot(R, -ray)), 20.0f);

				//Blinn����
				auto H = -(lightVec + ray).Normalized();	//�n�[�t�x�N�g��
				auto specular = pow(Clamp(Dot(H, N)), 50);
				//specular += pow(1.0f - Dot(-ray, N), 2.0f);
				//if (Dot(-ray, N) < 0.4f) { specular = 2.0f; }
				//���_�ɂ��Ē��_

				//�@�����̔��˃x�N�g�������
				Vector3 pos2 = eye + ray * t;
				//�A���̂̏Փˌ�_���n�_�Ƃ���
				Vector3 Rray = ReflectVector(ray, N);
				//�B�@�A�̏�񂩂�܂����C�g���[�X����
				//���C�g���[�X�Ƃ��������Ƃ̓����蔻��
				Color_t floorColor = { 1.0f, 1.0f, 1.0f };
				//if (IsHitRayAndObject(pos2, Rray, plane, t)) {
				Ray pray = {pos2, Rray};
				if (plane.IshitRay(pray, t, N)) {
					//�C���Ɠ������Ă��珰�̐F���擾���Ă���
					floorColor = GetFloorColor(pos2 + Rray * t, img);
				}
				//�D����ꂽ�F�����̐F(�f�B�t���[�Y)�Ə�Z����

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

				//      F            F		16�i��
				// 1  1  1  1   1  1  1  1   2�i��
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
					//����(pos)������̕���������
					//���x�N�g����lightVec�ł����A
					//�����x�N�g���ꍇ�ɂ͋t�x�N�g���ɂȂ�
					//����pos��lightVec�ł܂����C�g���[�V���O
					//���̂Ɠ����蔻����Ƃ�

					//if (IsHitRayAndObject(pos, -lightVec, sphere, t)) {
					Ray rray = {pos, -lightVec};
					if (sphere.IshitRay(rray, t, N)) {
						//���̎��͉e�Ȃ̂ŃJ���[�l(col)��
						//�����ɂ���
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
	SetMainWindowText(L"2016198_����Ǔ�");

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

		//��̍��W�A���́i���a�A���S���W�j
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