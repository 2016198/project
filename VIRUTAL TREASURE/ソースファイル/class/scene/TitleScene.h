#pragma once
#include <memory>
#include <list>
#include "../Vector2.h"
#include "../Color3.h"
#include "BaseScene.h"
#include "../title/bug.h"

class TitleScene:
	public BaseScene
{	

public:
	TitleScene(INPUT_TYPE type);	//�R���X�g���N�^
	~TitleScene() override;			//�f�X�g���N�^

	bool Init(void) override;					//����������
	SCENE_ID Update(double delta) override;		//�X�V����
	int Draw(void) override;					//�`�揈��
	void Release(void) override;				//�������
	const int GetNum(void) override;			//�l�킽��
	const SCENE_ID GetScene(void) override;		//�����̃V�[����n��

private:

	void ImgMove(void);							//�摜�̈ړ�����
	bool CheckMoveEnd(void);					//�摜�̈ړ��������I��������
	void SpeechBalloon(double num);				//�Z���t�̊g��k��

	void MessageDraw(void);						//�I���������̃��b�Z�[�W�`��

	static constexpr size_t IMG_COUNT = 6U;		//title�Ŏg���w�i�ȊO�̉摜�̐�
	static constexpr int OFFSET = 95;			//���������炷

	static constexpr int GEAR_SIZE_X = 76;						//���ԉ摜�̃T�C�YX
	static constexpr int GEAR_SIZE_Y = 76;						//���ԉ摜�̃T�C�YY
	static constexpr int GEAR_SIZE_HALF_X = GEAR_SIZE_X / 2;	//���ԉ摜�̔����T�C�YX
	static constexpr int GEAR_SIZE_HALF_Y = GEAR_SIZE_Y / 2;	//���ԉ摜�̔����T�C�YY

	static constexpr Vector2 PATTERN_COUNT = { 4, 2 };			//�Ŗ͗l�̐�
	static constexpr int PATTERN_TYPE = 8;						//�Ŗ͗l�̍��v�l
	static constexpr size_t PATTERN_NUM = 100U;					//�Ŗ͗l�̐�����

	const char* imgFile_[IMG_COUNT] =	//�t�@�C���p�X
	{
		"image/title/single.png",
		"image/title/double.png",
		"image/title/title.png",
		"image/title/gear.png",
		"image/title/end.png",
		"image/title/gameend.png"
	};

	static constexpr double BUG_TIME = 50.0;		//���������o�Ă��鎞��
	static constexpr size_t BUG_COUNT = 20U;		//�ő�̒��̐�

	std::list<std::unique_ptr<Bug>> bugPool_;		//���̗\���̃|�C���^
	std::list<std::unique_ptr<Bug>> bugList_;		//���̎g�p����|�C���^

	std::array<Vector2, IMG_COUNT> pos_;			//�e�摜�̍��W
	std::array<Vector2, IMG_COUNT - 1U> offset_;	//�l�p�̖ړI�n����̋���
	int offsetFont_;								//�t�H���g�𒆐S�悹�ɂ���ϐ�
	std::vector<int> titleImg_;						//�O���t�B�b�N�n���h��(�I�����ڌn)
	Color3 lineColor_;								//�O�g�̐F�R�[�h
	int sound_[2];									//�T�E���h�n���h��
	bool isSelect_;									//�I��������
	int alpha_;										//�A���t�@�l(�^�C�g��)
	double scale_;									//�Z���t�̑傫��
	Vector2 speechSize_;							//�Z���t�摜�̑傫��

	int msgScreen_;									//���b�Z�[�W�̕\���X�N���[��
	int msgGrassImg_;								//�O���t�B�b�N�n���h��
	std::vector<int> msgPatternImg_;				//�O���t�B�b�N�n���h��
	std::vector<Vector2> patternPos_;				//�͗l�̍��W
	double zoom_;									//�\���̑傫��
};

