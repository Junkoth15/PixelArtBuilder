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
	shared_ptr<const ColorItemSet> color_item_set;//颜色转颜色物品
public:
	/// <summary>
	/// MPB构造函数
	/// </summary>
	/// <param name="builder">建造器</param>
	/// <param name="line_builder">行建造器</param>
	/// <param name="task_spliter">任务分割器</param>
	/// <param name="color_item_map_path">颜色物品图路径</param>
	MapBuilder(shared_ptr<CanBuildMapPic> builder,shared_ptr<BuildLine> line_builder,
		shared_ptr<SplitTask> task_spliter,string color_item_map_path);
	// 通过 BuildMapPic 继承
	void buildMapPic(Mat mat, int begin_line, int end_line) override;
protected:
	//以下函数中的line都要求从0开始
	virtual void init(Mat& mat, int& begin_line, int& end_line);
	virtual void buildLines(const ColorItemMat& mat,int begin_line, int end_line,int line_length);
	virtual void buildOneLine(const ColorItemMat& mat, int now_line, int end_line, int line_length);
	virtual void getItem(map<string, int> item_map);
	virtual void goToLine(int line);
	virtual void recycleItem();
	//获取下一个目标行，并返回所需物品
	virtual int getNext(const ColorItemMat& mat,int begin_line, int max_line, map<string, int>& item_map);
	virtual void beforeEnd();
	virtual ColorItemMat MatToColorItemMat(Mat mat);
	virtual void refreshPackage();
	virtual void goToBoard();
};

