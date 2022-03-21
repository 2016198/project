#include "Eshot.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Eshot::Init(void)//‰Šú‰»ˆ—
{
	Image = LoadGraph("image/eshot.png");
	if (Image == -1)
	{
		TRACE("’e‚Ì‰æ‘œ‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
		return false;
	}
	pos.X = 0;
	pos.Y = 0;
	Alive = false;
	speed = 5;

	return true;
}

void Eshot::Setup(Vector2 ePos)//À•W‚ð—^‚¦‚é
{
	if (Alive == false)
	{
		Alive = true;
		pos.X = ePos.X;
		pos.Y = ePos.Y;
		//PlaySoundMem(se, DX_PLAYTYPE_BACK);
	}
}

void Eshot::UpDate(Vector2 Pos)//XVˆ—
{
	if (pos.Y >= -E_SHOT_SIZE_Y &&  //ƒXƒNƒŠ[ƒ“‚Ì’†‚É‚¢‚é‚Æ‚«
		pos.X >= -E_SHOT_SIZE_X &&
		pos.X <= SCREEN_SIZE_X &&
		pos.Y <= SCREEN_SIZE_Y &&
		Alive == true)          //”­ŽË‚µ‚Ä‚¢‚é‚Æ‚«
	{
		pos.Y += Pos.Yy * speed;
		pos.X += Pos.Xx * speed;
	}
	else    //‰æ–ÊŠO‚Éo‚½Žž‚Ìˆ—
	{
		Alive = false;          //”­ŽË‚µ‚Ä‚¢‚È‚¢‚Æ‚«
	}
}

void Eshot::Draw(void)//•`‰æˆ—
{
	if (Alive == true)
	{
		DrawGraph(pos.X, pos.Y, Image, true);                     //’e‚Ì•`‰æ
	}
}

Vector2 Eshot::GetPos(void)   //À•W¬•ª‚ð—^‚¦‚é
{
	return pos;
}

bool Eshot::GetAlive(void)  //Œ‚‚Á‚Ä‚é‚©‚Ç‚¤‚©‚Ìó‘Ô‚ð•Ô‚·
{
	return Alive;
}

void Eshot::DeleteShot(void) //’e‚ðÁ‚·ˆ—
{
	Alive = false;
}

bool Eshot::Release(void)  //‰ð•úˆ—
{
	DeleteGraph(Image);
	return true;
}

bool Eshot::GameInit(void)  //ƒQ[ƒ€ƒI[ƒo[‚ÌŒã‚Ì‰Šú‰»ˆ—
{
	pos.x = 0;
	pos.y = 0;
	Alive = false;

	return true;
}