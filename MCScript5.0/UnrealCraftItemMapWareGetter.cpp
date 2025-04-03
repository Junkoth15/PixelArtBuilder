#include "UnrealCraftItemMapWareGetter.h"
#include"MCItemMapFactory.h"
#include"FileLoader.h"
#include"Tools.h"
#include<sstream>
map<string, int> UnrealCraftItemMapWareGetter::item_index_map;
string UnrealCraftItemMapWareGetter::warehouse;

int UnrealCraftItemMapWareGetter::MAX_WAIT_MILITIME=10000;

UnrealCraftItemMapWareGetter::UnrealCraftItemMapWareGetter(
	ImagePerformer* performer, Box* ender_chest, string mc_item_map_path, string config_path):
	performer(performer),
	ender_chest(ender_chest),
	box(BoxType::BIG),
	tc(TimeCounterMode::MILISECOND)
{
	load(mc_item_map_path, config_path);
}

void UnrealCraftItemMapWareGetter::getItemMap(map<string, int> map)
{
	init(map);
	mainRoll();
}

void UnrealCraftItemMapWareGetter::load(string mc_item_map_path, string config_path)
{
	item_map = &MCItemMapFactory::getMCItemMap(mc_item_map_path);
	if (item_index_map.empty()) {
		map<string, string> map = FileLoader::loadTXTMap(config_path);
		warehouse = map.at("�ֿ���");
		for (auto pair : map) {
			if (pair.first != "�ֿ���") {
				item_index_map.insert(std::make_pair(pair.first, std::stoi(pair.second)));
			}
		}
	}
}

void UnrealCraftItemMapWareGetter::init(map<string, int> map)
{
	setStatus(Status::Original);
	pos = Pos::NotKnow;
	need_vec.clear();
	for (auto pair : map) {
		need_vec.push_back(pair);
	}
	std::sort(need_vec.begin(), need_vec.end(), [this](const pair<string, int>& a, const pair<string, int>& b) {
		return item_index_map.at(a.first) < item_index_map.at(b.first);
		});
	need_vec_copy = need_vec;
	item_to_get_index = 0;
	lack_item = false;
}

void UnrealCraftItemMapWareGetter::mainRoll()
{
	while (true) {
		switch (status)
		{
		case UnrealCraftItemMapWareGetter::Status::Original:original();
			break;
		case UnrealCraftItemMapWareGetter::Status::Selecting:selecting();
			break;
		case UnrealCraftItemMapWareGetter::Status::Getting:getting();
			break;
		case UnrealCraftItemMapWareGetter::Status::Arranging:arranging();
			break;
		case UnrealCraftItemMapWareGetter::Status::Checking:checking();
			break;
		case UnrealCraftItemMapWareGetter::Status::End:return;
			break;
		default:
			break;
		}
	}
}

void UnrealCraftItemMapWareGetter::setStatus(Status status)
{
	this->status = status;
}

void UnrealCraftItemMapWareGetter::original()
{
	LogDebug("begin");
	LogDebug("need_map:\n"+getPairVectorStr(need_vec));
	//getPairVectorStr(need_vec);
	//��ȡĩӰ���뱳��
	openEnderChest();
	readEnderChestAndPackage();
	closeEnderChest();
	setStatus(Status::Selecting);
}

void UnrealCraftItemMapWareGetter::selecting()
{
	pair<string,int> name_num_pair = need_vec[item_to_get_index];
	static int first_item_x;
	LogDebug(name_num_pair.first+"*"+std::to_string(name_num_pair.second));


	//ȥ���ʵ�λ��
	goToSuitablePos(name_num_pair, first_item_x);

	//������Ʒ������ǰ
	int target_x,k;
	switch (pos)
	{
	case UnrealCraftItemMapWareGetter::Pos::Concreate:k = 1;
		break;
	case UnrealCraftItemMapWareGetter::Pos::Clay:k = 17;
		break;
	case UnrealCraftItemMapWareGetter::Pos::Other:k = 33;
		break;
	default:
		break;
	}
	target_x= first_item_x - (item_index_map.at(name_num_pair.first)-k) * 2;
	float max_x = target_x + 0.8, min_x = target_x -0.8;//���Ӧ�ô��ڵ�x���귶Χ

	enum class MoveStatus{Stop,Right,Left};
	MoveStatus move_status = MoveStatus::Stop;
	//��ѭ���������Ƿ����λ��
	while (true) {
		performer->keyEvent(ASCIIKeyCode::D, KeyEvent::KeyUp);
		performer->keyEvent(ASCIIKeyCode::A, KeyEvent::KeyUp);
		usleep(400);
		PlayerStatus status = getPlayerStatus();
		float player_x = status.player_pos.x;
		if (min_x < player_x && player_x < max_x) break;
		//��ѭ��������λ�õ���
		while (true) {
			PlayerStatus status = getPlayerStatus();
			float player_x = status.player_pos.x;
			if (min_x < player_x && player_x < max_x) break;
			if (player_x < max_x && move_status == MoveStatus::Right) {
				performer->keyEvent(ASCIIKeyCode::D, KeyEvent::KeyUp);
			}
			else if (player_x > min_x && move_status == MoveStatus::Left) {
				performer->keyEvent(ASCIIKeyCode::A, KeyEvent::KeyUp);
			}
			else if (player_x > max_x && move_status != MoveStatus::Right) {
				performer->keyEvent(ASCIIKeyCode::D, KeyEvent::KeyDown);
			}
			else if (player_x < min_x && move_status != MoveStatus::Left) {
				performer->keyEvent(ASCIIKeyCode::A, KeyEvent::KeyDown);
			}

		}
	}
	openBox();
	setStatus(Status::Getting);
}

