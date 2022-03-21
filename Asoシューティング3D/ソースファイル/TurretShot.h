#pragma once
#include "ShotBase.h"

class TurretShot : public ShotBase
{
public:

    TurretShot(SceneManager* manager, Transform *parent);
    //①砲身から弾を発射する
    //  弾の方向に気を付けよう！
    //  弾の方向     = 砲身の前方方向
    //  弾の発射位置 = 砲身の位置からの相対位置(Q PosAxis)
    //                 ちょっと上(2)、ちょっと前(3)※回転を考慮


    //②弾の発射間隔
    //③時間が余ったら、弾の工夫(分裂、拡散、追尾、レーザー等)
};

