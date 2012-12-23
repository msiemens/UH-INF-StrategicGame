#include "client/GameClient.h"

using namespace std;
void GameClient::OnLoop() {
	if(pressedup){
		CameraOnMove(0, -100);
	}else if(pressedright){
		CameraOnMove(100, 0);
	}else if(presseddown){
		CameraOnMove(0, 100);
	}else if(pressedleft){
		CameraOnMove(-100, 0);
	}
}
