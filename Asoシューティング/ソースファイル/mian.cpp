//2016198_����Ǔ�

#include "DxLib.h"
#include "time.h"
#include "main.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "GameClear.h"
#include "_debug/_DebugDispOut.h"
#include "_debug/_DebugConOut.h"

//�ϐ��̐�`
SCENE_ID sceneID;                             //�V�[���̐�`
bool enterKeyBack;                            //�X�y�[�X�̂P�t���[���O�̏��
bool enterKeyTriggerKeyDown;                  //�G���^�[�L�[�̃g���K�[�i�����ꂽ�Ƃ��j
bool enterKeyTriggerKeyUp;                    //�G���^�[�L�[�̃g���K�[�i�b���ꂽ�Ƃ��j

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//----------------�V�X�e������
	SetWindowText("�ۑ�3_2016198_����Ǔ�");
 	//�V�X�e������
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);           //640x480�h�b�g65536�F���[�h�̐ݒ�
	ChangeWindowMode(true);                                   //true:window   false:�t���X�N���[��
	if (DxLib_Init() == -1)                                   //Dx���C�u�����[�̏�����
	{
		return -1;
	}
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 225);

	//�����̏�����
	srand((unsigned int)time(NULL));              

	//�e�평��������
	sceneID = TITLE_SCENE;

	//�C���X�^���X�̐���
	GameScene gamescene;
	TitleScene titlescene;
	GameOverScene gameover;
	GameClear gameclear;

	//�C���X�^���X�̏�����
	if (!gamescene.Init()) return -1;
	if (!titlescene.Init()) return -1;
	if (!gameover.Init()) return -1;
	if (!gameclear.Init()) return -1;

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		KeyCheck();                                     //�g���K�[�`�F�b�N
		_dbgStartDraw();
		SetDrawScreen(DX_SCREEN_BACK);                  //�o�b�N�o�b�t�@�ɐݒ�
		ClsDrawScreen();                                //��ʏ���
		if (enterKeyTriggerKeyDown == true)
		{
			if (sceneID == TITLE_SCENE)
			{
				sceneID = GAME_SCENE;
			}
			if (sceneID == GAME_OVER_SCENE)
			{
				sceneID = TITLE_SCENE;
			}
			if (sceneID == GAME_CLEAR_SCENE)
			{
				gameclear.Reset();
				if (!gamescene.GameInit()) return -1;           //�Q�[���N���A�̏���
				if (!titlescene.GameInit()) return -1;
				sceneID = TITLE_SCENE;
			}
		}
		if (gamescene.GameOver())
		{
			sceneID = GAME_OVER_SCENE;                      
			if (!gamescene.GameInit()) return -1;           //�Q�[���I�[�o�[��̏���
			if (!titlescene.GameInit()) return -1;
		}
		if (gamescene.GameClear())
		{
			sceneID = GAME_CLEAR_SCENE;
		}
		switch (sceneID)
		{
		case TITLE_SCENE:
			titlescene.UpDate();                            //�^�C�g���V�[���X�V����
			titlescene.Draw();                              //�^�C�g���V�[���`�揈��
			break;
		case GAME_SCENE:
			gamescene.UpDate();                             //�Q�[���V�[���X�V����
			gamescene.Draw();                               //�Q�[���V�[���`�揈��
			break;
		case GAME_OVER_SCENE:
			gameover.UpDate();                              //�Q�[���I�[�o�[�V�[���X�V����
			gameover.Draw();                                //�Q�[���I�[�o�[�V�[���`�揈��
			break;
		case GAME_CLEAR_SCENE:
			gameclear.UpDate();
			gameclear.Draw(gamescene.Score());
			break;
		default:
			break;
		}

		_dbgAddDraw();
		ScreenFlip();     //����ʂ�\��ʂɃR�s�[
	}

	if (!gameclear.Release()) return -1;
	if (!gameover.Release()) return -1;
	if (!titlescene.Release())return -1;
	if (!gamescene.Release()) return -1;

	DxLib_End();  //Dx���C�u�����̏I��
	return 0;     //�v���O�����̏I��
}

void KeyCheck(void)
{
	if (CheckHitKey(KEY_INPUT_RETURN) && enterKeyBack == false)
	{
		enterKeyTriggerKeyDown = true;
		//TRACE("down");
	}
	else
	{
		enterKeyTriggerKeyDown = false;
	}
	if (!CheckHitKey(KEY_INPUT_RETURN) && enterKeyBack == true)
	{
		enterKeyTriggerKeyUp = true;
		//TRACE("up");
	}
	else
	{
		enterKeyTriggerKeyUp = false;
	}
	if (enterKeyBack == true)
	{
		//TRACE("�O on");
	}
	else
	{
		//TRACE("�O off");
	}
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		//TRACE("�� on\n");
		enterKeyBack = true;
	}
	else
	{
		//TRACE("�� off\n");
		enterKeyBack = false;
	}
	
}
