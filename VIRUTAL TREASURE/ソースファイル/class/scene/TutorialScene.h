#pragma once
#include <memory>
#include <vector>
#include "../Vector2.h"
#include "../manager/MaterialManager.h"
#include "BaseScene.h"
#include "../game/Player.h"
#include "../game/item/Item.h"
#include "../tutorial/Text.h"
#include "../game/Map.h"

class TutorialScene :
    public BaseScene
{
public:
	TutorialScene(INPUT_TYPE type);		//コンストラクタ
	~TutorialScene() override;			//デストラクタ

	bool Init(void) override;					//初期化処理
	SCENE_ID Update(double delta) override;		//更新処理
	int Draw(void) override;					//描画処理
	void Release(void) override;				//解放処理
	const int GetNum(void) override;			//値わたし
	const SCENE_ID GetScene(void) override;		//自分のシーンを渡す

private:

	std::unique_ptr<Text> textPtr_;						//表示するテキストのインスタンス
	std::vector<std::unique_ptr<Player>> playerPtr_;	//プレイヤーのインスタンス	
	std::vector<std::unique_ptr<Item>> itemPtr_;		//アイテムのインスタンス
	std::unique_ptr<Map> mapPtr_;						//マップのインスタンス

	int screenP_;										//プレイヤーのスクリーン
	int screenM_;										//マニュアル画面のスクリーン
	bool rock[2];										//同じ処理を連続でしないようにロックする
	double delta_[2];									//デルタタイム、0:一回のデルタ値、1:デルタ値の合計

	static constexpr double TIP_TIME = 2000.0;			//ヒントを出す時間

	int bright_;										//画面の明るさ
	void ChackTextMode(TEXT_MODE textMode);				//テキストモードの管理関数

	//フェイド関係
	void FadeCommand(void);								//フェイド命令
	bool fadeIn_;										//フェイドイン
	bool fadeOut_;										//フェイアウト

	int progressNum_;									//現在の進捗
	double tipsTime_;									//ヒントの表示
	bool CheckProgress(int num);						//進捗チェック
	void ProgressUpdate(void);							//それぞれ進捗の更新
	void ProgressDraw(void);							//それぞれ進捗の描画
	void TipDraw(void);									//ヒント描画
	double alpha_;										//色のα値

	bool player_[2];									//プレイヤーの移動終了確認
};

