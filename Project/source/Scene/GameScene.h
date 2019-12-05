//=====================================
//
//GameScene.h
//�@�\:�Q�[���V�[������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#define _CRTDBG_MAP_ALLOC
#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"
#include "../../Framework/Pattern/BaseState.h"
#include "../../Framework/Pattern/Delegate.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class FieldCamera;
class UDPServer;
class GameParticleManager;
class RobotActor;


/**************************************
�N���X��`
***************************************/
class GameScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	FieldCamera* fieldCamera;					//�t�B�[���h�J����
	GameParticleManager *ParticleManager;		// �p�[�e�B�N���}�l�[�W���[
	UDPServer *Server;							// �T�[�o�[
	RobotActor *Robot;
};
#endif