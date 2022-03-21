#pragma once
//�萔��`
#define SCREEN_SIZE_X 800                                  //��ʂ̉��T�C�Y
#define SCREEN_SIZE_Y 600                                  //��ʂ̏c�T�C�Y
#define GAME_SCREEN_X 40                                   //�Q�[���̂킭X
#define GAME_SCREEN_Y 75                                   //�Q�[���̂킭Y
#define GAME_SCREEN_SIZE_X 640                             //�Q�[���̉��ʃT�C�YX
#define GAME_SCREEN_SIZE_Y 480                             //�Q�[���̉�ʃT�C�YY
#define ANIM_MAX 3                                         //�A�j���[�V�����̃R�}��
#define PLAYER_SIZE_X 32                                   //���@�̃T�C�YX
#define PLAYER_SIZE_Y 32                                   //���@�̃T�C�YY
#define PLAYER_LIFE 5                                      //���C�t�̐�
#define ENEMY_SIZE_X 32                                    //�G�̃T�C�YX
#define ENEMY_SIZE_Y 32                                    //�G�̃T�C�YY
#define ENEMY_POINT 100                                    //�G��|�������̃|�C���g
#define ENEMY_BONUS 5                                      //UFO��|�������̃|�C���g(ENEMY_POINT �~ ENEMY_BONUS)
#define ENEMY_COUNT_X 8                                    //�G�̐�X
#define ENEMY_COUNT_Y 7                                    //�G�̐�Y
#define P_SHOT_SIZE_X 6                                    //�e�̃T�C�Y��p
#define P_SHOT_SIZE_Y 30                                   //�e�̃T�C�Y�cp
#define E_SHOT_SIZE_X 16                                   //�e�̃T�C�Y��e
#define E_SHOT_SIZE_Y 25                                   //�e�̃T�C�Y�ce
#define SCORE_MAX 9999                                     //�X�R�A�̍ő�l
#define SCORE_TIME 30                                      //�X�R�A�̕\������(N/60�b)
#define TITLE_SIZE_X 423                                   //�^�C�g���̃T�C�YX
#define TITLE_SIZE_Y 198                                   //�^�C�g���̃T�C�YY
#define ARROW_SIZE_X 32                                    //���̃T�C�YX
#define ARROW_SIZE_Y 32                                    //���̃T�C�YY
#define GAMEOVER_SIZE_X 452                                //�Q�[���I�[�o�[�̃T�C�Y
#define GAMEOVER_SIZE_Y 123                                //�Q�[���I�[�o�[�̃T�C�Y
#define GET_ENEMY_POS_Y(y) (ENEMY_SIZE_Y * y * 9 / 7)      //�c�̌���
#define GET_ENEMY_POS_X(x) (ENEMY_SIZE_X * x * 3 / 2)      //���̌���
#define PI  3.1415926535897932384626433832795f	  	       //�~����

enum DIR_ID {
	DIR_DOWN,               //������
	DIR_LEFT,               //������
	DIR_RIGHT,              //�E����
	DIR_UP,                 //�����
	DIR_MAX
};

enum ENEMY_TYPE {           //�G�̎��
	ENEMY_TYPE_1,
	ENEMY_TYPE_2,
	ENEMY_TYPE_3,
	ENEMY_TYPE_4,
	ENEMY_TYPE_5,
	ENEMY_TYPE_6,
	ENEMY_TYPE_UFO,
	ENEMY_TYPE_MAX
};

enum MOVE_LR {                  //�����E��
	MOVE_LEFT,   
	MOVE_RIGHT,  
	MOVE_MAX
};

enum MOVE_MODE {                //�ړ����[�h�����E������
	MOVE_MODE_LR,    
	MOVE_MODE_DOWN,  
	MOVE_MODE_MAX
};

enum SCENE_ID {              //�Q�[���̃V�[��
	SCENE_ID_INIT,
	SCENE_ID_GAME,
	SCENE_ID_TITLE,
	SCENE_ID_LOSE,
	SCENE_ID_MAX
};
                                  //"�߂�l" "���O"("����");
bool SysInit(void);               //�v���g�^�C�v��`bool
bool GameInit(void);               //�Q�[���̏���������
void InitShot(void);              //�e�������֐�
void CheckEnemyMoveLR(void);      //�G�̈ړ����[�h
void Draw(void);                  //��揈��
void Player(void);                //�v���C���[����
void PlayerDeathProcess(void);    //�Q�[���I�[�o�[����
void Enemy(void);                 //�G�̏���
void PShot(void);                 //�e(P)�̏���
void EShot(void);                 //�e(E)�̏���
void HitCheck(void);              //�����蔻��
void Score(void);                 //�X�R�A�̏���
void BgMove(void);                //�w�i�̏���
void Gamestart(void);             //��������
void Gamescene(void);             //�Q�[���̏���
void Gameclear(void);             //�Q�[���N���A�̏���
void Gameover(void);              //�Q�[���I�[�o�[�̏���
void KeyCheck(void);              //�L�[�g���K�[�`�F�b�N�p�֐�
void InitScene(void);             //�������V�[��