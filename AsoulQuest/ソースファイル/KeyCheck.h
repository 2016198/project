//#pragma once

//��`�̐�`
enum KEY_LIST
{
	//�V�X�e�����̃L�[���
	KEY_SYS_START,
	KEY_SYS_RESET,
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,

	//�v���C���[�P�̃L�[���
	KEY_P1_UP,
	KEY_P1_DOWN,
	KEY_P1_LEFT,
	KEY_P1_RIGHT,
	KEY_P1_A,
	KEY_P1_B,

	//�v���C���[�Q�̃L�[���
	KEY_P2_UP,
	KEY_P2_DOWN,
	KEY_P2_LEFT,
	KEY_P2_RIGHT,
	KEY_P2_A,
	KEY_P2_B,

	//�L�[���X�g�̍ő�l
	KEY_LIST_MAX
};

//�L�[�Ǘ��p�ϐ�
//true : �L�[�������Ă����ԁ@�܂��́@�g���K�[���������Ă�����
//���C++������̂ō��̂Ƃ���Aextrun�Ō��J����]�`
//extern bool KeyOld[KEY_LIST_MAX];          //�P�t���[���O�̃L�[�̏��
extern bool KeyNow[KEY_LIST_MAX];            //���݂̃L�[�̏��
extern bool KeyTrgUp[KEY_LIST_MAX];          //KeyDown�̏��
extern bool KeyTrgDown[KEY_LIST_MAX];        //KeyUp�̏��

//�v���g�^�C�v��`
void KeyInit(void);           //�L�[���̏���������
void CheckKeyList(void);      //�L�[���̍쐬