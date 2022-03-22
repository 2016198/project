#pragma once
#include "Obj.h"
#include "../common/Raycast.h"
#include "../../tmx/rapidxml_utils.hpp"
#include "../../tmx/rapidxml.hpp"

struct ModuleNode;

class Enemy :
    public Obj
{
public:
	Enemy();
	Enemy(CntType cntType, Vector2 pos);
	~Enemy();
private:
	bool Init(CntType cntType, Vector2 pos) override;
	void UpDate(ColList colList) override;
	void Draw() override;

	const std::string Obj_ID = "enemy";

	Raycast raycast_;
};

