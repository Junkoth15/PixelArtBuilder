#pragma once
//ASCII������
enum class ASCIIKeyCode {
	ZERO = 48, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
	A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	SHIFT = 16, SPACEBAR = 32/*�ո�*/, XIEGANG = 111/*б��*/, CTRL = 17/*control*/, ENTER = 13/*enter*/
};

//�����¼�
enum class KeyEvent {
	KeyDown, KeyUp
	//, ClickKey
};
class KeyBoardControl
{
public:
	//���̲�������ѡ���Ƿ�������������Ĭ��Ϊʵ���Բ���
	virtual void keyEvent(ASCIIKeyCode key, KeyEvent key_event) = 0;
	//�û����ּ�
	virtual void clickNumberKey(int num) = 0;
	//���¼���һ��ʱ��
	virtual void clickKey(ASCIIKeyCode key, int interval_time, int delay_time) = 0;
};

