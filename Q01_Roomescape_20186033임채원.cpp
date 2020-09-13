#include <bangtal.h>
using namespace bangtal;


int main() {

	// 1. 장면 생성
	auto scene1 = Scene::create("Room1", "Images/배경-1.png");
	auto scene2 = Scene::create("Room2", "Images/배경-2.png");
	auto scene3 = Scene::create("Room3", "Images/배경-1.png");

	// 열쇠 생성
	auto key = Object::create("Images/열쇠.png", scene1, 600, 150);
	key->setScale(0.4f);

	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();	//인벤토리에 넣기 위한 함수 --> pick()
		return true;
		});

	// 열쇠 '앞'의 화분 생성 --> 열쇠를 가리는 용도. 나중에 선언해줘야 열쇠가 가려짐
	auto flowerpot_moved = false;
	auto flowerpot = Object::create("Images/화분.png", scene1, 550, 150);
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

	// 3. 문을 생성
	auto open1 = false;
	auto door1 = Object::create("Images/문-오른쪽-닫힘.png", scene1, 800, 270);

	// 4. 문을 클릭하면 이동  // lamda function [&]
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		// 5. 문이 열린 상태면 게임 종료
		//    문이 닫힌 상태면 문을 개방
		if (open1 == true) {	// 문 개방 상태
			scene2->enter(); // 장면 전환
		}
		else if (key->isHanded()) {					//문 닫힘 상태
			door1->setImage("Images/문-오른쪽-열림.png");
			open1 = true;
		}
		else {
			showMessage("We need a key to open this.");
		}

		return true;
		});

	// room2
	auto door2 = Object::create("Images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	auto open3 = false;
	auto door3 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 910, 270);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open3 == true) {	// 문 개방 상태
			scene3->enter();
		}
		else {					// 문 닫힘 상태
			door3->setImage("Images/문-오른쪽-열림.png");
			open3 = true;
		}

		return true;
		});

	// room3
	auto door4 = Object::create("Images/문-왼쪽-열림.png", scene3, 250, 290);
	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
		});

	// 화분 뒤에 숨겨진 문
	auto open5 = false;
	auto door5 = Object::create("Images/문-오른쪽-닫힘.png", scene3, 800, 270);
	door5->setScale(0.6f);

	auto flowerpot_moved_2 = false;
	auto flowerpot_2 = Object::create("Images/화분.png", scene3, 750, 260);
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
		});		// 화분이 옆으로 치워져야 문 등장

	door5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open5 == true) {	// 문 개방 상태
			endGame();
		}
		else {					// 문 닫힘 상태
			door5->setImage("Images/문-오른쪽-열림.png");
			open5 = true;
		}

		return true;
		});

	// 2. 게임 시작
	startGame(scene1);

	return 0;
}