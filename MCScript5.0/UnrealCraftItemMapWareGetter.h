#pragma once
#include"GetItemMap.h"
#include"ImagePerformer.h"
#include"UnrealCraftBox.h"
#include"MCItemMap.h"
#include"Tools.h"

class UnrealCraftItemMapWareGetter:
	public GetItemMap
{
public:
	static int MAX_WAIT_MILITIME;
private:
	enum class Status
	{
		Original,//初始状态
		Selecting,//选择状态
		Getting,//购买状态
		Arranging,//整理状态
		Checking,//检查状态
		End//结束状态
	};
	enum class Pos
	{
		NotKnow,Concreate,Clay,Other
	};
	static map<string, int> item_index_map;
	static string warehouse;
private:
	ImagePerformer* performer;
	UnrealCraftBox box;
	Box* ender_chest;
	const MCItemMap* item_map;
	TimeCounter tc;

	Status status;
	Pos pos;
	vector<pair<string, int>> need_vec;
	vector<pair<string, int>> need_vec_copy;
	int item_to_get_index;
	bool lack_item;//由getting提供的是否缺乏物品的bool值，由selecting接收
public:
	UnrealCraftItemMapWareGetter(ImagePerformer* performer, Box* ender_chest,
		string mc_item_map_path, string config_path);
	// 通过 GetItemMap 继承
	void getItemMap(map<string, int> map) override;
private:
	//所有操作都应该自带延迟
	//加载文件
	void load(string mc_item_map_path, string config_path);
	//初始化
	void init(map<string, int> map);
	//主循环
	void mainRoll();
	//状态切换
	void setStatus(Status status);
	//初始状态，先刷新背包和末影箱
	void original();
	//选择状态
	void selecting();
	//购买状态
	void getting();
	//整理状态，进入时打开末影箱
	void arranging();
	//检查状态，进入时打开末影箱
	void checking();
	//结束状态
	void end();
	//打开箱子
	void openBox();
	//关闭箱子
	void closeBox();
	//读取箱子信息，顺便刷新背包
	void readBox();
	//背包是否已满
	bool isPackageFull();
	//按下SHIFT
	void shiftDown();
	//松开SHIF
	void shiftUp();
	//从Box中获取物品
	void getItemFromBox(int x,int y);
	//打开末影箱
	void openEnderChest();
	//读取末影箱和背包，要求已经打开末影箱
	void readEnderChestAndPackage();
	//关闭末影箱
	void closeEnderChest();
	//显示need_vec
	string getPairVectorStr(const vector<pair<string, int>>& vec);
	//获取玩家状态
	PlayerStatus getPlayerStatus();
	//去某地
	void goTo(string name);
	//selecting的子函数，计算并传送到玩家应该处于的位置
	void goToSuitablePos(pair<string,int> name_num_pair,int& first_item_x);
	double countDistance(double x1, double y1, double z1, double x2, double y2, double z2);
};

