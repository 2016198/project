#pragma once
#include <DxLib.h>

//�}�b�v�`�b�v�̃T�C�Y
constexpr int CHIP_SIZE_X = 32;
constexpr int CHIP_SIZE_Y = 32;

//��ʃT�C�Y
constexpr int SCREEN_SIZE_X = 640;
constexpr int SCREEN_SIZE_Y = 480;

//�A�j���[�V�����̍ő吔
constexpr int ANIM_MAX = 3;

//�����̊Ǘ��p
enum class DIR {
	DOWN,		//������
	LEFT,		//��
	RIGHT,		//�E
	UP,			//��
	MAX
};
