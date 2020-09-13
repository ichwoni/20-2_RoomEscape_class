#include <bangtal.h>
using namespace bangtal;


int main() {

	// 1. ��� ����
	auto scene1 = Scene::create("Room1", "Images/���-1.png");
	auto scene2 = Scene::create("Room2", "Images/���-2.png");
	auto scene3 = Scene::create("Room3", "Images/���-1.png");

	// ���� ����
	auto key = Object::create("Images/����.png", scene1, 600, 150);
	key->setScale(0.4f);

	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();	//�κ��丮�� �ֱ� ���� �Լ� --> pick()
		return true;
		});

	// ���� '��'�� ȭ�� ���� --> ���踦 ������ �뵵. ���߿� ��������� ���谡 ������
	auto flowerpot_moved = false;
	auto flowerpot = Object::create("Images/ȭ��.png", scene1, 550, 150);
	flowerpot->setScale(1.1f);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (flowerpot_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot->locate(scene1, 450, 150);
				flowerpot_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot->locate(scene1, 650, 150);
				flowerpot_moved = true;
			}
		}
		return true;
		});

	// 3. ���� ����
	auto open1 = false;
	auto door1 = Object::create("Images/��-������-����.png", scene1, 800, 270);

	// 4. ���� Ŭ���ϸ� �̵�  // lamda function [&]
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		// 5. ���� ���� ���¸� ���� ����
		//    ���� ���� ���¸� ���� ����
		if (open1 == true) {	// �� ���� ����
			scene2->enter(); // ��� ��ȯ
		}
		else if (key->isHanded()) {					//�� ���� ����
			door1->setImage("Images/��-������-����.png");
			open1 = true;
		}
		else {
			showMessage("We need a key to open this.");
		}

		return true;
		});

	// room2
	auto door2 = Object::create("Images/��-����-����.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	auto open3 = false;
	auto door3 = Object::create("Images/��-������-����.png", scene2, 910, 270);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open3 == true) {	// �� ���� ����
			scene3->enter();
		}
		else {					// �� ���� ����
			door3->setImage("Images/��-������-����.png");
			open3 = true;
		}

		return true;
		});

	// room3
	auto door4 = Object::create("Images/��-����-����.png", scene3, 250, 290);
	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
		});

	// ȭ�� �ڿ� ������ ��
	auto open5 = false;
	auto door5 = Object::create("Images/��-������-����.png", scene3, 800, 270);
	door5->setScale(0.6f);

	auto flowerpot_moved_2 = false;
	auto flowerpot_2 = Object::create("Images/ȭ��.png", scene3, 750, 260);
	flowerpot_2->setScale(1.1f);
	flowerpot_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (flowerpot_moved_2 == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot_2->locate(scene3, 650, 270);
				flowerpot_moved_2 = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot_2->locate(scene3, 840, 220);
				flowerpot_moved_2 = true;
			}
		}
		return true;
		});		// ȭ���� ������ ġ������ �� ����

	door5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open5 == true) {	// �� ���� ����
			endGame();
		}
		else {					// �� ���� ����
			door5->setImage("Images/��-������-����.png");
			open5 = true;
		}

		return true;
		});

	// 2. ���� ����
	startGame(scene1);

	return 0;
}