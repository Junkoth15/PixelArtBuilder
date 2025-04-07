#include "MapBuilder.h"
#include"LineBuilder.h"
#include"ColorItemSetFactory.h"
#include"Tools.h"

MapBuilder::MapBuilder(shared_ptr<CanBuildMapPic> builder, shared_ptr<BuildLine> line_builder, 
	shared_ptr<SplitTask> task_spliter,string color_item_map_path):
	builder(builder),
	line_builder(line_builder),
	task_spliter(task_spliter)
{
	color_item_set=ColorItemSetFactory::getColorItemSet(color_item_map_path);
}

void MapBuilder::buildMapPic(Mat mat, int begin_line, int end_line)
{
	//����1��ʼ��lineת��Ϊ��0��ʼ
	begin_line--;
	end_line--;
	int now_line = begin_line, target_line = -1;
	Mat handled_mat = mat.clone();

	//��ʼ��ͼƬ
	init(handled_mat, begin_line, end_line);
	//�����ɫ��Ʒ����
	auto color_item_mat = MatToColorItemMat(handled_mat);
	//��ʼ����
	while (now_line <= end_line) {
		map<string, int> item_map;
		target_line=getNext(color_item_mat,now_line, end_line, item_map);
		getItem(item_map);
		goToBoard();
		buildLines(color_item_mat,now_line, target_line,handled_mat.cols);
		recycleItem();
		now_line = target_line + 1;
	}
	beforeEnd();
}

void MapBuilder::init(Mat& mat, int& begin_line, int& end_line)
{
	LogTrace("begin");
	//����ͼƬ��������������˳ʱ����ת90��
	//�и�ͼƬ��������
	//mat= mat(Rect(begin_line, 0, end_line - begin_line + 1, mat.rows));
	//�������ϱ�������,��ͼ��ת��
	rotate(mat, mat, cv::RotateFlags::ROTATE_90_CLOCKWISE);
	//end_line -= begin_line;
	//begin_line = 0;
}

void MapBuilder::buildLines(const ColorItemMat& mat,int begin_line, int end_line,int line_length)
{
	LogTrace("begin");
	LogInfo("begin:" + std::to_string(begin_line) + " end:" + std::to_string(end_line));
	int now_line = begin_line;
	refreshPackage();
	while (now_line <= end_line) {
		goToLine(now_line);
		buildOneLine(mat, now_line,end_line,line_length);
		if ((now_line - begin_line) % 4 == 0) {
			refreshPackage();
		}
		now_line++;
	}
}

void MapBuilder::buildOneLine(const ColorItemMat& mat, int now_line,int end_line,int line_length)
{
	//�ӳ�������ƣ�������һ��ʱ������n�еĲ���
	vector<ColorItem> color_item_vec;
	int item_num = 0;
	//�����ӳ�line��ֱ������end_line������Ʒ�������ܷŵ��£��˴���end_lineָ���Ǳ���װ����Ʒ�ܴ�еļ���
	for (int i = now_line; i <= end_line; i++) {
		const vector<ColorItem>& item_line = mat.mat[i];
		color_item_vec.insert(color_item_vec.end(), item_line.begin(), item_line.end());
		item_num += item_line.size();
		//��Ʒ�������ܷŵ���
		if (item_num > 64 * 9) break;
	}
	line_builder->buildLine(color_item_vec,line_length-1);
}

void MapBuilder::getItem(map<string, int> item_map)
{
	LogTrace("begin");
	builder->getItemMap(item_map);
}

void MapBuilder::goToLine(int line)
{
	builder->goToLine(line);
}

void MapBuilder::recycleItem()
{
	LogTrace("begin");
	builder->recycleItem();
}

int MapBuilder::getNext(const ColorItemMat& mat,int begin_line, int max_line, map<string, int>& item_map)
{
	LogTrace("begin");
	return task_spliter->getNextEndRow(mat,begin_line,max_line,builder,item_map);
}

void MapBuilder::beforeEnd()
{
	LogTrace("begin");
}

ColorItemMat MapBuilder::MatToColorItemMat(Mat mat)
{
	LogTrace("begin");
	ColorItemMat result;
	result.mat.resize(mat.rows);
	for (int y = 0; y < mat.rows; y++) {
		for (int x = 0; x < mat.cols; x++) {
			Scalar color = imageHandle::getColor(mat, y, x);
			result.mat[y].push_back(color_item_set->getColorMCItem(color));
		}
	}
	return result;
}

void MapBuilder::refreshPackage()
{
	builder->openPackage();
	builder->refreshPackage();
	builder->closePackage();
}

void MapBuilder::goToBoard()
{
	LogTrace("begin");
	builder->goToBoard();
}
