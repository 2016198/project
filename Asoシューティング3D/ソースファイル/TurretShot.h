#pragma once
#include "ShotBase.h"

class TurretShot : public ShotBase
{
public:

    TurretShot(SceneManager* manager, Transform *parent);
    //�@�C�g����e�𔭎˂���
    //  �e�̕����ɋC��t���悤�I
    //  �e�̕���     = �C�g�̑O������
    //  �e�̔��ˈʒu = �C�g�̈ʒu����̑��Έʒu(Q PosAxis)
    //                 ������Ə�(2)�A������ƑO(3)����]���l��


    //�A�e�̔��ˊԊu
    //�B���Ԃ��]������A�e�̍H�v(����A�g�U�A�ǔ��A���[�U�[��)
};

