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
	//�ӱ����л�ȡ��Ʒ����
	const MCItem& item = convert(line[item_index].name);
	POINT item_point = findOneMCItem(item);
	//��Ʒ����Ʒ���У�ֱ���л���
	if (item_point.y == 4) {
		if (performer->getHand() != item_point.x) {
			performer->changeHand(item_point.x);
			performer->setHand(item_point.x);
		}
	}
	//��Ʒ������Ʒ���У�ȥ����Ѱ��
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

	//����������
	bool package_full = false;
	for (auto& pair : item_map) {
		auto& item = convert(pair.first);
		int& num = pair.second;
		//ÿ�η�һ�飬����û�����ܷ�
		while (num > 0 && !package_full) {
			//���óɹ����ۼ�������ʧ�����˳�
			if (package.addItemByShift(item, std::min(num, 64))) num -= std::min(num, 64);
			else package_full = true;
		}
		if (package_full) break;
	}

	//����ĩӰ�����
	bool ender_box_full = false;
	for (auto& pair : item_map) {
		auto& item = convert(pair.first);
		int& num = pair.second;
		//ÿ�η�һ�飬û�����ܷ�
		while (num > 0 && !ender_box_full) {
			//���óɹ����ۼ�������ʧ�����˳�
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

	int line_x = mpb_info.board_first_line_x + line;//Ŀ���ж�Ӧ��x����
	if (!status.is_looking_at_block) {
		throw exception("UnrealCraftMPBPerformer::goToLine:δ���򷽿�");
	}
	else {
		//��δ����ָ���У�������ƽ��
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
	//ˢ��֮ǰҪ������ƿ�����Ȼ�ڵ�����
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
	//��ˢ�±���
	openPackage();
	refreshPackage();
	auto package = performer->getPackage();
	package->setPackageStatus(PackageStatus::USE_SMALL_BOX);

	//�Ȱ�ĩӰ��Ķ���ת�Ƶ�����
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyDown); usleep(500);
	auto points = ender_chest.getAllLatticePOINT();
	for (auto p : points) {
		auto& lattice = ender_chest.getLattice(p.x, p.y);
		//��δ��뵼����ĩӰ����������
		//if (lattice.isHasKnownItem()) {
		//	////�������ŵ��£������
		//	//if (package->addItemByShift(lattice.getItem(), lattice.getNum())) {
		//	//	lattice.eraseItem();
		//	//}
		//	////�Ų��£���ֹͣת��
		//	//else break;

		//	lattice.eraseItem();

		//}
		auto pos = ender_chest.getLatticeRelativeMidPos(p.x, p.y);
		performer->moveMouseAndClickLeft(pos.x, pos.y, false);
	}
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyUp); usleep(500);
	closePackage();
	//������Ͱ
	/*performer->clickKey(ASCIIKeyCode::V, 0, 800);
	performer->moveMouseAndClickLeft(1075, 535, false); usleep(1000);
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyDown); usleep(500);*/
	performer->useInstruction("/dispose"); usleep(2000);
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyDown); usleep(500);
	//��������
	points = package->getAllLatticePOINT();
	for (auto p : points) {
		auto& lattice = package->getLattice(p.x, p.y);
		//if (!lattice.isEmpty()) {
			lattice.eraseItem();
			auto pos = package->getLatticeRelativeMidPos(p.x, p.y);
			performer->moveMouseAndClickLeft(pos.x, pos.y, false);
		//}
	}
	//����
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyUp); usleep(500);
	closePackage();
}

