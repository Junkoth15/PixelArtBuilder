#include "UnrealCraftItemMapGetter.h"
#include"MCItemMapFactory.h"
#include"Tools.h"

UnrealCraftItemMapGetter::UnrealCraftItemMapGetter(
	ImagePerformer* performer, Box* ender_chest, string mc_item_map_path):
	performer(performer),
	ender_chest(ender_chest),
	item_map(&MCItemMapFactory::getMCItemMap(mc_item_map_path))
{
}

void UnrealCraftItemMapGetter::getItemMap(map<string, int> map)
{
	need_map = map;
	need_map_copy = map;
	setStatus(Status::Original);
	mainRoll();
}


void UnrealCraftItemMapGetter::mainRoll()
{
	while (true) {
		switch (status)
		{
		case UnrealCraftItemMapGetter::Status::Original:original();
			break;
		case UnrealCraftItemMapGetter::Status::Selecting:selecting();
			break;
		case UnrealCraftItemMapGetter::Status::Buying:buying();
			break;
		case UnrealCraftItemMapGetter::Status::Arranging:arranging();
			break;
		case UnrealCraftItemMapGetter::Status::Checking:checking();
			break;
		case UnrealCraftItemMapGetter::Status::End:return;
			break;
		default:
			break;
		}
	}
}

void UnrealCraftItemMapGetter::setStatus(Status status)
{
	this->status = status;
}

void UnrealCraftItemMapGetter::original()
{
	Logger::log("UnrealCraftItemMapGetter::original", "need_map:");
	Shower::showMap(need_map);
	Logger::log("UnrealCraftItemMapGetter::original", "");
	page = 1;
	next_page_is_bigger = true;
	//读取末影箱与背包
	openEnderChest();
	readEnderChestAndPackage();
	usleep(400);
	closeEnderChest();
	usleep(400);
	openShop();
	usleep(1000);
	setStatus(Status::Selecting);
}

void UnrealCraftItemMapGetter::selecting()
{
	Logger::log("UnrealCraftItemMapGetter::selecting", "");
	while (true) {
		//读商店
		readShop();
		//查找本页有无所需物品
		for (auto pair : need_map) {
			string item_name = pair.first;
			POINT point = shop.findFirstItem(item_map->item_map.at(item_name));
			//有所需物品，打开购买页面
			if (point.y != 0) {
				item_to_buy = item_name;
				POINT good_pos = shop.getLatticeRelativeMidPos(point.x, point.y);
				performer->moveMouseAndClickLeft(good_pos.x, good_pos.y, false);usleep(800);
				setStatus(Status::Buying);
				return;
			}
		}
		//没有所需物品，翻到下一页
		jumpToNextPage();
	}
}

void UnrealCraftItemMapGetter::buying()
{
	Logger::log("UnrealCraftItemMapGetter::buying", "");
	int num_to_buy = need_map.at(item_to_buy);
	const MCItem& item = item_map->item_map.at(item_to_buy);
	auto package = performer->getPackage();
	//如果放得下且还需要买，就加一组
	while (num_to_buy>0&&package->testAddItemByShift(item, 64)) {
		addOneGroup();
		addOneGroupToPackage(item);
		num_to_buy -= 64;
	}
	//买完了或者背包满了，结算
	//结算之前把多出来的一个去掉
	//修改数据
	if (num_to_buy == 0) need_map.erase(item_to_buy);
	else need_map.at(item_to_buy) = num_to_buy;
	//实际操作
	//若背包已满，则不用减一，否则需要减一
	if (package->testAddItemByShift(item, 1)) {
		removeOne();
	}
	pay();
	//若需求空则跳转到检查状态
	if (need_map.empty()) {
		closeShop();
		setStatus(Status::Checking);
	}
	//若背包满则跳转到整理状态，否则跳转到选择状态
	else if (isPackageFull()) {
		closeShop();
		setStatus(Status::Arranging);
	}
	else setStatus(Status::Selecting);
}

void UnrealCraftItemMapGetter::arranging()
{
	Logger::log("UnrealCraftItemMapGetter::arranging", "");
	//打开末影箱
	openEnderChest();
	//刷新背包和末影箱
	readEnderChestAndPackage();
	//按下SHIFT
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyDown);usleep(500);
	//转移操作
	auto package = performer->getPackage();
	package->setPackageStatus(PackageStatus::USE_SMALL_BOX);
	auto all_points = package->getAllLatticePOINT();
	for (auto p : all_points) {
		//将有物品的格子的物品转移到末影箱
		auto& lattice = package->getLattice(p.x, p.y);
		if (lattice.isHasKnownItem()) {
			//如果末影箱放得下，则转移
			if (ender_chest->addItemByShift(lattice.getItem(), lattice.getNum())) {
				lattice.eraseItem();
				POINT pos = package->getLatticeRelativeMidPos(p.x, p.y);
				performer->moveMouseAndClickLeft(pos.x, pos.y, false);
			}
		}
	}
	usleep(400);
	//松开SHIFT
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyUp);usleep(500);
	closeEnderChest();
	setStatus(Status::Original);
}

