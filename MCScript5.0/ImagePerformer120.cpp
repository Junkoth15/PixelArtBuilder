#include<opencv2/opencv.hpp>
#include "ImagePerformer120.h"
#include"Tools.h"

using namespace cv;
using namespace std;
using namespace imageHandle;

void ImagePerformer120::winTurnHead_x(float rad, float rad_speed, bool right, bool virtualAction)
{
	//pix_speed=rad_speed/0.1028/1000
	//最小精度=rad_speed/1000*interval_time
	auto minus = [](float begin, float end, bool turn_right) {
		begin -= (int)(begin / 180) * 180;
		end -= (int)(end / 180) * 180;
		float distance = fabs(end - begin);
		if (turn_right) {
			return end >= begin ? distance : 360 - distance;
		}
		else {
			return end <= begin ? distance : 360 - distance;
		}
		};

	PlayerFacing begin;
	CImage image;
	getWindowPic(image);
	if (!getPlayerFacingDirection(image, begin)) {
		return;
	}

	PlayerFacing end;
	float cost_time = 0;//转向已经花费的时间,每20ms转向一次
	int min_distance = (int)(rad_speed / 50 / 0.1028);//最小转向像素距离
	int moved_distance = 0;//已经移动的像素距离
	float half_min_rad = (float)min_distance / 2 * 0.1028;//最小转角的一半
	while (true)
	{
		CImage image;
		getWindowPic(image);
		getPlayerFacingDirection(image,end);
		//最后会落在[rad-half_min_rad,rad+half_min_rad]中
		if (minus(begin.x, end.x, right) < rad - half_min_rad) {
			float rad_direction = right ? 0 : PI;

			//以平均速度决定是加速还是减速转向
			if (moved_distance * 0.1028 / cost_time * 1000 > rad_speed) {
				moveMouseLinearly_inTime(rad_direction, min_distance, 20);
				moved_distance += min_distance;
			}
			else {
				moveMouseLinearly_inTime(rad_direction, min_distance + 1, 20);
				moved_distance += min_distance + 1;
			}
			cost_time += 20;
		}
		else {
			break;
		}
	}
}

void ImagePerformer120::winTurnHead_y(float rad, float rad_speed, bool up, bool virtualAction)
{
	//pix_speed=rad_speed/0.1028/1000
	//最小精度=rad_speed/1000*interval_time
	rad = fabs(rad);
	rad = min(180, rad);

	CImage image;
	getWindowPic(image);
	PlayerFacing begin;
	if (getPlayerFacingDirection(image,begin)) {
		//如果转向rad角度已经超过了[-90,90]，则修改rad
		rad = up ? min(rad, 90 + begin.y) : min(rad, 90 - begin.y);

		PlayerFacing end;
		float cost_time = 0;//转向已经花费的时间
		int min_distance = (int)(rad_speed / 50 / 0.1028);//最小转向像素距离
		int moved_distance = 0;//已经移动的像素距离
		float half_min_rad = (float)min_distance / 2 * 0.1028;//最小转角的一半
		float rad_direction = up ? PI / 2 : -PI / 2;//鼠标移动方向
		while (true)
		{
			CImage image;
			getWindowPic(image);
			getPlayerFacingDirection(image, end);
			if (fabs(end.y - begin.y) < rad - half_min_rad) {
				if (moved_distance * 0.1028 / cost_time * 1000 > rad_speed) {
					moveMouseLinearly_inTime(rad_direction, min_distance, 20);
					moved_distance += min_distance;
				}
				else {
					moveMouseLinearly_inTime(rad_direction, min_distance + 1, 20);
					moved_distance += min_distance + 1;
				}
				cost_time += 20;
			}
			else {
				break;
			}
		}
	}
}

void ImagePerformer120::winChangeFace_x(float rad_begin, float rad_target, float rad_speed, bool virtualAction)
{
	//用于把rad缩到范围[180,180)的函数
	auto transformRad = [](float rad) {
		//把rad缩到范围(-360,360)
		rad -= (int)(rad / 360) * 360;
		//把rad缩到范围[180,180)
		if (rad >= 180) {
			rad -= 360;
		}
		if (rad < -180) {
			rad += 360;
		}
		return rad;
		};
	//把beg和tar缩到范围[-180,180)
	rad_begin = transformRad(rad_begin);
	rad_target = transformRad(rad_target);
	//求出beg和tar最近转角
	float rad_distance = min(fabs(rad_begin - rad_target), 360 - fabs(rad_begin - rad_target));
	//判断是向左还是向右转向
	bool turnRight = rad_begin > rad_target + 180 || (rad_target > rad_begin && rad_target - rad_begin < 180);

	winTurnHead_x(rad_distance, rad_speed, turnRight, virtualAction);
}

