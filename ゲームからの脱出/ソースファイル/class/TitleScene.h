#pragma once
class TitleScene
{
public:
	bool Init(void);
	bool Update(void);
	void Draw(void);
	bool Release(void);

private:
	int image_;	//�w�i�摜�i�[�p
	int count_;
	int font_;	//�t�H���g���i�[�p
};
