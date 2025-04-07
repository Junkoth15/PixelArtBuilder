#include "UnrealCraftMPBPerformer.h"
#include"Tools.h"
#include"FileLoader.h"
#include"UnrealCraftBox.h"
#include"UnrealCraftPackage.h"
#include"MCItemMapFactory.h"
#include"UnrealCraftPerformerFile.h"
using namespace std;

int UnrealCraftMPBPerformer::MAX_WAIT_MINITIME=10000;

UnrealCraftMPBPerformer::UnrealCraftMPBPerformer(shared_ptr<ImagePerformer> performer, UnrealCraftMPBInfo mpb_info) :
	performer(performer),
	converter(mpb_info.convert_file_path, mpb_info.item_map_path),
	ender_chest(UnrealCraftBox(BoxType::SMALL)),
	mpb_info(mpb_info),
	getter(performer.get(),&ender_chest,
		UnrealCraftPerformerFile::getMCItemSetPath(),mpb_info.getter_file_path),
	tc(TimeCounterMode::MILISECOND)
{
}

void UnrealCraftMPBPerformer::getItemToHand(const vector<ColorItem>& line, int item_index)
{
	//从背包中获取物品坐标
	const MCItem& item = convert(line[item_index].name);
	POINT item_point = findOneMCItem(item);
	//物品在物品栏中，直接切换手
	if (item_point.y == 4) {
		if (performer->getHand() != item_point.x) {
			performer->changeHand(item_point.x);
			performer->setHand(item_point.x);
		}
	}
	//物品不在物品栏中，去背包寻找
	else {
		arrangePackage(line, item_index);
		getItemToHand(line, item_index);
	}
	return;
}

void UnrealCraftMPBPerformer::putBlock()
{
	performer->putBlock(true);
	usleep(70);
}

void UnrealCraftMPBPerformer::move(MoveMode mode)
{
	switch (mode)
	{
	case MoveMode::FrontBegin:performer->keyEvent(ASCIIKeyCode::W, KeyEvent::KeyDown);
		break;
	case MoveMode::FrontEnd:performer->keyEvent(ASCIIKeyCode::W, KeyEvent::KeyUp);
		break;
	case MoveMode::BackBegin:performer->keyEvent(ASCIIKeyCode::S, KeyEvent::KeyDown);
		break;
	case MoveMode::BackEnd:performer->keyEvent(ASCIIKeyCode::S, KeyEvent::KeyUp);
		break;
	case MoveMode::LeftBegin:performer->keyEvent(ASCIIKeyCode::A, KeyEvent::KeyDown);
		break;
	case MoveMode::LeftEnd:performer->keyEvent(ASCIIKeyCode::A, KeyEvent::KeyUp);
		break;
	case MoveMode::RightBegin:performer->keyEvent(ASCIIKeyCode::D, KeyEvent::KeyDown);
		break;
	case MoveMode::RightEnd:performer->keyEvent(ASCIIKeyCode::D, KeyEvent::KeyUp);
		break;
	default:
		break;
	}
}

PlayerStatus UnrealCraftMPBPerformer::getPlayerStatus()
{
	Mat img;
	performer->getF3Pic(img);
	performer->analysisPic(img);
	return performer->getAllPlayerInfo();
}

bool UnrealCraftMPBPerformer::testAddItemToPackage(map<string, int> item_map) const
{
	UnrealCraftBox ender_box(BoxType::SMALL);
	UnrealCraftPackage package;

	//先往背包放
	bool package_full = false;
	for (auto& pair : item_map) {
		auto& item = convert(pair.first);
		int& num = pair.second;
		//每次放一组，背包没满才能放
		while (num > 0 && !package_full) {
			//放置成功，扣减数量，失败则退出
			if (package.addItemByShift(item, std::min(num, 64))) num -= std::min(num, 64);
			else package_full = true;
		}
		if (package_full) break;
	}

	//再往末影箱里放
	bool ender_box_full = false;
	for (auto& pair : item_map) {
		auto& item = convert(pair.first);
		int& num = pair.second;
		//每次放一组，没满才能放
		while (num > 0 && !ender_box_full) {
			//放置成功，扣减数量，失败则退出
			if (ender_box.addItemByShift(item, std::min(num, 64))) num -= std::min(num, 64);
			else ender_box_full = true;
		}
		if (ender_box_full) break;
	}
	return !ender_box_full;
}