void ImagePerformer120::winChangeFace_y(float rad_begin, float rad_target, float rad_speed, bool virtualAction)
{
	//求出beg和tar最近转角
	float rad_distance = fabs(rad_begin - rad_target);
	//判断是向上还是向下转向
	bool turnUp = rad_begin > rad_target;

	winTurnHead_y(rad_distance, rad_speed, turnUp, virtualAction);
}

void ImagePerformer120::winMovePlayerPosition_inDistance(int direction, float distance, float move_speed, bool shift, bool virtualAction)
{
	if (direction < 0 || direction>7 || distance <= 0) {
		return;
	}

	PlayerPos begin;

	{
		CImage window_image;
		getWindowPic(window_image);
		//识别现在的位置
		getPlayerPosition(window_image,begin);
	}

	//按下SHIFT
	if (shift) {
		keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyDown);
	}

	//按下移动键
	KeyEvent key_event = KeyEvent::KeyDown;
	switch (direction)
	{
	case 0:keyEvent(ASCIIKeyCode::W, key_event); break;
	case 1:keyEvent(ASCIIKeyCode::W, key_event); keyEvent(ASCIIKeyCode::D, key_event); break;
	case 2:keyEvent(ASCIIKeyCode::D, key_event); break;
	case 3:keyEvent(ASCIIKeyCode::D, key_event); keyEvent(ASCIIKeyCode::S, key_event); break;
	case 4:keyEvent(ASCIIKeyCode::S, key_event); break;
	case 5:keyEvent(ASCIIKeyCode::S, key_event); keyEvent(ASCIIKeyCode::A, key_event); break;
	case 6:keyEvent(ASCIIKeyCode::A, key_event); break;
	case 7:keyEvent(ASCIIKeyCode::A, key_event); keyEvent(ASCIIKeyCode::W, key_event); break;
	default:
		break;
	}

	PlayerPos now;
	while (true)
	{
		CImage window_image;
		getWindowPic(window_image);
		if (!getPlayerPosition(window_image,now)) {
			//读取失败，退出
			break;
		}

		if (hypot(fabs(now.x - begin.x), fabs(now.z - begin.z)) > distance - distance / (distance + 1))
			break;
		//cout << "move_inDistance:" << x << " " << y << " " << z << endl;
		//cout << hypot(fabs(x - begin_x), fabs(z - begin_z))<<endl;
		usleep(10);
	}

	//松开移动键
	key_event = KeyEvent::KeyUp;
	switch (direction)
	{
	case 0:keyEvent(ASCIIKeyCode::W, key_event); break;
	case 1:keyEvent(ASCIIKeyCode::W, key_event); keyEvent(ASCIIKeyCode::D, key_event); break;
	case 2:keyEvent(ASCIIKeyCode::D, key_event); break;
	case 3:keyEvent(ASCIIKeyCode::D, key_event); keyEvent(ASCIIKeyCode::S, key_event); break;
	case 4:keyEvent(ASCIIKeyCode::S, key_event); break;
	case 5:keyEvent(ASCIIKeyCode::S, key_event); keyEvent(ASCIIKeyCode::A, key_event); break;
	case 6:keyEvent(ASCIIKeyCode::A, key_event); break;
	case 7:keyEvent(ASCIIKeyCode::A, key_event); keyEvent(ASCIIKeyCode::W, key_event); break;
	default:
		break;
	}

	//松开SHIFT
	if (shift) {
		keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyUp);
	}
}

bool ImagePerformer120::isLookingAtBlock(const CImage& f3_image)
{
	if (f3_image.IsNull())
		return false;
	return image_handler->isLookingAtBlock(Cimage2Mat(f3_image));
}

bool ImagePerformer120::getLookingAtBlock(const CImage& f3_image, BlockInfo& block_info)
{
	return image_handler->getLookingAtBlock(Cimage2Mat(f3_image),block_info);
}

bool ImagePerformer120::getLookingAtBlockName(const CImage& f3_image, string& blockname)
{
	return image_handler->getLookingAtBlockName(Cimage2Mat(f3_image),blockname);
}

bool ImagePerformer120::getLookingAtBlockPos(const CImage& f3_image, BlockPos& block_pos)
{
	return image_handler->getLookingAtBlockPos(Cimage2Mat(f3_image),block_pos);
}

bool ImagePerformer120::ifPosCanRead(const CImage& f3_image)
{
	if (f3_image.IsNull())
		return false;
	return image_handler->ifPosCanRead(Cimage2Mat(f3_image));
}

bool ImagePerformer120::ifDirectionCanRead(const CImage& f3_image)
{
	if (f3_image.IsNull())
		return false;
	return image_handler->ifDirectionCanRead(Cimage2Mat(f3_image));
}

