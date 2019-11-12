//=====================================
//
// �C�x���g�A�N�^�[���N���X[EventActorBase.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#ifndef _EventActorBase_H_
#define _EventActorBase_H_

#include "../Framework/Core/GameObject.h"
#include "../Framework/Renderer3D/MeshContainer.h"


//**************************************
// �N���X��`
//**************************************
class EventActorBase : public GameObject
{
private:
	MeshContainer* mesh;		// ���b�V���R���e�i

public:
	EventActorBase(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag);
	~EventActorBase();

	virtual void Update();
	virtual void Draw();
};

#endif
