#pragma once
//ASCII数字码
enum class ASCIIKeyCode {
	ZERO = 48, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
	A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	SHIFT = 16, SPACEBAR = 32/*空格*/, XIEGANG = 111/*斜杠*/, CTRL = 17/*control*/, ENTER = 13/*enter*/
};

//键盘事件
enum class KeyEvent {
	KeyDown, KeyUp
	//, ClickKey
};
class KeyBoardControl
{
public:
	//键盘操作，可选择是否进行虚拟操作，默认为实质性操作
	virtual void keyEvent(ASCIIKeyCode key, KeyEvent key_event) = 0;
	//敲击数字键
	virtual void clickNumberKey(int num) = 0;
	//按下键盘一段时间
	virtual void clickKey(ASCIIKeyCode key, int interval_time, int delay_time) = 0;
};