bool ImagePerformer120::getPlayerPosition(const CImage& f3_image,PlayerPos& player_pos)
{
	return image_handler->getPlayerPosition(Cimage2Mat(f3_image),player_pos);
}

bool ImagePerformer120::getPlayerFacingDirection(const CImage& f3_image,PlayerFacing& player_facing)
{
	return image_handler->getPlayerFacingDirection(Cimage2Mat(f3_image),player_facing);
}

void ImagePerformer120::readContain(const CImage& f3_img, Contain& contain)
{
	return image_handler->readContain(Cimage2Mat(f3_img), contain);
}

void ImagePerformer120::keyEvent(ASCIIKeyCode key, KeyEvent key_event)
{
	performer->keyEvent(key, key_event);
}

void ImagePerformer120::clickNumberKey(int num)
{
	performer->clickNumberKey(num);
}

void ImagePerformer120::clickKey(ASCIIKeyCode key, int interval_time, int delay_time)
{
	performer->clickKey(key, interval_time, delay_time);
}

void ImagePerformer120::moveMouseToPoint(int x, int y, bool absolute_coordinates)
{
	performer->moveMouseToPoint(x, y, absolute_coordinates);
}

void ImagePerformer120::moveMouse(int dx, int dy)
{
	performer->moveMouse(dx, dy);
}

void ImagePerformer120::moveMouseLinearly_inTime(float directionRad, int distance, int militime)
{
	performer->moveMouseLinearly_inTime(directionRad, distance, militime);
}

void ImagePerformer120::moveMouseLinearly_inSpeed(float directionRad, int distance, float speed)
{
	performer->moveMouseLinearly_inSpeed(directionRad, distance, speed);
}

POINT ImagePerformer120::getMousePosition()
{
	return performer->getMousePosition();
}

void ImagePerformer120::mouseEvent(MouseEvent mouse_event)
{
	performer->mouseEvent(mouse_event);
}

void ImagePerformer120::turnHead_x(float rad, float rad_speed, bool right)
{
	performer->turnHead_x(rad, rad_speed, right);
}

void ImagePerformer120::turnHead_y(float rad, float rad_speed, bool up)
{
	performer->turnHead_y(rad, rad_speed, up);
}

void ImagePerformer120::changeFace_x(float rad_begin, float rad_target, float rad_speed)
{
	performer->changeFace_x(rad_begin, rad_target, rad_speed);
}

void ImagePerformer120::changeFace_y(float rad_begin, float rad_target, float rad_speed)
{
	performer->changeFace_y(rad_begin, rad_target, rad_speed);
}

void ImagePerformer120::movePlayerPosition_inDistance(int direction, float distance, float move_speed, bool shift)
{
	performer->movePlayerPosition_inDistance(direction, distance, move_speed, shift);
}

void ImagePerformer120::movePlayerPosition_inTime(int direction, int militime, bool shift)
{
	performer->movePlayerPosition_inTime(direction, militime, shift);
}

HWND ImagePerformer120::getWindow()
{
	return performer->getWindow();
}

POINT ImagePerformer120::getWindowPos()
{
	return performer->getWindowPos();
}

void ImagePerformer120::getWindowSize(int& width, int& height)
{
	performer->getWindowSize(width, height);
}

void ImagePerformer120::changeWinodw(HWND window)
{
	performer->changeWinodw(window);
}

void ImagePerformer120::refreshWindowPositionAndSize()
{
	performer->refreshWindowPositionAndSize();
}

void ImagePerformer120::setWindowPos(int x, int y)
{
	performer->setWindowPos(x, y);
}

void ImagePerformer120::setWindowSize(int width, int height)
{
	performer->setWindowSize(width, height);
}

void ImagePerformer120::setWindowSize(int f_size_type)
{
	performer->setWindowSize(f_size_type);
}

void ImagePerformer120::guaji(int seconds)
{
	performer->guaji(seconds);
}

void ImagePerformer120::backGame()
{
	performer->refreshWindowPositionAndSize();
	performer->backGame();
}

void ImagePerformer120::speak(string str)
{
	performer->speak(str);
}

void ImagePerformer120::randomSpeak(string str)
{
	performer->randomSpeak(str);
}

void ImagePerformer120::resTp(string destination)
{
	performer->resTp(destination);
}

void ImagePerformer120::useInstruction(string instruction)
{
	performer->useInstruction(instruction);
}

string ImagePerformer120::getPackageInfo()
{
	return performer->getPackageInfo();
}

shared_ptr<Package> ImagePerformer120::getPackage()
{
	return performer->getPackage();
}

shared_ptr<Package> ImagePerformer120::setPackage(shared_ptr<Package> package)
{
	return performer->setPackage(package);
}

