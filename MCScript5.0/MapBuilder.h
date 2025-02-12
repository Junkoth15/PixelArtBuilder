#pragma once
#include"BuildMapPic.h"
#include"BuildLine.h"
#include"SplitTask.h"
#include"CanBuildMapPic.h"
#include"ColorItemSet.h"
#include"NameSpace.h"
class MapBuilder:public BuildMapPic
{

protected:
	shared_ptr<BuildLine> line_builder;
	shared_ptr<SplitTask> task_spliter;
	shared_ptr<CanBuildMapPic> builder;
	shared_ptr<const ColorItemSet> color_item_set;//��ɫת��ɫ��Ʒ
public:
	/// <summary>
	/// MPB���캯��
	/// </summary>
	/// <param name="builder">������</param>
	/// <param name="line_builder">�н�����</param>
	/// <param name="task_spliter">����ָ���</param>
	/// <param name="color_item_map_path">��ɫ��Ʒͼ·��</param>
	MapBuilder(shared_ptr<CanBuildMapPic> builder,shared_ptr<BuildLine> line_builder,
		shared_ptr<SplitTask> task_spliter,string color_item_map_path);
	// ͨ�� BuildMapPic �̳�
	void buildMapPic(Mat mat, int begin_line, int end_line) override;
protected:
	//���º����е�line��Ҫ���0��ʼ
	virtual void init(Mat& mat, int& begin_line, int& end_line);
	virtual void buildLines(const ColorItemMat& mat,int begin_line, int end_line,int line_length);
	virtual void buildOneLine(const ColorItemMat& mat, int now_line, int end_line, int line_length);
	virtual void getItem(map<string, int> item_map);
	virtual void goToLine(int line);
	virtual void recycleItem();
	//��ȡ��һ��Ŀ���У�������������Ʒ
	virtual int getNext(const ColorItemMat& mat,int begin_line, int max_line, map<string, int>& item_map);
	virtual void beforeEnd();
	virtual ColorItemMat MatToColorItemMat(Mat mat);
	virtual void refreshPackage();
	virtual void goToBoard();
};

