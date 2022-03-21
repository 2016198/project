#pragma once
#include "BaseInput.h"

class P1Input :
    public BaseInput
{
public:
    P1Input() {};                       //コンストラクタ
    ~P1Input() override {};             //デストラクタ

    void SetKeyList(INPUT_TYPE type) override;     //キーの状態を変更
private:

};

