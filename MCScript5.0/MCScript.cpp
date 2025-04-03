#include "MCScript.h"
#include"Tools.h"

MCScript::MCScript(NoImagePerformer* noImagePerformer):
	m_noImagePerformer(noImagePerformer),
	m_imagePerformer(nullptr)
{
}

MCScript::MCScript(ImagePerformer* imagePerformer):
	m_noImagePerformer(imagePerformer),
	m_imagePerformer(imagePerformer)
{
}

void MCScript::shouCai()
{
	NoImagePerformer* performer = m_noImagePerformer;
	shared_ptr<Package> package = performer->getPackage();
	package->setPackageStatus(PackageStatus::USE_BIG_BOX);//设置背包打开模式

	performer->setWindowSize(1750, 945); sleep(5000);
	performer->backGame();sleep(1000);
	performer->clickNumberKey(9);

	//while (true) {
	//	performer->mouseEvent(MouseEvent::ClickRight);
	//	sleep(100);
	//}
	int lun = 1;
	while (true) {
		for (int num = 1; num <= 16; num++) {		//有16片菜地

			
			LogInfo("第" + std::to_string(lun) + "轮第" + std::to_string(num) + "号田");

			/*if (num % 16 == 1) {
				performer->speak("pw 静海，好康地图画，精美字画，还有免费地图画。");
				sleep(1000);
			}*/

			bool b = num % 2 == 1;		//是单数还是双数号菜地
			MoveMode push_1 = b ? MoveMode::LeftDown : MoveMode::RightDown;
			MoveMode up_1 = b ? MoveMode::LeftUp : MoveMode::RightUp;
			MoveMode push_2 = b ? MoveMode::RightDown : MoveMode::LeftDown;
			MoveMode up_2 = b ? MoveMode::RightUp : MoveMode::LeftUp;

			performer->useInstruction("/home " + std::to_string(num));
			sleep(3000);

			//8行菜地
			for (int i = 0; i < 4; i++) {
				//两轮收菜
				for (int j = 0; j < 2; j++) {
					move(push_1); sleep(300);		//破坏菜移动
					if (j == 0)	moveForTime(MoveDirection::Back, 100, 0);//若为第一轮需要向后微调
					//sleep(11000);
					mouseEventForTime(SMouseEvent::ClickRight, 11000, 50);		//不断右键破坏菜
					move(up_1);	sleep(300);			//结束破坏菜移动
					move(push_2); sleep(11000);		//回收菜移动
					if (j == 0)	move(MoveMode::BackDown); sleep(400);		//若为第一轮需后移到下一行
					move(up_2); sleep(300);		//结束移动
					if (j == 0) {
						move(MoveMode::BackUp);		//若为第一轮还要结束后退
						moveForTime(MoveDirection::Front, 500, 200);	//向前调位
					}
				}
				//回收菜
				openBox(); sleep(3000);
				move(MoveMode::ShiftDown); sleep(500);		//按下SHIFT
				for (int x = 1; x <= 9; x++) {		//清空背包
					POINT p = package->getLatticeRelativeMidPos(x, 4);
					performer->moveMouseAndClickLeft(p.x, p.y, false);
				}
				move(MoveMode::ShiftUp); sleep(500);	//松开SHIFT
				closeBoxOrPackage(); sleep(1000);		//关闭箱子
				//去往第三行
				move(MoveMode::BackDown); sleep(300);
				move(MoveMode::ClickSpace); sleep(300);
				move(MoveMode::BackUp); sleep(300);
			}
		}
		lun++;
	}
}

