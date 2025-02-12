#pragma once
#include"ReadString.h"
#include"SearchLetter.h"
#include<memory>
class StringReader:public ReadString
{
public:
	template<typename Type>
	using shared_ptr = std::shared_ptr<Type>;
private:
	shared_ptr<const SearchLetter> letter_searcher;
public:
	StringReader(shared_ptr<const SearchLetter> letter_searcher);
	// ͨ�� ReadString �̳�
	string readString(const Mat& img, Scalar font_color, bool from_left_top) const override;
protected:
	//���ַ���ԭͼת��Ϊ�ڰ�ͼ
	virtual Mat BGR2GRAY(const Mat& img, Scalar font_color)const;
};