void UnrealCraftItemMapGetter::checking()
{
	Logger::log("UnrealCraftItemMapGetter::checking", "");
	openEnderChest();
	readEnderChestAndPackage();

	//统计
	map<string, int> own_map;
	Contain* contain=nullptr;
	//进行两轮统计，第一次统计背包，第二次统计末影箱
	for (int i = 0; i < 2; i++) {
		if (i == 0) contain = performer->getPackage().get();
		if (i == 1) contain = ender_chest;
		auto points = contain->getAllLatticePOINT();
			for (auto p : points) {
			auto& lattice = contain->getLattice(p.x, p.y);
			auto& item = lattice.getItem();
			//若格子有物品，则将物品增加或添加到图中
			if (lattice.isHasKnownItem()) {
				if (own_map.count(item.name)) {
					own_map.at(item.name) += lattice.getNum();
				}
				else own_map[item.name] = lattice.getNum();
			}
		}

	}
	Logger::log("UnrealCraftItemMapGetter::checking", "need_map_copy:");
	Shower::showMap(need_map_copy);
	Logger::log("UnrealCraftItemMapGetter::checking", "own_map:");
	Shower::showMap(own_map);

	map<string, int> lack_map = mapMinus(need_map_copy, own_map);
	closeEnderChest();
	//没有还缺的物品，跳转到完成状态
	if (lack_map.empty()) {
		setStatus(Status::End);
	}
	else {
		need_map = lack_map;
		need_map_copy = lack_map;
		setStatus(Status::Original);
	}
}

void UnrealCraftItemMapGetter::end()
{
	Logger::log("UnrealCraftItemMapGetter::end", "");
}

void UnrealCraftItemMapGetter::openShop()
{
	performer->mouseEvent(MouseEvent::ClickRight);usleep(2000);
	performer->clickNumberKey(1);usleep(2000);
	performer->clickKey(ASCIIKeyCode::F, 0, 0);usleep(2000);
	performer->clickKey(ASCIIKeyCode::F, 0, 0); usleep(2000);
}

void UnrealCraftItemMapGetter::closeShop()
{
	performer->open_Or_closePackage(); usleep(2000);
}

void UnrealCraftItemMapGetter::readShop()
{
	auto p = performer->getMousePosition();
	performer->moveMouseToPoint(0, 0, false);
	usleep(200);
	//读箱子和背包，注意背包设置为大箱子模式
	CImage img;
	performer->getWindowPic(img);
	performer->readContain(img,shop);
	performer->getPackage()->setPackageStatus(PackageStatus::USE_BIG_BOX);
	performer->readPackage(img);
	performer->moveMouseToPoint(p.x, p.y);
	usleep(400);
}

void UnrealCraftItemMapGetter::jumpToNextPage()
{
	if (page == 7) next_page_is_bigger = false;
	if (page == 1) next_page_is_bigger = true;
	if (next_page_is_bigger) {
		performer->moveMouseAndClickLeft(1010, 485, false);
		page++;
	}
	else {
		performer->moveMouseAndClickLeft(725, 485, false);
		page--;
	}
	usleep(1000);
}

bool UnrealCraftItemMapGetter::isPackageFull()
{
	auto package = performer->getPackage();
	auto points = package->getAllLatticePOINT();
	for (auto p : points) {
		if (package->getLattice(p.x, p.y).isEmpty()) return false;
	}
	return true;
}

void UnrealCraftItemMapGetter::addOneGroup()
{
	auto p = shop.getLatticeRelativeMidPos(9, 5);
	performer->moveMouseAndClickLeft(p.x, p.y, false);
	usleep(600);
}

void UnrealCraftItemMapGetter::removeOne()
{
	auto p = shop.getLatticeRelativeMidPos(3, 5);
	performer->moveMouseAndClickLeft(p.x, p.y, false);
	usleep(600);
}

void UnrealCraftItemMapGetter::pay()
{
	performer->moveMouseAndClickLeft(1010, 485, false);
	usleep(600);
}

void UnrealCraftItemMapGetter::addOneGroupToPackage(const MCItem& item)
{
	auto package = performer->getPackage();
	for (int y = 4; y >= 1; y--) {
		for (int x = 1; x <= 9; x++) {
			auto& lattice = package->getLattice(x, y);
			if (lattice.isEmpty()) {
				lattice.addItem(item, 64);
				return;
			}
		}
	}
}

void UnrealCraftItemMapGetter::openEnderChest()
{
	performer->useInstruction("/enderchest");
	usleep(3000);
}

void UnrealCraftItemMapGetter::readEnderChestAndPackage()
{
	//读取末影箱和背包，注意移动鼠标和设置为小箱子模式
	auto p = performer->getMousePosition();
	performer->moveMouseToPoint(0, 0, false);
	usleep(200);
	CImage img;
	performer->getWindowPic(img);
	performer->getPackage()->setPackageStatus(PackageStatus::USE_SMALL_BOX);
	performer->readPackage(img);
	performer->readContain(img, *ender_chest);
	performer->moveMouseToPoint(p.x, p.y);
	usleep(200);
}

void UnrealCraftItemMapGetter::closeEnderChest()
{
	performer->open_Or_closePackage();
	usleep(1000);
}


map<string, int> UnrealCraftItemMapGetter::mapMinus(const map<string, int>& larger, const map<string, int>& smaller)
{
	map<string, int> result = larger;
	for (auto pair : smaller) {
		if (result.count(pair.first)) {
			result.at(pair.first) -= pair.second;
			if (result.at(pair.first) <= 0) {
				result.erase(pair.first);
			}
		}
	}
	return result;
}
