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
	package->setPackageStatus(PackageStatus::USE_BIG_BOX);//���ñ�����ģʽ

	performer->setWindowSize(1750, 945); sleep(5000);
	performer->backGame();sleep(1000);
	performer->clickNumberKey(9);

	//while (true) {
	//	performer->mouseEvent(MouseEvent::ClickRight);
	//	sleep(100);
	//}
	int lun = 1;
	while (true) {
		for (int num = 1; num <= 16; num++) {		//��16Ƭ�˵�

			
			LogInfo("��" + std::to_string(lun) + "�ֵ�" + std::to_string(num) + "����");

			/*if (num % 16 == 1) {
				performer->speak("pw �������ÿ���ͼ���������ֻ���������ѵ�ͼ����");
				sleep(1000);
			}*/

			bool b = num % 2 == 1;		//�ǵ�������˫���Ų˵�
			MoveMode push_1 = b ? MoveMode::LeftDown : MoveMode::RightDown;
			MoveMode up_1 = b ? MoveMode::LeftUp : MoveMode::RightUp;
			MoveMode push_2 = b ? MoveMode::RightDown : MoveMode::LeftDown;
			MoveMode up_2 = b ? MoveMode::RightUp : MoveMode::LeftUp;

			performer->useInstruction("/home " + std::to_string(num));
			sleep(3000);

			//8�в˵�
			for (int i = 0; i < 4; i++) {
				//�����ղ�
				for (int j = 0; j < 2; j++) {
					move(push_1); sleep(300);		//�ƻ����ƶ�
					if (j == 0)	moveForTime(MoveDirection::Back, 100, 0);//��Ϊ��һ����Ҫ���΢��
					//sleep(11000);
					mouseEventForTime(SMouseEvent::ClickRight, 11000, 50);		//�����Ҽ��ƻ���
					move(up_1);	sleep(300);			//�����ƻ����ƶ�
					move(push_2); sleep(11000);		//���ղ��ƶ�
					if (j == 0)	move(MoveMode::BackDown); sleep(400);		//��Ϊ��һ������Ƶ���һ��
					move(up_2); sleep(300);		//�����ƶ�
					if (j == 0) {
						move(MoveMode::BackUp);		//��Ϊ��һ�ֻ�Ҫ��������
						moveForTime(MoveDirection::Front, 500, 200);	//��ǰ��λ
					}
				}
				//���ղ�
				openBox(); sleep(3000);
				move(MoveMode::ShiftDown); sleep(500);		//����SHIFT
				for (int x = 1; x <= 9; x++) {		//��ձ���
					POINT p = package->getLatticeRelativeMidPos(x, 4);
					performer->moveMouseAndClickLeft(p.x, p.y, false);
				}
				move(MoveMode::ShiftUp); sleep(500);	//�ɿ�SHIFT
				closeBoxOrPackage(); sleep(1000);		//�ر�����
				//ȥ��������
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