void UnrealCraftMPBPerformer::goToLine(int line)
{

	/*performer->resTp(mpb_info.board_line_name+to_string(line/16+1));
	usleep(6000);*/

	//performer->useInstruction("/home " + to_string(line / 16 + 1)); usleep(4000);
	homeTp(to_string(line / 16 + 1));
	PlayerStatus status = getPlayerStatus();

	int line_x = mpb_info.board_first_line_x + line;//目标列对应的x坐标
	if (!status.is_looking_at_block) {
		throw exception("UnrealCraftMPBPerformer::goToLine:未看向方块");
	}
	else {
		//若未到达指定列，则向右平移
		if (status.block_info.block_pos.x != line_x) {
			performer->keyEvent(ASCIIKeyCode::D, KeyEvent::KeyDown);
		}
	}
	while (status.block_info.block_pos.x > line_x) {
		status = getPlayerStatus();usleep(50);
	}
	performer->keyEvent(ASCIIKeyCode::D, KeyEvent::KeyUp);usleep(500);
}

void UnrealCraftMPBPerformer::goToBoard()
{
	/*performer->useInstruction("/pw jlu7"); usleep(20000);*/
	pwTp("jlu7");
	closeFly();
	fly();
}

void UnrealCraftMPBPerformer::refreshPackage()
{
	//刷新之前要把鼠标移开，不然遮挡视线
	POINT mouse_pos = performer->getMousePosition();
	performer->moveMouseToPoint(0, 0, false);usleep(200);
	Mat img;
	performer->getWindowPic(img);
	performer->getPackage()->setPackageStatus(PackageStatus::USE_SMALL_BOX);
	performer->readPackage(img);
	performer->readContain(img, ender_chest);
	performer->moveMouseToPoint(mouse_pos.x, mouse_pos.y);usleep(400);
}

void UnrealCraftMPBPerformer::recycleItem()
{
	usleep(2000);
	//先刷新背包
	openPackage();
	refreshPackage();
	auto package = performer->getPackage();
	package->setPackageStatus(PackageStatus::USE_SMALL_BOX);

	//先把末影箱的东西转移到背包
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyDown); usleep(500);
	auto points = ender_chest.getAllLatticePOINT();
	for (auto p : points) {
		auto& lattice = ender_chest.getLattice(p.x, p.y);
		//这段代码导致了末影箱清理不彻底
		//if (lattice.isHasKnownItem()) {
		//	////若背包放得下，则放入
		//	//if (package->addItemByShift(lattice.getItem(), lattice.getNum())) {
		//	//	lattice.eraseItem();
		//	//}
		//	////放不下，则停止转移
		//	//else break;

		//	lattice.eraseItem();

		//}
		auto pos = ender_chest.getLatticeRelativeMidPos(p.x, p.y);
		performer->moveMouseAndClickLeft(pos.x, pos.y, false);
	}
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyUp); usleep(500);
	closePackage();
	//打开垃圾桶
	/*performer->clickKey(ASCIIKeyCode::V, 0, 800);
	performer->moveMouseAndClickLeft(1075, 535, false); usleep(1000);
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyDown); usleep(500);*/
	performer->useInstruction("/dispose"); usleep(2000);
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyDown); usleep(500);
	//放入垃圾
	points = package->getAllLatticePOINT();
	for (auto p : points) {
		auto& lattice = package->getLattice(p.x, p.y);
		//if (!lattice.isEmpty()) {
			lattice.eraseItem();
			auto pos = package->getLatticeRelativeMidPos(p.x, p.y);
			performer->moveMouseAndClickLeft(pos.x, pos.y, false);
		//}
	}
	//结束
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyUp); usleep(500);
	closePackage();
}

void UnrealCraftMPBPerformer::getItemMap(map<string, int> need_map)
{
	//goToSpawn();
	//颜色物品map转mc物品map
	map<string,int> mc_item_map;
	for (auto pair : need_map) {
		mc_item_map[convert(pair.first).name] = pair.second;
	}
	
	//performer->useInstruction("/pw wnol8"); usleep(20000);
	pwTp("wnol8");
	getter.getItemMap(mc_item_map); usleep(2000);

}

const MCItem& UnrealCraftMPBPerformer::convert(string name)const
{
	return converter.convert(name);
}

