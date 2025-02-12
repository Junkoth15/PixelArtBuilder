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
	// Í¨¹ý ReadString ¼Ì³Ð
	string readString(const Mat& img, Scalar font_color, bool from_left_top) const override;
protected:
	//½«×Ö·û´®Ô­Í¼×ª»»ÎªºÚ°×Í¼
	virtual Mat BGR2GRAY(const Mat& img, Scalar font_color)const;
};

