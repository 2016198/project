#pragma once
#include "../Vector2.h"
#include "../Color3.h"

enum class MOVE_DIR			//�ړ��̕���
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX
};

class Fire
{
public:

	Fire(std::vector<int> imageVec);	//�R���X�g���N�^
	~Fire();							//�f�X�g���N�^

	static constexpr int ANIM_SIZE = 4;	//�A�j���[�V�����̐�

	void Create(int num);				//��������
	void Update(void);					//�X�V����
	void Move(MOVE_DIR dir);			//�ړ�����
	void Draw(void);					//�`�揈��
	bool Check(int pos);				//�m�F����

	bool IsAlive(void);					//�����`�F�b�N

private:

	Vector2 offsetSize_;				//�I�t�Z�b�g
	int move_;							//�ړ���
	double size_;						//�傫��
	int pos_;							//���݂̍��W
	bool alive_;						//�����m�F
	Vector2 drawPos_;					//�`����W
	std::vector<int> image_;			//�O���t�B�b�N�n���h��
};