void UnrealCraftMPBPerformer::arrangePackage(const vector<ColorItem>& line, int index)
{
	//Logger::log("UnrealCraftMPBPerformer::arrangePackage\n", performer->getPackageInfo());
	openPackage();	//打开背包
	POINT mouse_pos = performer->getMousePosition();	//记录鼠标初始位置，关闭背包前要复原

	vector<bool> is_used(9, false);	//标记口袋栏是否被使用的数组
	int pocket_used = 0;	//记录有多少口袋栏被使用
	int index_copy = index;
	map<string, int> pocket_map;	//记录口袋栏有多少mc物品
 
	while (pocket_used < 9 && index_copy < line.size())
	{
		const MCItem& item = convert(line[index_copy].name);		//待寻找的物品
		//Logger::log("UnrealCraftMPBPerformer::arrangePackage", to_string(index_copy) + " " + item.name);
		//Shower::showMap(pocket_map);
		//for (auto b : is_used) cout << boolTostr(b) << " ";
		//cout << endl;
		//Logger::log("UnrealCraftMPBPerformer::arrangePackage\n", performer->getPackageInfo());
		//若口袋栏有该物品，则减少一个物品，然后index增加
		if (isPocketMapHas(pocket_map, item.name, index_copy)) continue;
		POINT item_point = findUseAbleMCItemPOINT(item, is_used);

		//没找到物品报错
		if (item_point.y == 0)
			ThrowException::throwException("UnrealCraftMPBPerformer::arrangePackage", "缺乏物品:" + item.name);

		//如果找到的物品就在口袋栏中，则直接添加，不需要实际操作
		if (item_point.y == 4)ifMCItemInPocket(pocket_map, item_point, is_used, pocket_used);
		//如果不在口袋栏中，则需要实际操作
		else ifMCItemNotInPocket(pocket_map, item_point, is_used, pocket_used);
	}
	performer->moveMouseToPoint(mouse_pos.x, mouse_pos.y);
	usleep(200);
	performer->open_Or_closePackage();	//关闭背包
	usleep(1000);
}

bool UnrealCraftMPBPerformer::isPocketMapHas(map<string, int>& map, const string& item_name, int& index)
{
	if (map.count(item_name) &&map.at(item_name) > 0) {
		map.at(item_name)--;
		index++;	//只有消耗了口袋物品才可以index增加
		return true;
	}
	return false;
}

POINT UnrealCraftMPBPerformer::findUseAbleMCItemPOINT(const MCItem& item, const vector<bool>& is_used)
{
	vector<POINT> points = findAllMCItem(item);		//获取item所有坐标
	//对坐标排序，y==4的优先，否则数量多的优先，对于y == 4的则是数量少优先
	sort(points.begin(), points.end(), [=](POINT p1, POINT p2) {	
		if (p1.y == 4 && p2.y != 4) return true;
		else if (p1.y != 4 && p2.y == 4) return false;
		else if (p1.y == 4 && p2.y == 4) {
			if (getLattice(p1.x, p1.y).getNum() != getLattice(p2.x, p2.y).getNum())
				return getLattice(p1.x, p1.y).getNum() < getLattice(p2.x, p2.y).getNum();
			else
				return p1.x < p2.x;
		}
		else if(p1.y!=4&&p2.y!=4)
		{
			if (getLattice(p1.x, p1.y).getNum() != getLattice(p2.x, p2.y).getNum())
				return getLattice(p1.x, p1.y).getNum() > getLattice(p2.x, p2.y).getNum();
			else
				return p1.x < p2.x;
		}	
		});
	//sort(points.begin(), points.end(), [=](POINT p1, POINT p2) {	//对坐标排序，y==4的优先，否则数量少的优先
	//	if (p1.y == 4 && p2.y != 4) return true;
	//	else if (p1.y != 4 && p2.y == 4) return false;
	//	else {
	//		if (getLattice(p1.x, p1.y).getNum() != getLattice(p2.x, p2.y).getNum())
	//			return getLattice(p1.x, p1.y).getNum() < getLattice(p2.x, p2.y).getNum();
	//		else
	//			return p1.x < p2.x;
	//	}
	//	});

	POINT item_point = { 0,0 };		//合适的item坐标
	//寻找合适的item坐标
	auto iter = find_if(points.begin(), points.end(), [&is_used](POINT p) {
		return !(p.y == 4 && is_used[p.x - 1]);	//不能是在口袋栏已使用的坐标
		});
	if (iter != points.end()) item_point = *iter;
	return item_point;
}

void UnrealCraftMPBPerformer::ifMCItemInPocket(
	map<string, int>& pocket_map,POINT item_point,vector<bool>& is_used,int& pocket_used)
{
	Lattice& lattice = getLattice(item_point.x, item_point.y);
	//向口袋物品图添加物品
	MapCounter::addToMap(pocket_map,lattice.getItem().name, lattice.getNum());
	//更新已使用口袋
	is_used[item_point.x - 1] = true;
	pocket_used++;
}

