#pragma once
#include "BaseInput.h"
class P2Input :
    public BaseInput
{
public:
    P2Input() {};                       //�R���X�g���N�^
    ~P2Input() override {};             //�f�X�g���N�^

    void SetKeyList(INPUT_TYPE type) override;     //�L�[�̏�Ԃ�ύX
private:

};

