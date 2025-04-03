#include<opencv2/opencv.hpp>
#include"NoImagePerformer120.h"
#include"Tools.h"
#include<Windows.h>

NoImagePerformer120::NoImagePerformer120(HWND window, std::shared_ptr<Package> package) :
	package(package),
	hand(0)
{
	changeWinodw(window);
}

std::shared_ptr<Package> NoImagePerformer120::setPackage(std::shared_ptr<Package> package)
{
	std::shared_ptr<Package> ori_package = this->package;
	this->package = package;
	return ori_package;
}

void NoImagePerformer120::keyEvent(ASCIIKeyCode key, KeyEvent key_event)
{
	switch (key_event)
	{
	case KeyEvent::KeyDown:keybd_event((byte)key, (byte)ASCIIKeyCode2KeyBoardCode(key), 0, 0);
		break;
	case KeyEvent::KeyUp:keybd_event((byte)key, (byte)ASCIIKeyCode2KeyBoardCode(key), 2, 0);
		break;
	case KeyEvent::ClickKey:keyEvent(key, KeyEvent::KeyDown); usleep(50); keyEvent(key, KeyEvent::KeyUp);
		break;
	default:
		break;
	}
}

void NoImagePerformer120::clickNumberKey(int num)
{
	ASCIIKeyCode ascii_key_code = ASCIIKeyCode::ONE;
	switch (num)
	{
	case 0:ascii_key_code = ASCIIKeyCode::ZERO; break;
	case 1:ascii_key_code = ASCIIKeyCode::ONE; break;
	case 2:ascii_key_code = ASCIIKeyCode::TWO; break;
	case 3:ascii_key_code = ASCIIKeyCode::THREE; break;
	case 4:ascii_key_code = ASCIIKeyCode::FOUR; break;
	case 5:ascii_key_code = ASCIIKeyCode::FIVE; break;
	case 6:ascii_key_code = ASCIIKeyCode::SIX; break;
	case 7:ascii_key_code = ASCIIKeyCode::SEVEN; break;
	case 8:ascii_key_code = ASCIIKeyCode::EIGHT; break;
	case 9:ascii_key_code = ASCIIKeyCode::NINE; break;
	default:
		break;
	}

	keyEvent(ascii_key_code, KeyEvent::ClickKey);
}

void NoImagePerformer120::clickKey(ASCIIKeyCode key, int interval_time, int delay_time)
{
	keyEvent(key, KeyEvent::KeyDown);
	usleep(interval_time);
	keyEvent(key, KeyEvent::KeyUp);
	usleep(delay_time);
}


void NoImagePerformer120::moveMouseToPoint(int x, int y, bool absolute_coordinates)
{
	POINT point;
	point.x = x;
	point.y = y;
	if (!absolute_coordinates) {//��������꣬����������point
		ClientToScreen(window, &point);
	}
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, (point.x + 1) * 65535 / screenWidth, (point.y + 1) * 65535 / screenHeight, 0, 0);
}

void NoImagePerformer120::moveMouse(int dx, int dy)
{
	mouse_event(MOUSEEVENTF_MOVE, dx, dy, 0, 0);
}

void NoImagePerformer120::moveMouseLinearly_inTime(float directionRad, int distance, int militime)
{
	int refreshInteration = 20;
	//ÿ������unit�����룬Ȼ������ȷ����ľ���ֵ����1�����ƶ��������֣�Ȼ����������ּ�ȥ
	double cos_unit_x = distance * cos(directionRad) / militime * refreshInteration;
	double sin_unit_y = distance * sin(directionRad) / militime * refreshInteration;

	double fractionalPart_x = 0;
	double fractionalPart_y = 0;

	for (int i = 0; i < militime / refreshInteration; i++) {
		fractionalPart_x += cos_unit_x;
		fractionalPart_y += sin_unit_y;
		//���������ִ���һ��������ƶ�������ĵ�λ
		if (fabs(fractionalPart_x) > 1 || fabs(fractionalPart_y) > 1) {
			POINT mousePos;
			GetCursorPos(&mousePos);
			moveMouseToPoint(mousePos.x + (int)fractionalPart_x, mousePos.y - (int)fractionalPart_y);
			fractionalPart_x -= (int)fractionalPart_x;
			fractionalPart_y -= (int)fractionalPart_y;
		}
		usleep(refreshInteration);
	}
}

