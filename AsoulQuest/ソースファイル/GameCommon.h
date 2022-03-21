#pragma once 

//�}�b�v�̃`�b�v��
#define MAP_X 50
#define MAP_Y 50

//�}�b�v�̃`�b�v�T�C�Y
#define CHIP_SIZE_X 32
#define CHIP_SIZE_Y 32

//�G�̐�
#define ENEMY_COUNT 10

//�e�̐�
#define SHOT_COUNT 40

//�X�R�A�̐�
#define SCORE_COUNT 10

//�A�C�e���̐�
#define ITEM_COUNT 10

//�����̐�
#define BLAST_COUNT 10

//�L�����N�^�[�̃��C�t�ő�l
#define LIFE_COUNT 100


//�L�����N�^�[�̌���
enum class DIR {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX,
};

//�G�̎�ފǗ��p
enum ENEMY_TYPE {
	ENEMY_TYPE_SLIME,
	ENEMY_TYPE_BEE,
	ENEMY_TYPE_FLAME,
	ENEMY_TYPE_R_DRAGON,
	ENEMY_TYPE_B_DRAGON,
	ENEMY_TYPE_BOSS,
	ENEMY_TYPE_MAX
};
