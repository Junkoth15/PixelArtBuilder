#pragma once
#include"Font.h"
class VectorFont:public Font
{
public:
	template<typename Type>
	using vector = std::vector<Type>;
public:
	vector<Letter> font;
	vector<int> all_letter_width;
	int letter_height;
public:
	// Í¨¹ý Font ¼Ì³Ð
	bool searchLetter(const Mat& mat,char& ch) const override;
	vector<int> getAllLetterWidth() const override;
	int getLetterHeight() const override;
};

