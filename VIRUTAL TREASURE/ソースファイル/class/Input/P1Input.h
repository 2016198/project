#pragma once
#include "BaseInput.h"

class P1Input :
    public BaseInput
{
public:
    P1Input() {};                       //�R���X�g���N�^
    ~P1Input() override {};             //�f�X�g���N�^

    void SetKeyList(INPUT_TYPE type) override;     //�L�[�̏�Ԃ�ύX
private:

};

