#pragma once

//�萔��`
//�X�N���[���T�C�Y
#define SCREEN_SIZE_X 768
#define SCREEN_SIZE_Y 480

//�}�b�v�`�b�v�̃T�C�Y
#define CHIP_SIZE_X 32
#define CHIP_SIZE_Y 32

//�}�b�v�`�b�v�̐�
#define MAP_X 24
#define MAP_Y 14

//���t�g�̃T�C�Y
#define LIFT_SIZE_X 120
#define LIFT_SIZE_Y 16

enum class DIR	//�L�����N�^�[�̌���
{
	RIGHT,
	LEFT,
	TOP,
	BOTTOM,
	MAX
};

enum class PLAYER_TYPE //�v���C���[�̎��
{
	PLAYER1,
	PLAYER2,
	MAX
};
