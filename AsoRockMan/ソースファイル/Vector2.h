#pragma once    //二重定義させないコマンド

class Vector2
{
public:                     //メンバー変数
	int x;                  //x成分
	int y;                  //y成分

	//コンストラスタ
	Vector2(void);

	//コンストラスタ
	Vector2(int valueX, int valueY);
};
