//=====================================
//
//GameMain.h
//�@�\:�Q�[�����C������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "../main.h"
#include "../Framework/Core/BaseGame.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameMain : public BaseGame
{
public:
	GameMain(HINSTANCE hInstance, HWND hWnd);

	void Update() override;
};
#endif