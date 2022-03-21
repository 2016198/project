#pragma once
#include "Controller.h"

class KeyInput :
    public Controller
{
public:
    KeyInput();
    ~KeyInput() override;

    uniqueInput UpDate(uniqueInput ownInput) override;
    CntType GetCntType(void) override { return CntType::Key; };
private:
   //RingBuf* data = com.data();
   //RingBuf* ringBuf_;
    std::array<char, 256U> keyData_;
    std::map<InputID, unsigned int>inputTbl_;
};

