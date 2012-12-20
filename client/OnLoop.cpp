#include "client/GameClient.h"

using namespace std;
void GameClient::OnLoop() {
	if(pressedup == true){
		CameraOnMove(0, -10);
	}else if(pressedright){
		CameraOnMove(10, 0);
	}else if(presseddown){
		CameraOnMove(0, 10);
	}else if(pressedleft){
		CameraOnMove(-10, 0);
	}
}
