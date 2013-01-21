#include "client/GameClient.h"

using namespace std;
void GameClient::OnLoop() {
	if(pressedup){
		CameraOnMove(0, -10);
	}
	if(pressedright){
		CameraOnMove(10, 0);
	}
	if(presseddown){
		CameraOnMove(0, 10);
	}
	if(pressedleft){
		CameraOnMove(-10, 0);
	}
}
