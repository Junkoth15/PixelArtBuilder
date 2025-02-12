#pragma once
#include"MCItemMap.h"
#include<memory>
class MCItemMapFactory
{
public:
	template<typename Key, typename Value>
	using map = std::map<Key, Value>;  // ʹ�� using ����ģ����ı���
	using string = std::string;
public:
	static const MCItemMap& getMCItemMap(string item_set_path);

private:
	static map<string, MCItemMap> item_map_map;
private:
	//������Ʒ��������������Ʒ��Ϊ���򷵻�null
	static MCItemMap createMCItemMap(string item_set_path);
	static string getMCItemMapName(string item_set_path);
};

