//=====================================
//
// �v���C�X�A�N�^�[[PlaceActor.h]
// �@�\�F�t�B�[���h��ɐݒu�����3D�I�u�W�F�N�g�p�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _PLACEACTOR_H_
#define _PLACEACTOR_H_

#include "../../Framework/Core/GameObject.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Renderer3D/MeshContainer.h"
#include "PlaceConfig.h"

//**************************************
// �񋓎q�ݒ�
//**************************************



//**************************************
// �N���X��`
//**************************************
class PlaceActor : public GameObject
{
public:
	PlaceActor(const D3DXVECTOR3& pos);
	virtual ~PlaceActor();

	virtual void Update();
	virtual void Draw();

	// �C���^�[�t�F�[�X
	void Rotate(float y);								// Y����]
	void SetPosition(const D3DXVECTOR3&pos);			// ���W�Z�b�g
	void SetColor(const D3DXCOLOR& color);				// ���b�V���̐F�ύX
	void ResetTransform();								// ���W�A��]�A�傫�������Z�b�g����

protected:
	MeshContainer* mesh;								// ���b�V���R���e�i
	Field::Model::PlaceType type;						// �A�N�^�[�̎��

private:
	static const D3DXVECTOR3 Scale;

#if _DEBUG
	void Debug();
#endif
};

#endif
