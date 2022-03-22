#pragma once
#include <list>
#include <memory>
#include "Obj.h"
#include "Shot.h"
#include "../common/Raycast.h"
#include "../../tmx/rapidxml_utils.hpp"
#include "../../tmx/rapidxml.hpp"

struct ModuleNode;
struct KeyCheck;
struct StateCheck;
struct SetAnime;
struct CheckNonChangPos;
struct Move;
struct FloorCheck;
struct CeilingCheck;
struct NoJump;
struct SetPos;
struct EdgeCheck;

class Player :
	public Obj
{
public:
	Player();
	Player(CntType cntType, Vector2 pos);
	~Player();
private:
	bool Init(CntType cntType, Vector2 pos) override;
	void UpDate(ColList colList) override;
	void Draw() override;

	Raycast raycast_;
	std::vector<char> stateVec_;
	rapidxml::xml_node<>* stateNode_;
	rapidxml::xml_document<> stateDoc_;

	ModuleNode* moduleNode_;
	CntData cntData_;
	bool jump_;
	std::string cmd = "empty";

	ColList colList_;
	const std::string Obj_ID = "player";

	std::list<std::unique_ptr<Shot>> bulletList_;

	friend KeyCheck;			//ƒWƒƒƒCƒAƒ“
	friend StateCheck;
	friend SetAnime;
	friend CheckNonChangPos;
	friend Move;
	friend FloorCheck;
	friend CeilingCheck;
	friend NoJump;
	friend SetPos;
	friend EdgeCheck;
};