void UnrealCraftMPBPerformer::getItemMap(map<string, int> need_map)
{
	//goToSpawn();
	//��ɫ��Ʒmapתmc��Ʒmap
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
	openPackage();	//�򿪱���
	POINT mouse_pos = performer->getMousePosition();	//��¼����ʼλ�ã��رձ���ǰҪ��ԭ

	vector<bool> is_used(9, false);	//��ǿڴ����Ƿ�ʹ�õ�����
	int pocket_used = 0;	//��¼�ж��ٿڴ�����ʹ��
	int index_copy = index;
	map<string, int> pocket_map;	//��¼�ڴ����ж���mc��Ʒ
 
	while (pocket_used < 9 && index_copy < line.size())
	{
		const MCItem& item = convert(line[index_copy].name);		//��Ѱ�ҵ���Ʒ
		//Logger::log("UnrealCraftMPBPerformer::arrangePackage", to_string(index_copy) + " " + item.name);
		//Shower::showMap(pocket_map);
		//for (auto b : is_used) cout << boolTostr(b) << " ";
		//cout << endl;
		//Logger::log("UnrealCraftMPBPerformer::arrangePackage\n", performer->getPackageInfo());
		//���ڴ����и���Ʒ�������һ����Ʒ��Ȼ��index����
		if (isPocketMapHas(pocket_map, item.name, index_copy)) continue;
		POINT item_point = findUseAbleMCItemPOINT(item, is_used);

		//û�ҵ���Ʒ����
		if (item_point.y == 0)
			ThrowException::throwException("UnrealCraftMPBPerformer::arrangePackage", "ȱ����Ʒ:" + item.name);

		//����ҵ�����Ʒ���ڿڴ����У���ֱ����ӣ�����Ҫʵ�ʲ���
		if (item_point.y == 4)ifMCItemInPocket(pocket_map, item_point, is_used, pocket_used);
		//������ڿڴ����У�����Ҫʵ�ʲ���
		else ifMCItemNotInPocket(pocket_map, item_point, is_used, pocket_used);
	}
	performer->moveMouseToPoint(mouse_pos.x, mouse_pos.y);
	usleep(200);
	performer->open_Or_closePackage();	//�رձ���
	usleep(1000);
}

bool UnrealCraftMPBPerformer::isPocketMapHas(map<string, int>& map, const string& item_name, int& index)
{
	if (map.count(item_name) &&map.at(item_name) > 0) {
		map.at(item_name)--;
		index++;	//ֻ�������˿ڴ���Ʒ�ſ���index����
		return true;
	}
	return false;
}

POINT UnrealCraftMPBPerformer::findUseAbleMCItemPOINT(const MCItem& item, const vector<bool>& is_used)
{
	vector<POINT> points = findAllMCItem(item);		//��ȡitem��������
	//����������y==4�����ȣ���������������ȣ�����y == 4����������������
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
	//sort(points.begin(), points.end(), [=](POINT p1, POINT p2) {	//����������y==4�����ȣ����������ٵ�����
	//	if (p1.y == 4 && p2.y != 4) return true;
	//	else if (p1.y != 4 && p2.y == 4) return false;
	//	else {
	//		if (getLattice(p1.x, p1.y).getNum() != getLattice(p2.x, p2.y).getNum())
	//			return getLattice(p1.x, p1.y).getNum() < getLattice(p2.x, p2.y).getNum();
	//		else
	//			return p1.x < p2.x;
	//	}
	//	});

	POINT item_point = { 0,0 };		//���ʵ�item����
	//Ѱ�Һ��ʵ�item����
	auto iter = find_if(points.begin(), points.end(), [&is_used](POINT p) {
		return !(p.y == 4 && is_used[p.x - 1]);	//�������ڿڴ�����ʹ�õ�����
		});
	if (iter != points.end()) item_point = *iter;
	return item_point;
}

void UnrealCraftMPBPerformer::ifMCItemInPocket(
	map<string, int>& pocket_map,POINT item_point,vector<bool>& is_used,int& pocket_used)
{
	Lattice& lattice = getLattice(item_point.x, item_point.y);
	//��ڴ���Ʒͼ�����Ʒ
	MapCounter::addToMap(pocket_map,lattice.getItem().name, lattice.getNum());
	//������ʹ�ÿڴ�
	is_used[item_point.x - 1] = true;
	pocket_used++;
}

void UnrealCraftMPBPerformer::ifMCItemNotInPocket(
	map<string,int>& pocket_map,POINT item_point,vector<bool>& is_used,int& pocket_used)
{
	//���ҵ�����Ʒ���ڿڴ����У���������ݲ�������Ҫʵ�ʲ���
	//Ѱ�ҿ��пڴ�
	int pocket_free = 0;	//���еĿڴ�����1��ʼ��
	for (int i = 0; i < is_used.size(); i++) {
		if (!is_used[i]) {
			pocket_free = i + 1; break;
		}
	}

	//���ݲ���
	//��ڴ���Ʒͼ�����Ʒ
	Lattice& lattice = getLattice(item_point.x, item_point.y);
	MapCounter::addToMap(pocket_map, lattice.getItem().name, lattice.getNum());
	//�����������ݽ���
	exchangeLatticesItem(getLattice(pocket_free, 4), getLattice(item_point.x, item_point.y));

	//ʵ�ʲ���
	//ִ�б�����Ʒ��������
	POINT item_pos = getLatticeRelativeMidPos(item_point.x, item_point.y);		//��ȡ��Ʒ��λ��
	performer->moveMouseToPoint(item_pos.x, item_pos.y, false); usleep(200);
	performer->clickNumberKey(pocket_free); usleep(200);
	//������ʹ�ÿڴ�
	is_used[pocket_free - 1] = true;
	pocket_used++;
}


