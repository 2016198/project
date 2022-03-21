#pragma once
#include "Controller.h"
class PadInput :
    public Controller
{
public:
    PadInput();
    ~PadInput() override;

    uniqueInput UpDate(uniqueInput ownInput) override;
    CntType GetCntType(void) override { return CntType::Pad; };
private:
    std::map<InputID, unsigned int>inputTbl_;
};