void MCScript::move(MoveMode move_mode)
{
	NoImagePerformer* performer = m_noImagePerformer;
	switch (move_mode)
	{
	case MCScript::MoveMode::LeftDown:performer->keyEvent(ASCIIKeyCode::A, KeyEvent::KeyDown);
		break;
	case MCScript::MoveMode::LeftUp:performer->keyEvent(ASCIIKeyCode::A, KeyEvent::KeyUp);
		break;
	case MCScript::MoveMode::RightDown:performer->keyEvent(ASCIIKeyCode::D, KeyEvent::KeyDown);
		break;
	case MCScript::MoveMode::RightUp:performer->keyEvent(ASCIIKeyCode::D, KeyEvent::KeyUp);
		break;
	case MCScript::MoveMode::FrontDown:performer->keyEvent(ASCIIKeyCode::W, KeyEvent::KeyDown);
		break;
	case MCScript::MoveMode::FrontUp:performer->keyEvent(ASCIIKeyCode::W, KeyEvent::KeyUp);
		break;
	case MCScript::MoveMode::BackDown:performer->keyEvent(ASCIIKeyCode::S, KeyEvent::KeyDown);
		break;
	case MCScript::MoveMode::BackUp:performer->keyEvent(ASCIIKeyCode::S, KeyEvent::KeyUp);
		break;
	case MCScript::MoveMode::ShiftDown:performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyDown);
		break;
	case MCScript::MoveMode::ShiftUp:performer->keyEvent(ASCIIKeyCode::SHIFT, KeyEvent::KeyUp);
		break;
	case MCScript::MoveMode::SpaceDown:performer->keyEvent(ASCIIKeyCode::SPACEBAR, KeyEvent::KeyDown);
		break;
	case MCScript::MoveMode::SpaceUp:performer->keyEvent(ASCIIKeyCode::SPACEBAR, KeyEvent::KeyUp);
		break;
	case MCScript::MoveMode::ClickSpace:move(MoveMode::SpaceDown); sleep(100); move(MoveMode::SpaceUp);
		break;
	default:
		break;
	}
}

void MCScript::moveForTime(MoveDirection dir, int interval_time, int delay_time)
{
	switch (dir)
	{
	case MCScript::MoveDirection::Left:
		move(MoveMode::LeftDown); sleep(interval_time); move(MoveMode::LeftUp); sleep(delay_time);
		break;
	case MCScript::MoveDirection::Right:
		move(MoveMode::RightDown); sleep(interval_time); move(MoveMode::RightUp); sleep(delay_time);
		break;
	case MCScript::MoveDirection::Front:
		move(MoveMode::FrontDown); sleep(interval_time); move(MoveMode::FrontUp); sleep(delay_time);
		break;
	case MCScript::MoveDirection::Back:
		move(MoveMode::BackDown); sleep(interval_time); move(MoveMode::BackUp); sleep(delay_time);
		break;
	case MCScript::MoveDirection::Jump:
		move(MoveMode::SpaceDown); sleep(interval_time); move(MoveMode::SpaceUp); sleep(delay_time);
		break;
	default:
		break;
	}
}

void MCScript::mouseEvent(SMouseEvent mouse_event)
{
	NoImagePerformer* performer = m_noImagePerformer;
	switch (mouse_event)
	{
	case MCScript::SMouseEvent::LeftDown:performer->mouseEvent(MouseEvent::LeftDown);
		break;
	case MCScript::SMouseEvent::LeftUp:performer->mouseEvent(MouseEvent::LeftUp);
		break;
	case MCScript::SMouseEvent::RightDown:performer->mouseEvent(MouseEvent::RightDown);
		break;
	case MCScript::SMouseEvent::RightUp:performer->mouseEvent(MouseEvent::RightUp);
		break;
	case MCScript::SMouseEvent::ClickLeft:performer->mouseEvent(MouseEvent::ClickLeft);
		break;
	case MCScript::SMouseEvent::ClickRight:performer->mouseEvent(MouseEvent::ClickRight);
		break;
	default:
		break;
	}
}

void MCScript::sleep(int militime)
{
	usleep(militime);
}

void MCScript::openBox()
{
	mouseEvent(SMouseEvent::ClickRight);
}

void MCScript::closeBoxOrPackage()
{
	m_noImagePerformer->keyEvent(ASCIIKeyCode::E, KeyEvent::ClickKey);
}

void MCScript::mouseEventForTime(SMouseEvent mouse_event, int militime, int interval_time)
{
	NoImagePerformer* performer = m_noImagePerformer;
	TimeCounter tc(TimeCounterMode::MILISECOND);
	tc.begin();
	while (tc.end() < militime) {
		mouseEvent(mouse_event);
		int time = tc.end();
		sleep(MIN(militime-time,interval_time));
	}
}
