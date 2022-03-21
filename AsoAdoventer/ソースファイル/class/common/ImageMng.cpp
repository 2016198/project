#include <DxLib.h>
#include "ImageMng.h"
#include"../../_debug/_DebugConOut.h"
#include"../../_debug/_DebugDispOut.h"

const VecInt& ImageMng::GetID(std::string key)
{
    if (imageMap_.count(key) == 0)//ì«Ç›çûÇÒÇ≈Ç¢Ç»ÇØÇÍÇŒì«Ç›çûÇﬁ
    {
        imageMap_[key].resize(1);
        imageMap_[key][0] = LoadGraph(key.c_str());
        if (imageMap_[key][0] == -1)
        {
            TRACE("ì«Ç›çûÇ›é∏îs:%s", key.c_str());
        }
    }
    return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key)
{
    if (imageMap_.count(key) == 0)//ì«Ç›çûÇÒÇ≈Ç¢Ç»ÇØÇÍÇŒì«Ç›çûÇﬁ
    {
        imageMap_[key].resize(1);
        imageMap_[key][0] = LoadGraph(f_name.c_str());
        if (imageMap_[key][0] == -1)
        {
            TRACE("ì«Ç›çûÇ›é∏îs:%s", key.c_str());
        }
    }
    return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt)
{
    if (imageMap_.count(key) == 0)//ì«Ç›çûÇÒÇ≈Ç¢Ç»ÇØÇÍÇŒì«Ç›çûÇﬁ
    {
        imageMap_[key].resize(divCnt.x_ * divCnt.y_);
        if ((LoadDivGraph(
            f_name.c_str(),
            divCnt.x_ * divCnt.y_,
            divCnt.x_,
            divCnt.y_,
            divSize.x_,
            divSize.y_,
            &imageMap_[key][0])) == -1)
        {
            TRACE("ì«Ç›çûÇ›é∏îs:%s", f_name.c_str());
        }
    }
    return imageMap_[key];
}

ImageMng::ImageMng()
{

}

ImageMng::~ImageMng()
{

}
