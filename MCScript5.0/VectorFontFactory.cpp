#include "VectorFontFactory.h"
#include"FileLoader.h"
using namespace std;
using namespace cv;

map<string, shared_ptr<VectorFont>> VectorFontFactory::font_map;

bool ifInVec(const vector<int>& vec, int num) {
	bool result = false;
	for (auto n : vec) {
		if (n == num) {
			return true;
		}
	}
	return result;
}


shared_ptr<VectorFont> VectorFontFactory::createFont(string font_path)
{
	shared_ptr<VectorFont> result =make_shared<VectorFont>();
	result->name = getFontName(font_path);
	vector<Letter>& char_list = result->font;

	auto name_mat_map = FileLoader::loadPicsInFolder(font_path,ImreadModes::IMREAD_GRAYSCALE);
	for (auto p : name_mat_map) {
		string name = p.first;
		Mat mat = p.second;
		result->letter_height = mat.rows;

		int num = stoi(string(name.begin()+1,name.end()-1));
		char ch;

		//以灰度图方式读入
		if ( 1<=num && num <= 10) {
			ch = '0' + num - 1;
		}
		else if (11<=num && num <= 36) {
			ch = 'a' + num - 11;
		}
		else if (37<=num && num <= 62) {
			ch = 'A' + num - 37;
		}
		else {
			switch (num)
			{
			case 63:ch = '-'; break;
			case 64:ch = '/'; break;
			case 65:ch = '('; break;
			case 66:ch = ')'; break;
			case 67:ch = '['; break;
			case 68:ch = ']'; break;
			case 69:ch = ':'; break;
			case 70:ch = '_'; break;
			case 71:ch = '.'; break;
			case 72:ch = ' '; break;
			case 73:ch = ','; break;
			default:throw exception(string("VectorFontFactory::createFont:未知字符:" + to_string(num) + "\n").c_str());
			}
		}
		char_list.emplace_back(Letter(ch,mat));
		if (!ifInVec(result->all_letter_width, mat.cols)) {
			result->all_letter_width.push_back(mat.cols);
		}
	}

	if (char_list.empty()) {
		return nullptr;
	}
	sort(result->all_letter_width.begin(), result->all_letter_width.end(),greater<int>());
	return result;
}

string VectorFontFactory::getFontName(string font_path)
{
	int begin = font_path.find_last_of('/');
	return string(font_path.begin()+begin,font_path.end());
}

shared_ptr<const VectorFont> VectorFontFactory::getFont(string font_path)
{
	auto iter = font_map.find(getFontName(font_path));
	if (iter != font_map.end()) {
		return iter->second;
	}
	else {
		shared_ptr<VectorFont> new_font = createFont(font_path);
		if (new_font == nullptr) {
			return nullptr;
		}
		font_map[new_font->name] = new_font;
		return font_map[new_font->name];
	}
}