POINT UnrealCraftMPBPerformer::findOneMCItem(const MCItem& item) const
{
	vector<POINT> points = findAllMCItem(item);
	if(points.empty()) 
		ThrowException::throwException("UnrealCraftMPBPerformer::findOneMCItem", "ȱ����Ʒ:" + item.name);
	
	//����������y==4�����ȣ���������������ȣ������xֵС���ȣ�����y==4����������������
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

	//����ʽ�ǣ����ȿڴ�����Ȼ���ǵ�������ĸ��ӣ���Ȼ����xֵС�ĸ���
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
	////���ڱ�������
	//p = performer->getPackage()->findFirsItemFirstFromRow4(item);
	//if (p.y != 0) return p;
	////����ĩӰ������
	//p = ender_chest.findFirstItem(item);
	//if (p.y != 0) {//ע��ĩӰ���y����
	//	p.y += 4;
	//	return p;
	//}
	//ThrowException::throwException("UnrealCraftMPBPerformer::findOneMCItem", "ȱ����Ʒ:" + item.name);
}

vector<POINT> UnrealCraftMPBPerformer::findAllMCItem(const MCItem& item) const
{
	vector<POINT> result;
	vector<POINT> package = performer->getPackage()->findItem(item);
	vector<POINT> ender_chest = this->ender_chest.findItem(item);
	for (auto& p : ender_chest) p.y += 4;//ע��ĩӰ���y����
	result.insert(result.end(), package.begin(), package.end());
	result.insert(result.end(), ender_chest.begin(), ender_chest.end());
	return result;
}

POINT UnrealCraftMPBPerformer::getLatticeRelativeMidPos(int x, int y) const
{
	if (1 <= y && y <= 4) return performer->getPackage()->getLatticeRelativeMidPos(x, y);
	if (5 <= y && y <= 7) return ender_chest.getLatticeRelativeMidPos(x, y - 4);
	ThrowException::throwException("UnrealCraftMPBPerformer::getLatticeRelativeMidPos", "��Χ����:" + std::to_string(x) + " " + std::to_string(y));
}

Lattice& UnrealCraftMPBPerformer::getLattice(int x, int y)
{
	if (1 <= y && y <= 4) return performer->getPackage()->getLattice(x, y);
	if (5 <= y && y <= 7) return ender_chest.getLattice(x, y - 4);
	ThrowException::throwException("UnrealCraftMPBPerformer::getLattice",
		"��Χ����:" + std::to_string(x) + " " + std::to_string(y));

}

const Lattice& UnrealCraftMPBPerformer::getLattice(int x, int y) const
{
	if (1 <= y && y <= 4) return performer->getPackage()->getLattice(x, y);
	if (5 <= y && y <= 7) return ender_chest.getLattice(x, y - 4);
	ThrowException::throwException("UnrealCraftMPBPerformer::getLattice",
		"��Χ����:" + std::to_string(x) + " " + std::to_string(y));
}

void UnrealCraftMPBPerformer::tp(
	string instruction, int tp_judge_distance, int before_delay_militime, int end_delay_militime)
{
	//�ȴ������ȫֹͣ
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
		//���ϵȴ���ɫ�������ƶ���ֱ����ʱ
		tc.begin();
		do {
			performer->getF3Pic(img);
			performer->analysisPic(img);
			PlayerPos new_pos;
			if (!performer->getPlayerPosition(new_pos)) {
				break;
			}
			//�������ƶ�������
			if (countDistance(old_pos.x,old_pos.y,old_pos.z,new_pos.x,new_pos.y,new_pos.z)>tp_judge_distance) {
				usleep(end_delay_militime);
				return;
			}
			usleep(100);
		} while (tc.end() < MAX_WAIT_MINITIME);
	} while (false);

	ThrowException::throwException(__FUNCTION__, instruction+"���ʹ���!");
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
	//�ȴ������򿪣��򿪱�־ΪF3���ɶ�
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
	ThrowException::throwException(__FUNCTION__, "�����򿪳�ʱ!");
}

void UnrealCraftMPBPerformer::closePackage()
{
	performer->open_Or_closePackage();
	//�ȴ������رգ��رձ�־ΪF3�ɶ�
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
	ThrowException::throwException(__FUNCTION__, "�����رճ�ʱ!");
}