void UnrealCraftItemMapWareGetter::getting()
{
	LogDebug("begin");
	//�ȶ�ȡ����
	readBox();
	pair<string, int>& name_num_pair = need_vec[item_to_get_index];
	const MCItem& item = item_map->item_map.at(name_num_pair.first);
	//Ѱ����Ҫ����Ʒ
	vector<POINT> points = box.findItem(item);
	shared_ptr<Package> package = performer->getPackage();
	shiftDown();
	for (auto p : points) {
		if (name_num_pair.second <= 0) {	//��������������
			item_to_get_index++;
			break;
		}
		if (!package->testAddItemByShift(item, 64)) break;		//����������������

		//��ȡ��Ʒ�����Ա�����������в���
		Lattice& lattice = box.getLattice(p.x, p.y);
		if (lattice.getNum() == 64) {
			getItemFromBox(p.x, p.y);
			package->addItemByShift(item, 64);
			name_num_pair.second -= 64;
		}
	}
	shiftUp();
	closeBox();
	//�˳�ѭ��������ԭ�򣺱����������������㣬��������

	//�����������ת�����״̬
	if (item_to_get_index >= need_vec.size()) setStatus(Status::Checking);
	//������������ת������״̬
	else if (isPackageFull()) setStatus(Status::Arranging);
	//������ת��ѡ��״̬
	else {
		//��û��ȫ�õ�������Ʒ����֪ͨȱ��Ʒ
		if (name_num_pair.second > 0)	lack_item = true;
		setStatus(Status::Selecting);
	}

}

void UnrealCraftItemMapWareGetter::arranging()
{
	LogDebug("begin");
	openEnderChest();	//��ĩӰ��
	readEnderChestAndPackage();	//ˢ�±�����ĩӰ��
	shiftDown();	//����SHIFT
	//ת�Ʋ���
	auto package = performer->getPackage();
	package->setPackageStatus(PackageStatus::USE_SMALL_BOX);
	auto all_points = package->getAllLatticePOINT();
	for (auto p : all_points) {
		//������Ʒ�ĸ��ӵ���Ʒת�Ƶ�ĩӰ��
		auto& lattice = package->getLattice(p.x, p.y);
		if (lattice.isHasKnownItem()) {
			//���ĩӰ��ŵ��£���ת��
			if (ender_chest->addItemByShift(lattice.getItem(), lattice.getNum())) {
				lattice.eraseItem();
				POINT pos = package->getLatticeRelativeMidPos(p.x, p.y);
				performer->moveMouseAndClickLeft(pos.x, pos.y, false);
			}
		}
	}
	usleep(400);
	shiftUp();	//�ɿ�SHIFT
	closeEnderChest();
	setStatus(Status::Original);
}

void UnrealCraftItemMapWareGetter::checking()
{
	LogDebug("begin");
	openEnderChest();
	readEnderChestAndPackage();

	//ͳ��
	map<string, int> own_map;
	Contain* contain = nullptr;
	//��������ͳ�ƣ���һ��ͳ�Ʊ������ڶ���ͳ��ĩӰ��
	for (int i = 0; i < 2; i++) {
		if (i == 0) contain = performer->getPackage().get();
		if (i == 1) contain = ender_chest;
		auto points = contain->getAllLatticePOINT();
		for (auto p : points) {
			auto& lattice = contain->getLattice(p.x, p.y);
			auto& item = lattice.getItem();
			//����������Ʒ������Ʒ���ӻ���ӵ�ͼ��
			if (lattice.isHasKnownItem()) {
				if (own_map.count(item.name)) {
					own_map.at(item.name) += lattice.getNum();
				}
				else own_map[item.name] = lattice.getNum();
			}
		}

	}
	map<string, int> need_map_copy;
	for (auto pair : need_vec_copy) {
		need_map_copy.insert(pair);
	}
	LogDebug("need_map_copy:\n" + Shower::getMapStr(need_map_copy));
	//Shower::showMap(need_map_copy);
	LogDebug("own_map:\n" + Shower::getMapStr(own_map));
	//Shower::showMap(own_map);

	map<string, int> lack_map = MapCounter::minusMap(need_map_copy, own_map);
	closeEnderChest();
	//û�л�ȱ����Ʒ����ת�����״̬
	if (lack_map.empty()) {
		setStatus(Status::End);
	}
	else {
		init(lack_map);
		setStatus(Status::Original);
	}
}

