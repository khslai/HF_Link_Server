//=====================================
//
//�g�����X�t�H�[���I�u�W�F�N�g�w�b�_[TransformObject.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TRANSFORMOBJECT_H_
#define _TRANSFORMOBJECT_H_

#include "../../main.h"
#include "MeshContainer.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class TransformObject : public GameObject
{
public:
	TransformObject();
	~TransformObject();

	void Draw();

private:
	MeshContainer *mesh;
};

#endif