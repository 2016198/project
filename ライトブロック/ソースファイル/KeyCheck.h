//#pragma once

//��`�̐錾
enum KEY_LIST			//�L�[�Ǘ����
{
	//�V�X�e���֘A�̃L�[���
	KEY_SYS_START,
	//�}�E�X������
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,

	//�v���C���[1�̃L�[���
	KEY_P1_UP,
	KEY_P1_DOWN,
	KEY_P1_LEFT,
	KEY_P1_RIGHT,
	KEY_P1_A,
	KEY_P1_B,

	//�v���C���[2�̃L�[���
	KEY_P2_UP,
	KEY_P2_DOWN,
	KEY_P2_LEFT,
	KEY_P2_RIGHT,
	KEY_P2_A,
	KEY_P2_B,

	KEY_LIST_MAX

};
//true:�L�[�������Ă����ԁA�܂��̓g���K�[���������Ă�����
extern bool keyOld[KEY_LIST_MAX];			//1�t���[���O�̃L�[���
extern bool keyNew[KEY_LIST_MAX];			//���t���[���̃L�[���
extern bool keyTrgUp[KEY_LIST_MAX];		//KeyDown�g���K�[
extern bool keyTrgDown[KEY_LIST_MAX];		//KeyUp�g���K�[

//�v���g�^�C�v�錾
void KeyInit(void);				//�L�[���̏�����
void CheckKeyList(void);		//�L�[���̍쐬