void ImagePerformer120::open_Or_closePackage()
{
	performer->open_Or_closePackage();
}

void ImagePerformer120::getWindowPic(WindowCImage& image)
{
	int width = 0, height = 0;
	performer->getWindowSize(width, height);
	getWindowPic(image, width, height, 0, 0);
}

void ImagePerformer120::getWindowPic(WindowCImage& image, int width, int height, int left_x, int top_y)
{
	//refreshWindowPositionAndSize();
	//由于网易禁止窗口截屏了，所以不得已用桌面截屏代替
	//scriptImageHandler.getWindowPic(image, 0, 0, windowWidth, windowHeight, 0, 0);
	if (!image.IsNull()) {
		image.Destroy();
	}
	auto p = performer->getWindowPos();
	imageHandle::getWindowPic(nullptr, image, 0, 0, width, height, p.x + left_x, p.y + top_y);
}

void ImagePerformer120::getF3Pic(WindowCImage& image)
{
	int width = 0, height = 0;
	performer->getWindowSize(width, height);
	getWindowPic(image, width, (int)(height * 0.5), 0, 0);
}

int ImagePerformer120::getHand()
{
	return performer->getHand();
}

void ImagePerformer120::setHand(int hand)
{
	return performer->setHand(hand);
}

void ImagePerformer120::changeHand(int hand)
{
	performer->changeHand(hand);
}

void ImagePerformer120::putBlock(bool change_package)
{
	performer->putBlock(change_package);
}

void ImagePerformer120::moveMouseAndClickLeft(int x, int y, bool absolute, int move_delay, int click_delay)
{
	performer->moveMouseAndClickLeft(x, y, absolute, move_delay, click_delay);
}

void ImagePerformer120::readPackage(const CImage& img)
{
	readContain(img, *performer->getPackage());
}

ImagePerformer120::ImagePerformer120(HWND window,shared_ptr<NoImagePerformer> performer , shared_ptr<ReadAllInfo> image_handler):
	image_handler(image_handler),
	performer(performer)
{
}

PlayerStatus ImagePerformer120::getAllPlayerInfo(CImage img)
{
	PlayerStatus player_status;
	player_status.is_F3_can_read = ifPosCanRead(img);
	player_status.is_looking_at_block = isLookingAtBlock(img);

	if (player_status.is_F3_can_read) {
		getPlayerPosition(img, player_status.player_pos);
		getPlayerFacingDirection(img, player_status.facing_direction);
	}
	if (player_status.is_looking_at_block) {
		getLookingAtBlock(img, player_status.block_info);
	}
	return player_status;


	/*PlayerStatus player_status;
	TimeCounter tc,tc2;
	int time,total_time;
	tc2.begin();
	tc.begin();
	player_status.is_F3_can_read = ifPosCanRead(img);
	time = tc.end();
	cout << "ImagePerformer120::getAllPlayerInfo:ifPosCanRead:" << time << endl;

	tc.begin();
	player_status.is_looking_at_block = isLookingAtBlock(img);
	time = tc.end();
	cout << "ImagePerformer120::getAllPlayerInfo:isLookingAtBlock:" << time << endl;

	if (player_status.is_F3_can_read) {
		tc.begin();
		getPlayerPosition(img,player_status.player_pos);
		time = tc.end();
		cout << "ImagePerformer120::getAllPlayerInfo:getPlayerPosition:" << time << endl;

		tc.begin();
		getPlayerFacingDirection(img, player_status.facing_direction);
		time = tc.end();
		cout << "ImagePerformer120::getAllPlayerInfo:getPlayerFacingDir" << time << endl;
	}
	if (player_status.is_looking_at_block) {
		tc.begin();
		getLookingAtBlock(img,player_status.block_info);
		time = tc.end();
		cout << "ImagePerformer120::getAllPlayerInfo:getLookingAtBlock:" << time << endl;
	}
	total_time = tc2.end();
	cout << "ImagePerformer120::getAllPlayerInfo:Total:" << total_time << endl << endl;
	return player_status;*/
}

shared_ptr<ReadAllInfo> ImagePerformer120::setImageReader(shared_ptr<ReadAllInfo> reader)
{
	auto ori = image_handler;
	image_handler = reader;
	return image_handler;
}

shared_ptr<ReadAllInfo> ImagePerformer120::getImageReader()
{
	return image_handler;
}

shared_ptr<NoImagePerformer> ImagePerformer120::setPerformer(shared_ptr<NoImagePerformer> performer)
{
	auto ori = this->performer;
	this->performer = performer;
	return ori;
}

shared_ptr<NoImagePerformer> ImagePerformer120::getPerformer()
{
	return performer;
}