void UnrealCraftItemMapWareGetter::end()
{
	LogDebug("begin");
}

void UnrealCraftItemMapWareGetter::openBox()
{
	//performer->mouseEvent(MouseEvent::ClickRight); usleep(5000);
	performer->mouseEvent(MouseEvent::ClickRight); 	usleep(200);
	tc.begin();
	do {
		Mat mat;
		performer->getF3Pic(mat);
		performer->analysisPic(mat);
		//��F3���ɶ���������
		if (!performer->ifF3CanRead()) {
			usleep(500);
			return;
		}
	} while (tc.end()<MAX_WAIT_MILITIME);
	ThrowException::throwException(__FUNCTION__, "�����ӳ�ʱ!");
}

void UnrealCraftItemMapWareGetter::closeBox()
{
	//performer->open_Or_closePackage(); usleep(2000);
	performer->open_Or_closePackage(); usleep(200);
	tc.begin();
	do {
		Mat mat;
		performer->getF3Pic(mat);
		performer->analysisPic(mat);
		//��F3���ɶ�����ر���
		if (performer->ifF3CanRead()) {
			usleep(500);
			return;
		}
	} while (tc.end() < MAX_WAIT_MILITIME);
	ThrowException::throwException(__FUNCTION__, "�ر����ӳ�ʱ!");
}

void UnrealCraftItemMapWareGetter::readBox()
{
	auto p = performer->getMousePosition();
	performer->moveMouseToPoint(0, 0, false);usleep(200);
	//�����Ӻͱ�����ע�ⱳ������Ϊ������ģʽ
	Mat img;
	performer->getWindowPic(img);
	performer->readContain(img, box);
	performer->getPackage()->setPackageStatus(PackageStatus::USE_BIG_BOX);
	performer->readPackage(img);
	performer->moveMouseToPoint(p.x, p.y);
	usleep(400);
}

bool UnrealCraftItemMapWareGetter::isPackageFull()
{
	auto package = performer->getPackage();
	auto points = package->getAllLatticePOINT();
	for (auto p : points) {
		if (package->getLattice(p.x, p.y).isEmpty()) return false;
	}
	return true;
}

void UnrealCraftItemMapWareGetter::shiftDown()
{
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyDown); usleep(500);
}

void UnrealCraftItemMapWareGetter::shiftUp()
{
	performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyUp); usleep(500);
}

void UnrealCraftItemMapWareGetter::getItemFromBox(int x, int y)
{
	POINT p = box.getLatticeRelativeMidPos(x, y);
	performer->moveMouseAndClickLeft(p.x, p.y, false);
}

void UnrealCraftItemMapWareGetter::openEnderChest()
{
	//performer->useInstruction("/enderchest");	usleep(3000);
	performer->useInstruction("/enderchest"); usleep(200);
	tc.begin();
	do {
		Mat mat;
		performer->getF3Pic(mat);
		performer->analysisPic(mat);
		//��F3���ɶ���������
		if (!performer->ifF3CanRead()) {
			usleep(500);
			return;
		}
	} while (tc.end() < MAX_WAIT_MILITIME);
	ThrowException::throwException(__FUNCTION__, "��ĩӰ�䳬ʱ!");

}

void UnrealCraftItemMapWareGetter::readEnderChestAndPackage()
{
	//��ȡĩӰ��ͱ�����ע���ƶ���������ΪС����ģʽ
	auto p = performer->getMousePosition();
	performer->moveMouseToPoint(0, 0, false);
	usleep(200);
	Mat img;
	performer->getWindowPic(img);
	performer->getPackage()->setPackageStatus(PackageStatus::USE_SMALL_BOX);
	performer->readPackage(img);
	performer->readContain(img, *ender_chest);
	performer->moveMouseToPoint(p.x, p.y);
	usleep(200);
}

void UnrealCraftItemMapWareGetter::closeEnderChest()
{
	//performer->open_Or_closePackage();usleep(1000);
	performer->open_Or_closePackage(); usleep(200);
	tc.begin();
	do {
		Mat mat;
		performer->getF3Pic(mat);
		performer->analysisPic(mat);
		//��F3�ɶ�����ر���
		if (performer->ifF3CanRead()) {
			usleep(500);
			return;
		}
	} while (tc.end() < MAX_WAIT_MILITIME);
	ThrowException::throwException(__FUNCTION__, "�ر�ĩӰ�䳬ʱ!");
}

