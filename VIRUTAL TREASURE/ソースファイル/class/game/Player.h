#pragma once
#include <type_traits>
#include <memory>
#include <array>
#include <map>
#include <string>
#include <vector>
#include "../Vector2.h"
#include "../Color3.h"
#include "../manager/MaterialManager.h"
#include "../Input/BaseInput.h"
#include "item/Item.h"

enum class DIR			//player�̌���
{
	DOWN,				//��
	LIFT,				//��
	RIGHT,				//�E
	UP,					//��
	MAX
};

enum class MODE	//�I�����[�h
{
	MOVE,					//�ړ�
	ITEM,					//�A�C�e���I��
	SELECT,					//�ړ����A�C�e�����I��
	WARP,					//���[�v�ړ�
	NONE
};

constexpr int INVECTORY_MAX = 4;					//�C���x���g���̍ő�l
constexpr size_t SOUND_CNT = 13;					//�T�E���h�̐�
constexpr int ANIM_SIZE = 3;						//�A�j���[�V�����̐�
constexpr Vector2 IMAGE_SIZE = { 96, 128 };			//�v���C���[�摜�̃T�C�Y
constexpr Vector2 NUM_CNT = { 10, 1 };				//�v���C���[�摜�̃T�C�Y
constexpr Vector2 PLAYER_SIZE = {					//�v���C���[�̃T�C�Y
	IMAGE_SIZE.x / ANIM_SIZE,
	IMAGE_SIZE.y / static_cast<int>(DIR::MAX)
};			
constexpr Vector2 PLAYER_HAFE_SIZE = {		//�v���C���[�̔����T�C�Y
	PLAYER_SIZE.x / 2,
	PLAYER_SIZE.y / 2,
};

class Player
{
private:

	enum class HAPPENING	//�n�v�j���O
	{
		RANDOM_POS,			//�ǂ����֔��
		RESET_POS,			//�ŏ��̂Ƃ���֖߂�
		GET_ITEM,			//�A�C�e������
		CHANGE_POS,			//�ꏊ����
		CHANGE_MAP,			//���w�ύX
		NONE,				//�͂���
		MAX
	};

	struct PLAYER	//�v���C���[�̏��
	{
		int pos[7];										//���W�F0 = ���݁A1�` = �ߋ��̃��O
		std::vector<ITEM>item;							//�������Ă���A�C�e��
		int move;										//����ړ�������
		DIR dir;										//�v���C���[�̌���
		int warp;										//�ړ���
		double delta_;									//�c�莞��
	}; 

	const std::array<int, 4U> animNum_ = {	//�A�j���[�V�����̃��[�v
		0,
		1,
		2,
		1
	};

	std::string item_name_[static_cast<int>(ITEM::MAX)]	//�\�����镶��
	{
		"���ʎ��΂���ɓ��ꂽ�I",
		"�����T�m�@����ɓ��ꂽ�I",
		"���΂���ɓ��ꂽ�I",
		"�낤��������ɓ��ꂽ�I",
		"�A�C�e���������ς��œ���ł��Ȃ������c"
	};

	std::map<std::string, std::vector<std::string>> fileName_;			//�O���t�B�b�N�֌W
	std::map<std::string ,VecInt> image_;								//�O���t�B�b�N�n���h��
	VecInt sound_;														//�T�E���h�n���h��

	//�Z���N�g�p�ϐ�
	MODE select_;			//���ǂ��ɃJ�[�\�������邩
	ITEM selectItem_;		//�ǂ̃A�C�e����I��ł�H
	int selectInven_;		//�C���x���g���̑I��l
	int offsetSize_[static_cast<int>(ITEM::MAX) - 1] = {5, 1, 1, 1};//�I�����Ă���̂�傫������
	void SetSize(int num);	//�I�����Ă�̂͂ǂ�H
	
	//�ړ��p�ϐ�
	Vector2 drawPos_[7];	//�`��̍��W
	Vector2 movePow_;		//�ړ���
	double moveSpeed_;		//�ړ��̑���
	int map_;				//�ړI�n
	PLAYER player_ = {};	//Player�̓Ǝ��̕ϐ�
	int alpha_;				//�F�̓����x
	Color3 color_;			//�F�R�[�h
	bool moveEnd_;			//���ǂ���������H
	void Move(void);		//�ړ�����
	void MoveEnd(void);		//�ړ����I���������s
	int surround_;			//�͂񂾂Ƃ���
	int SetSurround(void);	//�͂񂾂Ƃ���͂ǂ�
	std::map<DIR, std::pair<bool, double>> canMove_ = {};				//�ړ��\
	unsigned int defultColor_;											//�����J���[
	void ChackDir(void);												//�����̏���

