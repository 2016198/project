#pragma once

//�萔��`
/*---------------------------------*/
#define SCREEN_SIZE_X 600     //��ʂ̉��T�C�Y
#define SCREEN_SIZE_Y 480     //��ʂ̏c�T�C�Y

//�v���g�^�C�v��`
enum SCENE_ID {
	TITLE_SCENE,
	GAME_SCENE,
	GAME_OVER_SCENE,
	GAME_CLEAR_SCENE,
	MAX_SCENE
};

void KeyCheck(void);
