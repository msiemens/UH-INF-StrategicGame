#include "client/GameClient.h"

using namespace std;
void GameClient::OnRender() {
    //CArea::AreaControl.OnRender(Surf_Display, CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());
    SDL_Flip(Surf_Display);
}
