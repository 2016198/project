#pragma once
#include <string>
#include <map>
#include <functional>
#include "Player.h"
#include "../../tmx/rapidxml_utils.hpp"
#include "../../tmx/rapidxml.hpp"

struct KeyCheck//structはpublic:classはprivate(デフォルト)
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)//(？)(引数)
	{
		auto checkMove = [&](Vector2 moveVec) {
			Raycast::Ray ray = { dynamic_cast<Player*>(obj)->pos_ + dynamic_cast<Player*>(obj)->collisionSize, moveVec };
			//_dbgDrawLine(ray.point.x_, ray.point.y_, ray.point.x_ + ray.vec.x_, ray.point.y_ + ray.vec.y_,0xff00ff);
			for (auto col : dynamic_cast<Player*>(obj)->colList_)
			{
				/*_dbgDrawBox(
					col.first.x_ - 1, col.first.y_ - 1,
					col.first.x_ + col.second.x_ + 1, col.first.y_ + col.second.y_ + 1,
					0xff00ff, 0);*/
				if (dynamic_cast<Player*>(obj)->raycast_.CheckCollision(ray, col))//動かない(壁にくっついている)のでfasle
				{
					return false;
				}
			}
			return true;
		};

		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string num = atr->value();
			std::string name = atr->name();
			if (name == "key")
			{
				if (num == "left")
				{
					if (checkMove(Vector2{ -(4 + dynamic_cast<Player*>(obj)->collisionSize.x_), 0 }))
					{
						if (dynamic_cast<Player*>(obj)->cntData_[InputID::Left][static_cast<int>(Trg::Now)])
						{
							dynamic_cast<Player*>(obj)->turn_ = true;
							return true;
						}
					}
				}
				if (num == "right")
				{
					if (checkMove(Vector2{ 4 + dynamic_cast<Player*>(obj)->collisionSize.x_, 0 }))
					{
						if (dynamic_cast<Player*>(obj)->cntData_[InputID::Right][static_cast<int>(Trg::Now)])
						{
							dynamic_cast<Player*>(obj)->turn_ = false;
							return true;
						}
					}
				}
				if (num == "buttonE")
				{
					if (!checkMove(Vector2{ 0, (int)(dynamic_cast<Player*>(obj)->speedY_) + dynamic_cast<Player*>(obj)->collisionSize.y_ }))
					{
						if (dynamic_cast<Player*>(obj)->cntData_[InputID::ButtonE][static_cast<int>(Trg::Now)] &&
							!dynamic_cast<Player*>(obj)->cntData_[InputID::ButtonE][static_cast<int>(Trg::Old)])
						{
							dynamic_cast<Player*>(obj)->jump_ = true;
							return true;
						}
					}
				}
			}

		}
		return false;
	}
};

struct StateCheck//structはpublic:classはprivate(デフォルト)
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)//(？)(引数)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string num = atr->value();
			std::string name = atr->name();
			if ("state" == name && dynamic_cast<Player*>(obj)->state_ == num)
			{
				return true;
			}
		}
		return false;
	}
};

struct CheckNonChangPos//structはpublic:classはprivate(デフォルト)
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)//(？)(引数)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			if (dynamic_cast<Player*>(obj)->state_ != "idle")
			{
				if (dynamic_cast<Player*>(obj)->pos_ == dynamic_cast<Player*>(obj)->bPos_)
				{
					return true;
				}
			}
		}
		return false;
	}
};

struct SetAnime//structはpublic:classはprivate(デフォルト)
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)//(？)(引数)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			if (name == "state")
			{
				dynamic_cast<Player*>(obj)->state_ = atr->value();
				return true;
			}
		}
		return false;
	}
};

struct Move//structはpublic:classはprivate(デフォルト)
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)//(？)(引数)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "x")
			{
				dynamic_cast<Player*>(obj)->pos_.x_ += atoi(atr->value());
				return true;
			}
			if (atrName == "y")
			{
				auto num = atof(atr->value());
				bool super = dynamic_cast<Player*>(obj)->cmd == "ﾌｧｯ!?";
				if (super)
				{
					dynamic_cast<Player*>(obj)->speedY_ *= 1.4;
				}
				dynamic_cast<Player*>(obj)->speedY_ += num;
				dynamic_cast<Player*>(obj)->pos_.y_ += (int)(dynamic_cast<Player*>(obj)->speedY_);
				return true;
			}
		}
		return false;
	}
};