void NoImagePerformer120::moveMouseLinearly_inSpeed(float directionRad, int distance, float speed)
{
	//�����ԣ�ÿ��ˢ��60�����ұȽ��ȶ�,����ÿ��50�Σ��Ƕ���������Ϊ0.1028����С�ƶ��Ƕ�Ϊspeed*refreshInteration*0.1028
	//speed��ƽ��ÿms���پ��룬refreshInteration�������������
	int refreshInteration = 20;
	//ÿ������unit�����룬Ȼ������ȷ����ľ���ֵ����1�����ƶ��������֣�Ȼ����������ּ�ȥ
	double cos_unit_x = speed * cos(directionRad) * refreshInteration;
	double sin_unit_y = speed * sin(directionRad) * refreshInteration;

	double fractionalPart_x = 0;
	double fractionalPart_y = 0;

	for (int i = 0; i < distance / speed / refreshInteration; i++) {
		fractionalPart_x += cos_unit_x;
		fractionalPart_y += sin_unit_y;
		//���������ִ���һ��������ƶ�������ĵ�λ
		if (fabs(fractionalPart_x) > 1 || fabs(fractionalPart_y) > 1) {
			/*POINT mousePos;
			GetCursorPos(&mousePos);
			moveMouseToPoint(mousePos.x + (int)fractionalPart_x, mousePos.y - (int)fractionalPart_y);*/
			moveMouse((int)fractionalPart_x, -(int)fractionalPart_y);
			fractionalPart_x -= (int)fractionalPart_x;
			fractionalPart_y -= (int)fractionalPart_y;
		}
		usleep(refreshInteration);
	}
}

POINT NoImagePerformer120::getMousePosition()
{
	POINT point;
	GetCursorPos(&point);
	return point;
}

void NoImagePerformer120::mouseEvent(MouseEvent _mouse_event)
{
	switch (_mouse_event)
	{
	case MouseEvent::LeftDown:mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); break;//����������
	case MouseEvent::LeftUp:mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); break;//������̧��
	case MouseEvent::RightDown:mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0); break;//����Ҽ�����
	case MouseEvent::RightUp:mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0); break;//����Ҽ�̧��
	case MouseEvent::ClickLeft:mouseEvent(MouseEvent::LeftDown); usleep(20); mouseEvent(MouseEvent::LeftUp); break;//���������
	case MouseEvent::ClickRight:mouseEvent(MouseEvent::RightDown); usleep(20); mouseEvent(MouseEvent::RightUp); break;//����Ҽ����
	default:break;
	}
}

std::shared_ptr<Package> NoImagePerformer120::getPackage()
{
	return package;
}

void NoImagePerformer120::open_Or_closePackage()
{
	keyEvent(ASCIIKeyCode::E, KeyEvent::ClickKey);
}

void NoImagePerformer120::turnHead_x(float rad, float rad_speed, bool right)
{
	//�㶼��ÿ�ƶ�100����תͷ15��
	/*pix_speed=rad_speed/0.15/1000
	��С����=rad_speed/1000*interval_time
	�Ǿ�ȷ״̬*/
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

	//�Ǿ�ȷ����
	rad = fabs(rad);
	rad -= 360 * (int)(rad / 360);
	int length = (int)(rad / 0.15);
	double pix_speed = rad_speed / 0.15 / 1000;
	if (right) {
		moveMouseLinearly_inSpeed(0, length, pix_speed);
	}
	else {
		moveMouseLinearly_inSpeed(PI, length, pix_speed);
	}
}

