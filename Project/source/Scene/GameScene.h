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
class PlaceActor;
class UDPServer;
class GameParticleManager;

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

	//�X�e�[�g��\���񋓎q
	enum State
	{
		Initialize,
		Idle,
		Max
	};

	//�X�e�[�g�J�ڏ���
	void ChangeState(State next);

private:
	using SceneState = BaseState<GameScene, State>;

	//�V�[���X�e�[�g�}�V��
	std::vector<SceneState*> fsm;
	std::vector<PlaceActor*> PlaceActorContainer;
	State currentState, prevState;
	FieldCamera* fieldCamera;					//�t�B�[���h�J����
	GameParticleManager *ParticleManager;		// �p�[�e�B�N���}�l�[�W���[
	UDPServer *Server;							// �T�[�o�[

	//�e�X�e�[�g�N���X
	class GameInit;
	class GameIdle;

	// ���b�V���A�e�N�X�`����ǂݍ���
	void LoadResource(void);
};
#endif