struct FloorCheck
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)//(？)(引数)
	{
		auto checkMove = [&](Vector2 moveVec) {
			Raycast::Ray ray = { dynamic_cast<Player*>(obj)->pos_ + dynamic_cast<Player*>(obj)->collisionSize, moveVec };
			//_dbgDrawLine(ray.point.x_, ray.point.y_, ray.point.x_ + ray.vec.x_, ray.point.y_ + ray.vec.y_,0xff00ff);
			for (auto col : dynamic_cast<Player*>(obj)->colList_)
			{
				/*_dbgDrawBox(
					col.first.x_ - 1, col.first.y_ - 1,
					col.first.x_ + col.second.x_ + 1, col.first.y_ + col.second.y_ + 1,
					0xff00ff, 0);*/
				if (dynamic_cast<Player*>(obj)->raycast_.CheckCollision(ray, col))//動かない(対象物ぶつかっている)のでfasle
				{
					return false;
				}
			}
			return true;
		};
		if (checkMove(Vector2{ 0, (int)(dynamic_cast<Player*>(obj)->speedY_) + dynamic_cast<Player*>(obj)->collisionSize.y_ }))
		{
			return true;
		}
		dynamic_cast<Player*>(obj)->jump_ = false;
		dynamic_cast<Player*>(obj)->state_ = node->first_attribute("state")->value();
		int mapChip = atoi(node->last_attribute("mapchip")->value());
		dynamic_cast<Player*>(obj)->pos_.y_ += (int)(dynamic_cast<Player*>(obj)->speedY_);
		int offSetPos = (dynamic_cast<Player*>(obj)->pos_.y_ + (dynamic_cast<Player*>(obj)->collisionSize.y_ * 2)) % mapChip;
		dynamic_cast<Player*>(obj)->pos_.y_ -= offSetPos - 1;
		dynamic_cast<Player*>(obj)->speedY_ = 0.0;
		return false;
	}
};

struct CeilingCheck
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)//(？)(引数)
	{
		//_dbgDrawCircle(dynamic_cast<Player*>(obj)->pos_.x_, dynamic_cast<Player*>(obj)->pos_.y_, 5, 0xffffff,1);
		auto checkMove = [&](Vector2 moveVec) {
			Raycast::Ray ray = { dynamic_cast<Player*>(obj)->pos_ + dynamic_cast<Player*>(obj)->collisionSize, moveVec };
			//_dbgDrawLine(ray.point.x_, ray.point.y_, ray.point.x_ + ray.vec.x_, ray.point.y_ + ray.vec.y_,0xff00ff);
			for (auto col : dynamic_cast<Player*>(obj)->colList_)
			{
				/*_dbgDrawBox(
					col.first.x_ - 1, col.first.y_ - 1,
					col.first.x_ + col.second.x_ + 1, col.first.y_ + col.second.y_ + 1,
					0xff00ff, 0);*/
				if (dynamic_cast<Player*>(obj)->raycast_.CheckCollision(ray, col))//動かない(対象物ぶつかっている)のでfasle
				{
					return false;
				}
			}
			return true;
		};
		if (checkMove(Vector2{ 0, -((int)(dynamic_cast<Player*>(obj)->speedY_) + dynamic_cast<Player*>(obj)->collisionSize.y_) }))
		{
			return true;
		}
		dynamic_cast<Player*>(obj)->jump_ = false;
		dynamic_cast<Player*>(obj)->state_ = node->first_attribute("state")->value();
		int mapChip = atoi(node->last_attribute("mapchip")->value());
		dynamic_cast<Player*>(obj)->pos_.y_ += (int)(dynamic_cast<Player*>(obj)->speedY_);
		int offSetPos = dynamic_cast<Player*>(obj)->pos_.y_ % mapChip;
		dynamic_cast<Player*>(obj)->pos_.y_ += offSetPos + 1;
		dynamic_cast<Player*>(obj)->speedY_ = 1.0;
		return false;
	}
};

struct NoJump
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)//(？)(引数)
	{
		return !(dynamic_cast<Player*>(obj)->jump_);
	}
};

struct SetPos
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)//(？)(引数)
	{
		auto value = atoi(node->first_attribute("pos")->value());
		dynamic_cast<Player*>(obj)->pos_.x_ = value;
		return false;
	}
};

struct EdgeCheck
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)//(？)(引数)
	{
		std::string value = node->first_attribute("move")->value();
		if (value == "-")
		{
			value = node->first_attribute("pos")->value();
			if (dynamic_cast<Player*>(obj)->pos_.x_ < atoi(value.c_str()))
			{
				return true;
			}
		}
		else if (value == "+")
		{
			value = node->first_attribute("pos")->value();
			if (dynamic_cast<Player*>(obj)->pos_.x_ > atoi(value.c_str()))
			{
				return true;
			}
		}
		return false;
	}
};

struct ModuleNode//structはpublic:classはprivate(デフォルト)
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)//(？)(引数)
	{
		for (auto moduleNode = node->first_node(); moduleNode != nullptr; moduleNode = moduleNode->next_sibling())
		{
			std::string moduleName = moduleNode->first_attribute("name")->value();
			if (modul_.count(moduleName))
			{
				if (!modul_[moduleName](obj, moduleNode))
				{
					continue;
				}
				auto subModuleNode = moduleNode->first_node();
				if (subModuleNode != nullptr)
				{
					if (/*再起呼び出し*/!(*this)(obj, moduleNode))//objectを無駄に作らない
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	std::map < std::string, std::function<bool(Obj* obj, rapidxml::xml_node<>* node)>> modul_ =
	{
		{"keycheck",KeyCheck()},
		{"statecheck",StateCheck()},
		{"setanime",SetAnime()},
		{"move",Move()},
		{ "checknonchangpos",CheckNonChangPos()},
		{"floorcheck",FloorCheck()},
		{"ceilingcheck",CeilingCheck()},
		{"jump",NoJump()},
		{"setpos",SetPos()},
		{"edgecheck",EdgeCheck()}
	};
};