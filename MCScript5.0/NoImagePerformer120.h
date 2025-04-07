#pragma once
#include"NoImagePerformer.h"
#include"Package.h"
#include<memory>
//������
enum class KeyBoardCode
{
	NONE=0,
	ONE = 0x02, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO,
	Q = 0x10, W, E, R, T, Y, U, I, O, P,
	A = 0x1e, S, D, F, G, H, J, K, L,
	Z = 0x2c, X, C, V, B, N, M,
	SPACEBAR = 0x39, XIEGANG = 0x35, SHIFT = 0x2A,CTRL=0x1D
};

KeyBoardCode ASCIIKeyCode2KeyBoardCode(ASCIIKeyCode keycode);

/// <summary>
/// ��ͼ��ٿ�����ʵ���࣬
/// ���к������Ѹ���Ĭ��ʵ��
/// </summary>
class NoImagePerformer120 :
	public NoImagePerformer
{
protected:
	//���ھ��
	HWND window;
	//��Ļ���
	int screenWidth;
	//��Ļ�߶�
	int screenHeight;
	//���ڿ�
	int winWidth;
	//���ڸ�
	int winHeight;
	//�ͻ������Ͻ�x����
	int win_x;
	//�ͻ������Ͻ�y����
	int win_y;
	//�ֵ�λ��
	int hand;
private:
	//��ұ���������Ϊ˽�У�����ʵ����ʹ�ø߼�����ʱ���ῴ������ͼ�����
	shared_ptr<Package> package;
public:
	NoImagePerformer120(HWND window, shared_ptr<Package> package);
	//��������붨�������������
	virtual ~NoImagePerformer120() = default;
	shared_ptr<Package> setPackage(shared_ptr<Package> package)override;
	shared_ptr<Package> getPackage()override;
	void open_Or_closePackage()override;
	virtual void moveMouseAndClickLeft(int x, int y, int intervalMiliTime, int delayMiliTime, bool absolute_coordinate);
	virtual void putBlock(int delay_militime, int handPos, bool operate_package);


	// ͨ�� KeyBoardControl �̳�
	void keyEvent(ASCIIKeyCode key, KeyEvent key_event) override;
	void clickNumberKey(int num) override;
	void clickKey(ASCIIKeyCode key, int interval_time=50, int delay_time=0) override;

	// ͨ�� MouseControl �̳�
	void moveMouseToPoint(int x, int y, bool absolute_coordinates = true) override;
	void moveMouse(int dx, int dy) override;
	void moveMouseLinearly_inTime(float directionRad, int distance, int militime) override;
	void moveMouseLinearly_inSpeed(float directionRad, int distance, float speed) override;
	POINT getMousePosition() override;
	void mouseEvent(MouseEvent mouse_event) override;

	// ͨ�� PlayerControl �̳�
	void turnHead_x(float rad, float rad_speed, bool right) override;
	void turnHead_y(float rad, float rad_speed, bool up) override;
	void changeFace_x(float rad_begin, float rad_target, float rad_speed) override;
	void changeFace_y(float rad_begin, float rad_target, float rad_speed) override;
	void movePlayerPosition_inDistance(int direction, float distance, float move_speed, bool shift) override;
	void movePlayerPosition_inTime(int direction, int militime, bool shift) override;

	// ͨ�� WindowControl �̳�
	HWND getWindow() override;
	POINT getWindowPos() override;
	void getWindowSize(int& width, int& height) override;
	void changeWinodw(HWND window) override;
	void refreshWindowPositionAndSize() override;
	void setWindowPos(int x, int y) override;
	void setWindowSize(int width, int height) override;
	void setWindowSize(int f_size_type) override;

	// ͨ�� NoImageBasicFunction �̳�
	void putBlock(bool change_package) override;
	void guaji(int seconds) override;
	void backGame() override;
	void speak(string str) override;
	void randomSpeak(string str) override;
	void resTp(string destination) override;
	void useInstruction(string instruction) override;
	string getPackageInfo() override;
	void moveMouseAndClickLeft(int x, int y, bool absolute, int move_delay, int click_delay) override;

	// ͨ�� HandControl �̳�
	int getHand() override;
	void setHand(int hand) override;
	void changeHand(int hand) override;
};

