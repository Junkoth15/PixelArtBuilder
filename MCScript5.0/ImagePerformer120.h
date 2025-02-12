#pragma once
#include"ImagePerformer.h"
#include"NoImagePerformer120.h"
#include"ReadAllInfo.h"

/// <summary>
/// 有图像识别的操控类
/// 继承了无图像识别的操控类
/// 利用ImageHandler成员处理图像
/// 最终实现有图像识别的操控类
/// </summary>
class ImagePerformer120 :
	public ImagePerformer
{
protected:
	shared_ptr<ReadAllInfo> image_handler;
	shared_ptr<NoImagePerformer> performer;

public:
	ImagePerformer120(HWND window, shared_ptr<NoImagePerformer> performer, shared_ptr<ReadAllInfo> image_handler);
	shared_ptr<ReadAllInfo> setImageReader(shared_ptr<ReadAllInfo> reader);
	shared_ptr<ReadAllInfo> getImageReader();
	shared_ptr<NoImagePerformer> setPerformer(shared_ptr<NoImagePerformer> performer);
	shared_ptr<NoImagePerformer> getPerformer();

	// 通过 WinPlayerControl 继承
	void winTurnHead_x(float rad, float rad_speed, bool right, bool virtualAction) override;
	void winTurnHead_y(float rad, float rad_speed, bool up, bool virtualAction) override;
	void winChangeFace_x(float rad_begin, float rad_target, float rad_speed, bool virtualAction) override;
	void winChangeFace_y(float rad_begin, float rad_target, float rad_speed, bool virtualAction) override;
	void winMovePlayerPosition_inDistance(
		int direction, float distance, float move_speed, bool shift, bool virtualAction) override;

	// 通过 ReadAllInfoCImage 继承
	PlayerStatus getAllPlayerInfo(CImage img)override;
	bool isLookingAtBlock(const CImage& f3_image) override;
	bool getLookingAtBlock(const CImage& f3_image,BlockInfo& block_info) override;
	bool getLookingAtBlockName(const CImage& f3_image, string& blockname) override;
	bool getLookingAtBlockPos(const CImage& f3_image, BlockPos& block_pos) override;
	bool ifPosCanRead(const CImage& f3_image) override;
	bool ifDirectionCanRead(const CImage& f3_image) override;
	bool getPlayerPosition(const CImage& f3_image,PlayerPos& player_pos) override;
	bool getPlayerFacingDirection(const CImage& f3_image,PlayerFacing& player_facing) override;
	void readContain(const CImage& f3_img, Contain& contain) override;
	void readPackage(const CImage& img) override;

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
	void getWindowPic(WindowCImage& image) override;
	void getWindowPic(WindowCImage& image, int width, int height, int left_x, int top_y) override;
	void getF3Pic(WindowCImage& image) override;

	// 通过 ImagePerformer 继承
	int getHand() override;
	void setHand(int hand) override;
	void changeHand(int hand) override;


	// 通过 ImagePerformer 继承
	void putBlock(bool change_package) override;


	// 通过 ImagePerformer 继承
	void moveMouseAndClickLeft(int x, int y, bool absolute, int move_delay, int click_delay) override;

};


