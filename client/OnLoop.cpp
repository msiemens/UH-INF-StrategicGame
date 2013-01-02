#include "client/GameClient.h"

using namespace std;
void GameClient::OnLoop() {
	if(pressedup){
		CameraOnMove(0, -20);
	}else if(pressedright){
		CameraOnMove(20, 0);
	}else if(presseddown){
		CameraOnMove(0, 20);
	}else if(pressedleft){
		CameraOnMove(-20, 0);
	}
}
