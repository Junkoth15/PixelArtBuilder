#pragma once
#include"GetItemMap.h"
#include"ImagePerformer.h"
#include"UnrealCraftBox.h"
#include"MCItemMap.h"
#include"UnrealCraftShopBox.h"
class UnrealCraftItemMapGetter:
	public GetItemMap
{
private:
	enum class Status
	{
		Original,//初始状态
		Selecting,//选择状态
		Buying,//购买状态
		Arranging,//整理状态
		Checking,//检查状态
		End//结束状态
	};
protected:
	ImagePerformer* performer;
	UnrealCraftShopBox shop;
	Box* ender_chest;
	const MCItemMap* item_map;
	Status status;
	map<string, int> need_map;
	map<string, int> need_map_copy;
	string item_to_buy;
	int page;//当前页数
	bool next_page_is_bigger;//下一页是往右翻
public:
	UnrealCraftItemMapGetter(ImagePerformer* performer,Box* ender_chest,string mc_item_map_path);
	// 通过 GetItemMap 继承
	void getItemMap(map<string, int> map) override;
private:
	//所有操作都应该自带延迟
	//主循环
	void mainRoll();
	//状态切换
	void setStatus(Status status);
	//初始状态，进入时自动设置page和next_page，先刷新背包和末影箱，然后打开商店
	void original();
	//选择状态
	void selecting();
	//购买状态
	void buying();
	//整理状态，进入时打开末影箱
	void arranging();
	//检查状态，进入时打开末影箱
	void checking();
	//结束状态
	void end();
	//打开商店
	void openShop();
	//关闭商店
	void closeShop();
	//读取商店信息，顺便刷新背包
	void readShop();
	//跳转到下一页
	void jumpToNextPage();
	//背包是否已满
	bool isPackageFull();
	//添加一组
	void addOneGroup();
	//减少一个
	void removeOne();
	//购买
	void pay();
	//将一组物品加入背包
	void addOneGroupToPackage(const MCItem& item);
	//打开末影箱
	void openEnderChest();
	//读取末影箱和背包，要求已经打开末影箱
	void readEnderChestAndPackage();
	//关闭末影箱
	void closeEnderChest();
	//图减法
	map<string, int> mapMinus(const map<string, int>& larger, const map<string, int>& smaller);
};