void NoImagePerformer120::turnHead_y(float rad, float rad_speed, bool up)
{
	/*pix_speed=rad_speed/0.15/1000
	��С����=rad_speed/1000*interval_time*/
	rad = fabs(rad);
	rad = min(180, rad);

	//�Ǿ�ȷ����
	double dis_rad_radio = 0.15;//����Ƕȱ�
	int length = (int)(rad / dis_rad_radio);
	double pix_speed = rad_speed / dis_rad_radio / 1000;
	if (up) {
		moveMouseLinearly_inSpeed(PI / 2, length, pix_speed);
	}
	else {
		moveMouseLinearly_inSpeed(-PI / 2, length, pix_speed);
	}
}

void NoImagePerformer120::changeFace_x(float rad_begin, float rad_target, float rad_speed)
{
	//���ڰ�rad������Χ[180,180)�ĺ���
	auto transformRad = [](float rad) {
		//��rad������Χ(-360,360)
		rad -= (int)(rad / 360) * 360;
		//��rad������Χ[180,180)
		if (rad >= 180) {
			rad -= 360;
		}
		if (rad < -180) {
			rad += 360;
		}
		return rad;
		};
	//��beg��tar������Χ[-180,180)
	rad_begin = transformRad(rad_begin);
	rad_target = transformRad(rad_target);
	//���beg��tar���ת��
	float rad_distance = min(fabs(rad_begin - rad_target), 360 - fabs(rad_begin - rad_target));
	//�ж�������������ת��
	bool turnRight = rad_begin > rad_target + 180 || (rad_target > rad_begin && rad_target - rad_begin < 180);

	turnHead_x(rad_distance, rad_speed, turnRight);
}

void NoImagePerformer120::changeFace_y(float rad_begin, float rad_target, float rad_speed)
{
	//���beg��tar���ת��
	float rad_distance = fabs(rad_begin - rad_target);
	//�ж������ϻ�������ת��
	bool turnUp = rad_begin > rad_target;

	turnHead_y(rad_distance, rad_speed, turnUp);
}

void NoImagePerformer120::movePlayerPosition_inDistance(int direction, float distance, float move_speed, bool shift)
{
	if (direction < 0 || direction>7 || distance <= 0) {
		return;
	}

	//�Ǿ�ȷ�ƶ�
	int militime;
	militime = distance / move_speed * 1000;
	//cout << militime << "movePlayer_inDis" << endl;
	movePlayerPosition_inTime(direction, militime, shift);
}

void NoImagePerformer120::movePlayerPosition_inTime(int direction, int militime, bool shift)
{
	//�����������
	if (direction < 0 || direction>7 || militime <= 0) {
		return;
	}
	//����SHIFT
	if (shift) {
		keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyDown);
	}

	//�����ƶ���
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

	usleep(militime);

	//�ɿ��ƶ���
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

	//�ɿ�SHIFT
	if (shift) {
		keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyUp);
	}
}

HWND NoImagePerformer120::getWindow()
{
	return window;
}

POINT NoImagePerformer120::getWindowPos()
{
	POINT point;
	point.x = win_x;
	point.y = win_y;
	return point;
}

void NoImagePerformer120::getWindowSize(int& width, int& height)
{
	width = winWidth;
	height = winHeight;
}

