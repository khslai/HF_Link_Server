//=====================================
//
//�V�[���}�l�[�W���w�b�_[SceneManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "../../main.h"
#include <unordered_map>

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class BaseScene;
class SceneManager
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	SceneManager();
	~SceneManager();

	//�V�[���؂�ւ�����
	static void ChangeScene(const int sceneID);

	//�V�[���ǉ�����
	void Add(const int sceneID, BaseScene* scene);

	//�X�V�����A�`�揈���A�I������
	void Update();
	void Draw();
	void Uninit();

	//�V�[���m�F����
	bool ExistsScene(int sceneID);

	//�N���A����
	void Clear();

private:
	//�V�[���R���e�i
	std::unordered_map<int, BaseScene*> sceneContainer;

	//���݂̃V�[���A��O�̃V�[��
	BaseScene *current, *prev;

	//�V�[���؂�ւ��i���������j
	void _ChengeScene(const int sceneID);

	//static�C���X�^���X
	static SceneManager* mInstance;
};

#endif