void UnrealCraftMPBPerformer::ifMCItemNotInPocket(
	map<string,int>& pocket_map,POINT item_point,vector<bool>& is_used,int& pocket_used)
{
	//若找到的物品不在口袋栏中，则除了数据操作还需要实际操作
	//寻找空闲口袋
	int pocket_free = 0;	//空闲的口袋（从1开始）
	for (int i = 0; i < is_used.size(); i++) {
		if (!is_used[i]) {
			pocket_free = i + 1; break;
		}
	}

	//数据操作
	//向口袋物品图添加物品
	Lattice& lattice = getLattice(item_point.x, item_point.y);
	MapCounter::addToMap(pocket_map, lattice.getItem().name, lattice.getNum());
	//背包进行数据交换
	exchangeLatticesItem(getLattice(pocket_free, 4), getLattice(item_point.x, item_point.y));

	//实际操作
	//执行背包物品交换操作
	POINT item_pos = getLatticeRelativeMidPos(item_point.x, item_point.y);		//获取物品的位置
	performer->moveMouseToPoint(item_pos.x, item_pos.y, false); usleep(200);
	performer->clickNumberKey(pocket_free); usleep(200);
	//更新已使用口袋
	is_used[pocket_free - 1] = true;
	pocket_used++;
}


POINT UnrealCraftMPBPerformer::findOneMCItem(const MCItem& item) const
{
	vector<POINT> points = findAllMCItem(item);
	if(points.empty()) 
		ThrowException::throwException("UnrealCraftMPBPerformer::findOneMCItem", "缺乏物品:" + item.name);
	
	//对坐标排序，y==4的优先，否则数量多的优先，相等则x值小优先，对于y==4的则是数量少优先
	sort(points.begin(), points.end(), [=](POINT p1, POINT p2) {	
		if (p1.y == 4 && p2.y != 4) return true;
		else if (p1.y != 4 && p2.y == 4) return false;
		else if (p1.y == 4 && p2.y == 4) {
			if (getLattice(p1.x, p1.y).getNum() != getLattice(p2.x, p2.y).getNum())
				return getLattice(p1.x, p1.y).getNum() < getLattice(p2.x, p2.y).getNum();
			else
				return p1.x < p2.x;
		}
		else if (p1.y != 4 && p2.y != 4)
		{
			if (getLattice(p1.x, p1.y).getNum() != getLattice(p2.x, p2.y).getNum())
				return getLattice(p1.x, p1.y).getNum() > getLattice(p2.x, p2.y).getNum();
			else
				return p1.x < p2.x;
		}
		});

	//排序方式是，优先口袋栏，然后是的数量多的格子，再然后是x值小的格子
	/*sort(points.begin(), points.end(), [=](POINT a, POINT b) {
		if (a.y == 4 && b.y != 4) return true;
		else if (a.y != 4 && b.y == 4) return false;
		else {
			if (getLattice(a.x, a.y).getNum() != getLattice(b.x, b.y).getNum())
				return getLattice(a.x, a.y).getNum() < getLattice(b.x, b.y).getNum();
			else
				return a.x < b.x;
		}
		});*/
	return points[0];
	

	//POINT p;
	////先在背包里找
	//p = performer->getPackage()->findFirsItemFirstFromRow4(item);
	//if (p.y != 0) return p;
	////再在末影箱里找
	//p = ender_chest.findFirstItem(item);
	//if (p.y != 0) {//注意末影箱的y坐标
	//	p.y += 4;
	//	return p;
	//}
	//ThrowException::throwException("UnrealCraftMPBPerformer::findOneMCItem", "缺乏物品:" + item.name);
}

vector<POINT> UnrealCraftMPBPerformer::findAllMCItem(const MCItem& item) const
{
	vector<POINT> result;
	vector<POINT> package = performer->getPackage()->findItem(item);
	vector<POINT> ender_chest = this->ender_chest.findItem(item);
	for (auto& p : ender_chest) p.y += 4;//注意末影箱的y坐标
	result.insert(result.end(), package.begin(), package.end());
	result.insert(result.end(), ender_chest.begin(), ender_chest.end());
	return result;
}

POINT UnrealCraftMPBPerformer::getLatticeRelativeMidPos(int x, int y) const
{
	if (1 <= y && y <= 4) return performer->getPackage()->getLatticeRelativeMidPos(x, y);
	if (5 <= y && y <= 7) return ender_chest.getLatticeRelativeMidPos(x, y - 4);
	ThrowException::throwException("UnrealCraftMPBPerformer::getLatticeRelativeMidPos", "范围错误:" + std::to_string(x) + " " + std::to_string(y));
}

Lattice& UnrealCraftMPBPerformer::getLattice(int x, int y)
{
	if (1 <= y && y <= 4) return performer->getPackage()->getLattice(x, y);
	if (5 <= y && y <= 7) return ender_chest.getLattice(x, y - 4);
	ThrowException::throwException("UnrealCraftMPBPerformer::getLattice",
		"范围错误:" + std::to_string(x) + " " + std::to_string(y));

}