void NoImagePerformer120::changeWinodw(HWND window)
{
	this->window = window;
	refreshWindowPositionAndSize();

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

void NoImagePerformer120::refreshWindowPositionAndSize()
{
	//���㴰�ڿ�ߺ����Ͻ�����
	RECT rect;
	GetClientRect(window, &rect);
	winHeight = rect.bottom - rect.top;
	winWidth = rect.right - rect.left;

	POINT point;
	point.x = 0;
	point.y = 0;
	ClientToScreen(window, &point);

	win_x = point.x;
	win_y = point.y;
}

void NoImagePerformer120::setWindowPos(int x, int y)
{
	MoveWindow(window, x, y, winWidth, winHeight, false);
	refreshWindowPositionAndSize();
}

void NoImagePerformer120::setWindowSize(int width, int height)
{
	RECT window_rect, client_rect;
	GetWindowRect(window, &window_rect);
	GetClientRect(window, &client_rect);
	int border_width = window_rect.right - window_rect.left - client_rect.right;
	int border_height = window_rect.bottom - window_rect.top - client_rect.bottom;

	MoveWindow(window, window_rect.left, window_rect.top, width + border_width, height + border_height, false);
	refreshWindowPositionAndSize();
}

void NoImagePerformer120::setWindowSize(int f_size_type)
{
	////setWindowSize����ͻ�ˢ�´���λ�úʹ�С
	//switch (f_size_type)
	//{
	//case SIZE_1740_945:setWindowSize(1740, 945); break;
	//default:
	//	break;
	//}
}

void NoImagePerformer120::guaji(int seconds)
{
	TimeCounter tc(TimeCounterMode::SECOND);
	tc.begin();
	while (tc.end()<seconds) {
		mouseEvent(MouseEvent::ClickLeft);
		Sleep(1000);
	}
}

void NoImagePerformer120::backGame()
{
	refreshWindowPositionAndSize();
	moveMouseToPoint(870, 270, false);
	usleep(200);
	mouseEvent(MouseEvent::ClickLeft);
}

void NoImagePerformer120::speak(string str)
{
	useInstruction(str);
}

void NoImagePerformer120::randomSpeak(string str)
{
}

void NoImagePerformer120::resTp(string destination)
{
	string address = "/res tp " + destination;
	useInstruction(address);
}

void NoImagePerformer120::useInstruction(string instruction)
{
	keyEvent(ASCIIKeyCode::T, KeyEvent::ClickKey);usleep(400);
	//������ճ����������
	setClipbar(instruction);

	keyEvent(ASCIIKeyCode::CTRL, KeyEvent::KeyDown);usleep(200);
	keyEvent(ASCIIKeyCode::V, KeyEvent::ClickKey);usleep(200);
	keyEvent(ASCIIKeyCode::CTRL, KeyEvent::KeyUp);usleep(200);
	keyEvent(ASCIIKeyCode::ENTER, KeyEvent::ClickKey);
}

string NoImagePerformer120::getPackageInfo()
{
	return package->getAllLatticeInfo();
}

int NoImagePerformer120::getHand()
{
	return hand;
}

void NoImagePerformer120::setHand(int hand)
{
	this->hand = hand;
}

void NoImagePerformer120::changeHand(int hand)
{
	if (!(1 <= hand && hand <= 9))
		ThrowException::throwException("NoImagePerformer120::changeHand", "hand����:" + std::to_string(hand));
	clickNumberKey(hand);
}

void NoImagePerformer120::moveMouseAndClickLeft(int x, int y, bool absolute, int move_delay, int click_delay)
{
	moveMouseToPoint(x, y, absolute);
	usleep(move_delay);
	mouseEvent(MouseEvent::ClickLeft);
	usleep(click_delay);
}

void NoImagePerformer120::putBlock(bool change_package)
{
	mouseEvent(MouseEvent::ClickRight);
	if (change_package) {
		if (!package->getLattice(hand, 4).removeItem(1))
			ThrowException::throwException("NoImagePerformer120::putBlock", "��Ʒ����ʧ��!");
	}
	//std::cout << "NoImagePerformer120::putBlock:\n" << package->getAllLatticeInfo() << std::endl;
}


void NoImagePerformer120::moveMouseAndClickLeft(int x, int y, int intervalMiliTime, int delayMiliTime, bool absolute_coordinate)
{
	moveMouseToPoint(x, y, absolute_coordinate);
	usleep(intervalMiliTime);
	mouseEvent(MouseEvent::ClickLeft);
	usleep(delayMiliTime);
}


void NoImagePerformer120::putBlock(int delay_militime, int handPos, bool operate_package)
{
	mouseEvent(MouseEvent::ClickRight);
	usleep(delay_militime);
	if (operate_package) {
		package->getLattice(handPos, 4).removeItem(1);
	}
}


KeyBoardCode ASCIIKeyCode2KeyBoardCode(ASCIIKeyCode keycode)
{
	switch (keycode)
	{
	case ASCIIKeyCode::ZERO:return KeyBoardCode::ZERO;
		break;
	case ASCIIKeyCode::ONE:return KeyBoardCode::ONE;
		break;
	case ASCIIKeyCode::TWO:return KeyBoardCode::TWO;
		break;
	case ASCIIKeyCode::THREE:return KeyBoardCode::THREE;
		break;
	case ASCIIKeyCode::FOUR:return KeyBoardCode::FOUR;
		break;
	case ASCIIKeyCode::FIVE:return KeyBoardCode::FIVE;
		break;
	case ASCIIKeyCode::SIX:return KeyBoardCode::SIX;
		break;
	case ASCIIKeyCode::SEVEN:return KeyBoardCode::SEVEN;
		break;
	case ASCIIKeyCode::EIGHT:return KeyBoardCode::EIGHT;
		break;
	case ASCIIKeyCode::NINE:return KeyBoardCode::NINE;
		break;
	case ASCIIKeyCode::A:return KeyBoardCode::A;
		break;
	case ASCIIKeyCode::B:return KeyBoardCode::B;
		break;
	case ASCIIKeyCode::C:return KeyBoardCode::C;
		break;
	case ASCIIKeyCode::D:return KeyBoardCode::D;
		break;
	case ASCIIKeyCode::E:return KeyBoardCode::E;
		break;
	case ASCIIKeyCode::F:return KeyBoardCode::F;
		break;
	case ASCIIKeyCode::G:return KeyBoardCode::G;
		break;
	case ASCIIKeyCode::H:return KeyBoardCode::H;
		break;
	case ASCIIKeyCode::I:return KeyBoardCode::I;
		break;
	case ASCIIKeyCode::J:return KeyBoardCode::J;
		break;
	case ASCIIKeyCode::K:return KeyBoardCode::K;
		break;
	case ASCIIKeyCode::L:return KeyBoardCode::L;
		break;
	case ASCIIKeyCode::M:return KeyBoardCode::M;
		break;
	case ASCIIKeyCode::N:return KeyBoardCode::N;
		break;
	case ASCIIKeyCode::O:return KeyBoardCode::O;
		break;
	case ASCIIKeyCode::P:return KeyBoardCode::P;
		break;
	case ASCIIKeyCode::Q:return KeyBoardCode::Q;
		break;
	case ASCIIKeyCode::R:return KeyBoardCode::R;
		break;
	case ASCIIKeyCode::S:return KeyBoardCode::S;
		break;
	case ASCIIKeyCode::T:return KeyBoardCode::T;
		break;
	case ASCIIKeyCode::U:return KeyBoardCode::U;
		break;
	case ASCIIKeyCode::V:return KeyBoardCode::V;
		break;
	case ASCIIKeyCode::W:return KeyBoardCode::W;
		break;
	case ASCIIKeyCode::X:return KeyBoardCode::X;
		break;
	case ASCIIKeyCode::Y:return KeyBoardCode::Y;
		break;
	case ASCIIKeyCode::Z:return KeyBoardCode::Z;
		break;
	case ASCIIKeyCode::SHIFT:return KeyBoardCode::SHIFT;
		break;
	case ASCIIKeyCode::SPACEBAR:return KeyBoardCode::SPACEBAR;
		break;
	case ASCIIKeyCode::XIEGANG:return KeyBoardCode::XIEGANG;
		break;
	case ASCIIKeyCode::CTRL:return KeyBoardCode::CTRL;
		break;
	case ASCIIKeyCode::ENTER:return KeyBoardCode::NONE;
		break;
	default:return KeyBoardCode::NONE;
		break;
	}
	return {};
}
