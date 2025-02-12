#pragma once
#include"CanBuildMapPic.h"
#include"ImagePerformer.h"
#include"ItemConverter.h"
#include"UnrealCraftBox.h"
#include"MCItemMap.h"
#include"UnrealCraftItemMapWareGetter.h"
struct UnrealCraftMPBInfo
{
	int board_first_line_x;//�����һ��x
	string item_map_path;//mc��Ʒ��·��
	string convert_file_path;//ת���ļ�·��
	string getter_file_path;//��ȡ���ļ�·��
};

class UnrealCraftMPBPerformer:public CanBuildMapPic
{
protected:
	shared_ptr<ImagePerformer> performer;
	ItemConverter converter;//��ɫ��Ʒתmc��Ʒ
	UnrealCraftBox ender_chest;
	UnrealCraftMPBInfo mpb_info;
	UnrealCraftItemMapWareGetter getter;

public:
	UnrealCraftMPBPerformer(shared_ptr<ImagePerformer> performer,UnrealCraftMPBInfo mpb_info);
	// ͨ�� CanBuildMapPic �̳У����к����������ӳ�
	void getItemToHand(const vector<ColorItem>& line,int item_index) override;
	void putBlock() override;
	void move(MoveMode mode) override;
	PlayerStatus getPlayerStatus() override;
	bool testAddItemToPackage(map<string, int> item_map) const override;
	//line��0��ʼ
	void goToLine(int line) override;
	void goToBoard() override;
	//�򿪱��������ñ���״̬ΪĩӰ��
	void openPackage() override;
	void closePackage() override;
	void refreshPackage() override;
	void recycleItem() override;
	void getItemMap(map<string, int> map) override;
private:
	//��ɫ��Ʒתmc��Ʒ
	const MCItem& convert(string name)const;
	void arrangePackage(const vector<ColorItem>& line,int index);
	//arrange���Ӻ��������ڴ���Ʒͼ�и���Ʒ���޸���Ʒ������index
	bool isPocketMapHas(map<string, int>& map, const string& item_name, int& index);
	//arrange���Ӻ�����Ѱ�ҿ��õ���Ʒ����
	POINT findUseAbleMCItemPOINT(const MCItem& item, const vector<bool>& is_used);
	//arrange���Ӻ��������item�������ڿڴ���
	void ifMCItemInPocket(map<string, int>& pocket_map,POINT item_point , vector<bool>& is_used, int& pocket_used);
	//arrange���Ӻ��������item�����겻�ڿڴ���
	void ifMCItemNotInPocket(map<string, int>& pocket_map, POINT item_point, vector<bool>& is_used, int& pocket_used);
	//����������Ʒ����ȡ���ӱ��
	POINT findOneMCItem(const MCItem& item)const;
	vector<POINT> findAllMCItem(const MCItem& item)const;
	POINT getLatticeRelativeMidPos(int x, int y)const;
	Lattice& getLattice(int x, int y);
	const Lattice& getLattice(int x, int y) const;
	//ȥ����
	void goToSpawn();
	//ȥ������
	void goToSurviveArea();
	//����
	void fly();
	//�������
	void closeFly();
};