string UnrealCraftItemMapWareGetter::getPairVectorStr(const vector<pair<string, int>>& vec)
{
	std::stringstream ss;
	for (const auto& pair : vec) {
		ss << pair.first << " " << pair.second << std::endl;
	}
	return ss.str();
}

PlayerStatus UnrealCraftItemMapWareGetter::getPlayerStatus()
{
	Mat img;
	performer->getWindowPic(img);
	performer->analysisPic(img);
	return performer->getAllPlayerInfo();
}

void UnrealCraftItemMapWareGetter::goTo(string name)
{
	//performer->resTp(name); usleep(6000);

	do
	{
		Mat img;
		performer->getF3Pic(img);
		performer->analysisPic(img);
		PlayerPos old_pos;
		if (!performer->getPlayerPosition(old_pos)) {
			break;
		}
		performer->resTp(name);usleep(500);
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
			if (countDistance(old_pos.x, old_pos.y, old_pos.z, new_pos.x, new_pos.y, new_pos.z) > 0.5) {
				usleep(500);
				return;
			}
			usleep(100);
		} while (tc.end() < MAX_WAIT_MILITIME);
	} while (false);

	ThrowException::throwException(__FUNCTION__, name + "���ʹ���!");
}

void UnrealCraftItemMapWareGetter::goToSuitablePos(pair<string, int> name_num_pair,int& first_item_x)
{
	using namespace std;
	static vector<string> concreate = { ".concreate1",".concreate2" };
	static vector<string> clay = { ".clay1",".clay2" };
	static vector<string> others = { ".others1",".others2" };
	static int concreate_index=0, clay_index=0, others_index=0;

	//Logger::log("UnrealCraftItemMapWareGetter::goToSuitablePos1"
	//	, "index:" + to_string(concreate_index) + " " + to_string(clay_index));
	//Logger::log("UnrealCraftItemMapWareGetter::goToSuitablePos1", "pos:" + to_string((int)pos));

	//������ҵ�ǰӦ�ô��ڵ�λ��
	Pos should_pos;//�����������Ӧ�ô��ڵ�λ��
	//Logger::log("UnrealCraftItemMapWareGetter::goToSuitablePos1", "name" + name_num_pair.first);
	if (name_num_pair.first.find("��")==4) {
		should_pos = Pos::Concreate;
	} 
	else if (name_num_pair.first.find("��")==4) {
		should_pos = Pos::Clay;
	} 
	else should_pos = Pos::Other;
	//Logger::log("UnrealCraftItemMapWareGetter::goToSuitablePos2", "should_pos:" + to_string((int)should_pos));
	//��λ�ò��ԣ�����
	if (should_pos != pos||lack_item) {
		//Logger::log("UnrealCraftItemMapWareGetter::goToSuitablePos3", "");
		string destination = warehouse;
		switch (should_pos)
		{
		case UnrealCraftItemMapWareGetter::Pos::Concreate: {
			if (lack_item) {
				concreate_index = (concreate_index + 1) % concreate.size();
				lack_item = false;
			}
			destination += concreate[concreate_index];

		}
			break;
		case UnrealCraftItemMapWareGetter::Pos::Clay:{
			if (lack_item) {
				clay_index = (clay_index + 1) % clay.size();
				lack_item = false;
			}
			destination += clay[clay_index];
		}
			break;
		case UnrealCraftItemMapWareGetter::Pos::Other: {
			if (lack_item) {
				others_index = (others_index + 1) % others.size();
				lack_item = false;
			}
			destination += others[others_index];
		}
			break;
		default:
			break;
		}
		goTo(destination);	
		shiftDown();	//�������
		shiftUp();
		//��ʼ����һ����Ʒ��x����
		pos = should_pos;
		PlayerStatus status = getPlayerStatus();
		if (!status.is_looking_at_block)
			ThrowException::throwException("UnrealCraftItemMapWareGetter::selecting", "δ���򷽿�!");
		first_item_x = status.block_info.block_pos.x;

		//Logger::log("UnrealCraftItemMapWareGetter::goToSuitablePos2"
		//	, "index:" + to_string(concreate_index) + " " + to_string(clay_index));
	}
}

double UnrealCraftItemMapWareGetter::countDistance(double x1, double y1, double z1, double x2, double y2, double z2)
{
	return sqrt(
		(x1 - x2) * (x1 - x2) +
		(y1 - y2) * (y1 - y2) +
		(z1 - z2) * (z1 - z2)
	);
}
