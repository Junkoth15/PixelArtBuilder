#pragma once
#include"ImagePerformer.h"
#include"NoImagePerformer120.h"
//#include"ReadAllInfo.h"
#include"ReadPlayerInfo.h"
#include"ReadContain.h"

/// <summary>
/// 有图像识别的操控类
/// 继承了无图像识别的操控类
/// 利用ImageHandler成员处理图像
/// 最终实现有图像识别的操控类
/// </summary>
class ImagePerformer120:
	public ImagePerformer
{
protected:
	//shared_ptr<ReadAllInfo> image_handler;
	shared_ptr<NoImagePerformer> performer;
	shared_ptr<ReadPlayerInfo> player_reader;
	shared_ptr<ReadContain> contain_reader;

public:
	//ImagePerformer120();
	ImagePerformer120(
		HWND window,
		shared_ptr<NoImagePerformer> performer,
		shared_ptr<ReadPlayerInfo> player_reader,
		shared_ptr<ReadContain> contain_reader);
	//shared_ptr<ReadAllInfo> setImageReader(shared_ptr<ReadAllInfo> reader);
	//shared_ptr<ReadAllInfo> getImageReader();
	shared_ptr<ReadPlayerInfo> setPlayerReader(shared_ptr<ReadPlayerInfo> player_reader);
	shared_ptr<ReadPlayerInfo> getPlayerReader();
	shared_ptr<ReadContain> setContainReader(shared_ptr<ReadContain>);
	shared_ptr<ReadContain> getContainReader();
	shared_ptr<NoImagePerformer> setPerformer(shared_ptr<NoImagePerformer> performer);
	shared_ptr<NoImagePerformer> getPerformer();

	// 通过 WinPlayerControl 继承
	void winTurnHead_x(float rad, float rad_speed, bool right, bool virtualAction) override;
	void winTurnHead_y(float rad, float rad_speed, bool up, bool virtualAction) override;
	void winChangeFace_x(float rad_begin, float rad_target, float rad_speed, bool virtualAction) override;
	void winChangeFace_y(float rad_begin, float rad_target, float rad_speed, bool virtualAction) override;
	void winMovePlayerPosition_inDistance(
		int direction, float distance, float move_speed, bool shift, bool virtualAction) override;

	// 通过 ImagePerformer 继承
	void keyEvent(ASCIIKeyCode key, KeyEvent key_event) override;
	void clickNumberKey(int num) override;
	void clickKey(ASCIIKeyCode key, int interval_time, int delay_time) override;
	void moveMouseToPoint(int x, int y, bool absolute_coordinates) override;
	void moveMouse(int dx, int dy) override;
	void moveMouseLinearly_inTime(float directionRad, int distance, int militime) override;
	void moveMouseLinearly_inSpeed(float directionRad, int distance, float speed) override;
	POINT getMousePosition() override;
	void mouseEvent(MouseEvent mouse_event) override;
	void turnHead_x(float rad, float rad_speed, bool right) override;
	void turnHead_y(float rad, float rad_speed, bool up) override;
	void changeFace_x(float rad_begin, float rad_target, float rad_speed) override;
	void changeFace_y(float rad_begin, float rad_target, float rad_speed) override;
	void movePlayerPosition_inDistance(int direction, float distance, float move_speed, bool shift) override;
	void movePlayerPosition_inTime(int direction, int militime, bool shift) override;
	HWND getWindow() override;
	POINT getWindowPos() override;
	void getWindowSize(int& width, int& height) override;
	void changeWinodw(HWND window) override;
	void refreshWindowPositionAndSize() override;
	void setWindowPos(int x, int y) override;
	void setWindowSize(int width, int height) override;
	void setWindowSize(int f_size_type) override;
	void guaji(int seconds) override;
	void backGame() override;
	void speak(string str) override;
	void randomSpeak(string str) override;
	void resTp(string destination) override;
	void useInstruction(string instruction) override;
	string getPackageInfo() override;
	shared_ptr<Package> getPackage() override;
	shared_ptr<Package> setPackage(shared_ptr<Package> package) override;
	void open_Or_closePackage() override;
	void getWindowPic(Mat& image) override;
	void getWindowPic(Mat& image, int width, int height, int left_x, int top_y) override;
	void getF3Pic(Mat& image) override;

	// 通过 ImagePerformer 继承
	int getHand() override;
	void setHand(int hand) override;
	void changeHand(int hand) override;

	// 通过 ImagePerformer 继承
	void putBlock(bool change_package) override;

	// 通过 ImagePerformer 继承
	void moveMouseAndClickLeft(int x, int y, bool absolute, int move_delay, int click_delay) override;

	// 通过 ImagePerformer 继承
	void analysisPic(const Mat& img) override;
	bool isLookingAtBlock() override;
	bool getLookingAtBlock(BlockInfo& block_info) override;
	bool getLookingAtBlockName(string& name) override;
	bool getLookingAtBlockPos(BlockPos& block_pos) override;
	bool ifF3CanRead() override;
	bool getPlayerPosition(PlayerPos& player_pos) override;
	bool getPlayerFacing(PlayerFacing& player_facing) override;
	void readContain(const Mat& mat, Contain& contain) override;
	void readPackage(const Mat& mat)override;

	// 通过 ImagePerformer 继承
	PlayerStatus getAllPlayerInfo() override;
};


