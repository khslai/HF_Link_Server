//=====================================
//
//�R���C�_�[�I�u�U�[�o�[�w�b�_[ColliderObserver.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _COLLIDEROBSERVER_H_
#define _COLLIDEROBSERVER_H_

#include <string>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class ColliderObserver
{
public:
	virtual void OnColliderHit(const std::string& other) = 0;
};

#endif