const Lattice& UnrealCraftMPBPerformer::getLattice(int x, int y) const
{
	if (1 <= y && y <= 4) return performer->getPackage()->getLattice(x, y);
	if (5 <= y && y <= 7) return ender_chest.getLattice(x, y - 4);
	ThrowException::throwException("UnrealCraftMPBPerformer::getLattice",
		"范围错误:" + std::to_string(x) + " " + std::to_string(y));
}

void UnrealCraftMPBPerformer::tp(
	string instruction, int tp_judge_distance, int before_delay_militime, int end_delay_militime)
{
	//等待玩家完全停止
	usleep(before_delay_militime);
	do
	{
		Mat img;
		PlayerPos old_pos;
		performer->getF3Pic(img);
		performer->analysisPic(img);
		if (!performer->getPlayerPosition(old_pos)) {
			break;
		}
		performer->useInstruction(instruction);	usleep(500);
		//不断等待角色长距离移动，直至超时
		tc.begin();
		do {
			performer->getF3Pic(img);
			performer->analysisPic(img);
			PlayerPos new_pos;
			if (!performer->getPlayerPosition(new_pos)) {
				break;
			}
			//长距离移动，结束
			if (countDistance(old_pos.x,old_pos.y,old_pos.z,new_pos.x,new_pos.y,new_pos.z)>tp_judge_distance) {
				usleep(end_delay_militime);
				return;
			}
			usleep(100);
		} while (tc.end() < MAX_WAIT_MINITIME);
	} while (false);

	ThrowException::throwException(__FUNCTION__, instruction+"传送错误!");
}

void UnrealCraftMPBPerformer::pwTp(string destination)
{
	tp("/pw " + destination, 2, 3000, 3000);
}

void UnrealCraftMPBPerformer::homeTp(string home_name)
{
	tp("/home " + home_name, 2, 1000, 1000);
}

//void UnrealCraftMPBPerformer::goToSpawn()
//{
//	performer->clickKey(ASCIIKeyCode::V, 0, 1000);
//	performer->moveMouseAndClickLeft(800, 450,false); usleep(1000);
//	performer->moveMouseAndClickLeft(800, 350,false); usleep(8000);
//}
//
//void UnrealCraftMPBPerformer::goToSurviveArea()
//{
//	performer->clickKey(ASCIIKeyCode::V, 0, 800);
//	performer->moveMouseAndClickLeft(800, 350,false); usleep(1000);
//	performer->moveMouseAndClickLeft(950, 350,false); usleep(1000);
//	performer->moveMouseAndClickLeft(870, 570,false); usleep(8000);
//}

void UnrealCraftMPBPerformer::fly()
{
	performer->clickKey(ASCIIKeyCode::SPACEBAR, 100, 100);
	performer->clickKey(ASCIIKeyCode::SPACEBAR, 100, 100);
}

void UnrealCraftMPBPerformer::closeFly()
{
	performer->clickKey(ASCIIKeyCode::SHIFT, 500,500);
}

double UnrealCraftMPBPerformer::countDistance(double x1, double y1, double z1, double x2, double y2, double z2)
{
	return sqrt(
		(x1 - x2) * (x1 - x2) +
		(y1 - y2) * (y1 - y2) +
		(z1 - z2) * (z1 - z2)
	);
}

void UnrealCraftMPBPerformer::openPackage()
{
	performer->useInstruction("/enderchest");
	performer->getPackage()->setPackageStatus(PackageStatus::USE_SMALL_BOX);
	//等待背包打开，打开标志为F3不可读
	tc.begin();
	do
	{
		Mat img;
		performer->getWindowPic(img);
		performer->analysisPic(img);
		if (!performer->ifF3CanRead()) {
			usleep(200);
			return;
		}
		usleep(100);
	} while (tc.end()<MAX_WAIT_MINITIME);
	ThrowException::throwException(__FUNCTION__, "背包打开超时!");
}

void UnrealCraftMPBPerformer::closePackage()
{
	performer->open_Or_closePackage();
	//等待背包关闭，关闭标志为F3可读
	tc.begin();
	do
	{
		Mat img;
		performer->getWindowPic(img);
		performer->analysisPic(img);
		if (performer->ifF3CanRead()) {
			usleep(200);
			return;
		}
		usleep(100);
	} while (tc.end() < MAX_WAIT_MINITIME);
	ThrowException::throwException(__FUNCTION__, "背包关闭超时!");
}
