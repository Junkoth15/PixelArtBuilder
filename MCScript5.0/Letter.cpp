#include "Letter.h"

Letter::Letter(char ch, const Mat& pic) :
	ch(ch),
	pic(pic.clone())
{
}
