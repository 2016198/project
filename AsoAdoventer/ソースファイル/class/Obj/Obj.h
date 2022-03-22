#pragma once
#include <memory>
#include<list>
#include<map>
#include "../common/ImageMng.h"
#include "../common/ListMng.h"
#include "../common/Vector2.h"
#include "../common/input/Controller.h"
#include "../common/Collision.h" 

//class Controller;
//struct Move;
//struct StateCheck;
//struct KeyCheck;

class Obj
{
public:
	Obj();
	~Obj();
	virtual bool Init(CntType cntType, Vector2 pos) = 0;
	virtual void UpDate(ColList colList) = 0;
	virtual void Draw() = 0;
private:

protected:
	std::string state_;							//�I�u�W�F�N�g�̃A�j���[�V�����̏��
	std::string bState_;						//1�t���[���O�I�u�W�F�N�g�̃A�j���[�V�����̏��
	double speedY_ = 0.0;						//�ړ����x:�c
	Vector2 pos_;								//���W
	Vector2 bPos_;								//��t���[���O�̍��W
	std::unique_ptr<Controller> controller_;	//�R���g���[��
	Vector2 collisionSize;						//�����蔻��T�C�Y
	AnimeData animeData_;						//�A�j���̃f�[�^
	bool turn_;									//�摜�̔��]���邩
	const double gravity = 0.2;					//�d�͉����x
	ColList colList_;							//�����蔻��i�n�`�j

	//friend Move;								//�W���C�A��
	//friend StateCheck;
	//friend KeyCheck;
};

