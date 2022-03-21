#pragma once
#include "BaseInput.h"
class P2Input :
    public BaseInput
{
public:
    P2Input() {};                       //コンストラクタ
    ~P2Input() override {};             //デストラクタ

    void SetKeyList(INPUT_TYPE type) override;     //キーの状態を変更
private:

};

