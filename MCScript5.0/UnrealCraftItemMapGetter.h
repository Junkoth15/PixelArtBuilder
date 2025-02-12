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
		Original,//��ʼ״̬
		Selecting,//ѡ��״̬
		Buying,//����״̬
		Arranging,//����״̬
		Checking,//���״̬
		End//����״̬
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
	int page;//��ǰҳ��
	bool next_page_is_bigger;//��һҳ�����ҷ�
public:
	UnrealCraftItemMapGetter(ImagePerformer* performer,Box* ender_chest,string mc_item_map_path);
	// ͨ�� GetItemMap �̳�
	void getItemMap(map<string, int> map) override;
private:
	//���в�����Ӧ���Դ��ӳ�
	//��ѭ��
	void mainRoll();
	//״̬�л�
	void setStatus(Status status);
	//��ʼ״̬������ʱ�Զ�����page��next_page����ˢ�±�����ĩӰ�䣬Ȼ����̵�
	void original();
	//ѡ��״̬
	void selecting();
	//����״̬
	void buying();
	//����״̬������ʱ��ĩӰ��
	void arranging();
	//���״̬������ʱ��ĩӰ��
	void checking();
	//����״̬
	void end();
	//���̵�
	void openShop();
	//�ر��̵�
	void closeShop();
	//��ȡ�̵���Ϣ��˳��ˢ�±���
	void readShop();
	//��ת����һҳ
	void jumpToNextPage();
	//�����Ƿ�����
	bool isPackageFull();
	//���һ��
	void addOneGroup();
	//����һ��
	void removeOne();
	//����
	void pay();
	//��һ����Ʒ���뱳��
	void addOneGroupToPackage(const MCItem& item);
	//��ĩӰ��
	void openEnderChest();
	//��ȡĩӰ��ͱ�����Ҫ���Ѿ���ĩӰ��
	void readEnderChestAndPackage();
	//�ر�ĩӰ��
	void closeEnderChest();
	//ͼ����
	map<string, int> mapMinus(const map<string, int>& larger, const map<string, int>& smaller);
};