	//�A�C�e���p�ϐ�
	double angle_;			//���ʎ��j�̊p�x
	ITEM useItem_;			//�ǂ̃A�C�e�����g���Ă���H
	int fullItem_;			//�A�C�e���������ς���
	double itemLife_;		//�A�C�e���̌��ʎ���
	bool useMagnet_;		//���΂��g�p���Ă��邩

	//���̑�
	MODE mode_;								//����mode
	bool fadeIn_;							//�F���ς��
	bool fadeOut_;							//�F���ς��
	int respawn_;							//�ŏ��ɂ����Ƃ���
	int font_;								//�t�H���g�̃n���h��
	double fontSize_;						//�t�H���g�̃T�C�Y
	double delta_;							//�f���^�^�C��
	bool lock_;								//���ł��ړ������烍�b�N����
	bool isMove_;							//�����Ă��邩�ǂ���
	double target_;							//�摜�̊p�x
	double targetSenter_;					//�摜�̊p�x

	//�A�j���[�V����
	std::pair<double, int> animCnt_[2];			//�A�j���[�V�����Ǘ�
	void SetAnim(double delta, int num);		//�A�j���[�V��������
	double Deg2Rad(double deg);					//Deg����Rad�֕ϊ�

	//���͊֌W
	InputList input_ = {};					//���͏��

public:

	bool Init(int pos, int point, Color3 color);		//����������
	bool Update(const InputList input, double delta);	//�X�V����
	void Draw(int size);				//�`�揈��(���C��)
	void DrawMoveLine(void);			//�`�揈��(�ʒu���d�Ȃ��Ă��킩��₷��)
	void DrawPlayer(bool over,int size);//�`�揈��(�v���C���[�̉摜)
	void DrawInfo(int num);				//�`�揈��(�v���C���[�̏��)
	bool Release(void);					//�������

	Player(const char* nameG, const char* nameS);		//�R���X�g���N�^
	~Player();											//�f�X�g���N�^

	bool IsChange_;						//�ꏊ���
	bool IsHere_;						//�W��
	void SetPos(int point);				//�ꏊ���
	void SetItemLife(double life);		//�A�C�e���̌��ʎ��Ԃ��擾

	void Happening(HAPPENING eve);		//�ԈႦ���Ƃ�����͂񂾂�
	void ResetMove(void);				//�^�[�����I��
	ITEM GetSelectItem(void);			//�I�����Ă���A�C�e����\��
	ITEM GetUseItem(void);				//�g�p���Ă���A�C�e����\��
	double GetAngle(void);				//�p�x��Ԃ�
	Vector2 GetDrawPos(void);			//���WVector2���擾
	bool CheckHap(void);				//�͂񂾂Ƃ��낪�Ԉ���Ă��邩:false�@�����A���邢�͈͂�łȂ�
	int GetMap(void);					//�ړI�n��Ԃ�
	int GetPoint(void);					//���W��Ԃ�
	Vector2 GetDisVec2(void);			//�ړI�n�܂ł̋���(x������y����)
	void Undo(void);					//��߂�
	void Candle(CANDLE candle);			//�낤�����̌���
	bool IsFull(void);					//�A�C�e���������ς����ǂ���
	int GetMove(void);					//�v���C���[�̈ړ��ʂ��󂯎��
	void SetMode(MODE mode);			//���[�h�̕ύX
	MODE GetMode(void);					//�v���C���[�̃��[�h���󂯎��
	Vector2 GetInfoDrawPos(int num);	//���̕`��̂킽��
	int GetSurround(void);				//�͂񂾈ʒu��Ԃ�
};

static DIR begin(DIR) { return DIR::DOWN; };
static DIR end(DIR) { return DIR::MAX; };
static DIR operator++(DIR& state)
{
	state = static_cast<DIR>(std::underlying_type<DIR>::type(state) + 1);
	return state;
};
static DIR operator*(const DIR& state) { return state; };

