#pragma once

class Tips
{
public:
	bool Init(void);
	bool Update(void);
	bool Release(void);

	//�q���g�摜�̕`��
	void SlideDraw(void);
	void LightDraw(void);
	void MatchDraw(void);

	bool MatchFlag(void);
	void InventoryDraw(void);
	bool ReturnFlag(void);


private:

	//�摜�i�[�ϐ�
	int slideTips;	//�q���g�P
	int lightTips;	//�q���g�Q
	int matchTips;	//�q���g�P�ƂQ�����킹���摜

	//�q���g����ɓ���邽�߂̃t���O
	bool slideFlag;	
	bool lightFlag;
	bool matchFlag;

	int count;
	int font;
};

