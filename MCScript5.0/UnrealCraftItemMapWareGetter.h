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
		Original,//��ʼ״̬
		Selecting,//ѡ��״̬
		Getting,//����״̬
		Arranging,//����״̬
		Checking,//���״̬
		End//����״̬
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
	bool lack_item;//��getting�ṩ���Ƿ�ȱ����Ʒ��boolֵ����selecting����
public:
	UnrealCraftItemMapWareGetter(ImagePerformer* performer, Box* ender_chest,
		string mc_item_map_path, string config_path);
	// ͨ�� GetItemMap �̳�
	void getItemMap(map<string, int> map) override;
private:
	//���в�����Ӧ���Դ��ӳ�
	//�����ļ�
	void load(string mc_item_map_path, string config_path);
	//��ʼ��
	void init(map<string, int> map);
	//��ѭ��
	void mainRoll();
	//״̬�л�
	void setStatus(Status status);
	//��ʼ״̬����ˢ�±�����ĩӰ��
	void original();
	//ѡ��״̬
	void selecting();
	//����״̬
	void getting();
	//����״̬������ʱ��ĩӰ��
	void arranging();
	//���״̬������ʱ��ĩӰ��
	void checking();
	//����״̬
	void end();
	//������
	void openBox();
	//�ر�����
	void closeBox();
	//��ȡ������Ϣ��˳��ˢ�±���
	void readBox();
	//�����Ƿ�����
	bool isPackageFull();
	//����SHIFT
	void shiftDown();
	//�ɿ�SHIF
	void shiftUp();
	//��Box�л�ȡ��Ʒ
	void getItemFromBox(int x,int y);
	//��ĩӰ��
	void openEnderChest();
	//��ȡĩӰ��ͱ�����Ҫ���Ѿ���ĩӰ��
	void readEnderChestAndPackage();
	//�ر�ĩӰ��
	void closeEnderChest();
	//��ʾneed_vec
	string getPairVectorStr(const vector<pair<string, int>>& vec);
	//��ȡ���״̬
	PlayerStatus getPlayerStatus();
	//ȥĳ��
	void goTo(string name);
	//selecting���Ӻ��������㲢���͵����Ӧ�ô��ڵ�λ��
	void goToSuitablePos(pair<string,int> name_num_pair,int& first_item_x);
	double countDistance(double x1, double y1, double z1, double x2, double y2, double z2);
};

