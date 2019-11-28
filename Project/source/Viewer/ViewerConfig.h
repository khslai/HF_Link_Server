//=============================================================================
//
// �T�[�o�[�r���[�A�R���t�B�O�N���X [ViewerConfig.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _ViewerConfig_H_
#define _ViewerConfig_H_

namespace Viewer
{
	// X(10.264f),Y(5.773f)�̓J������NearZ��10.0f�̏ꍇ�A���傤�ǔw�i���S��ʕ\���ł���T�C�Y
	static D3DXVECTOR2 BackGroundSize = D3DXVECTOR2(10.264f * 10, 5.773f * 10);
	// Z�l��NearZ��10�{������A�T�C�Y��10�{������
	static D3DXVECTOR3 BackgroundPos = D3DXVECTOR3(0.0f, 10.0f, 100.0f);

	enum State
	{
		Ranking,
		EventLive,
		//LevelUp,
		Max,
	};
}

//*****************************************************************************
// �N���X��`
//*****************************************************************************


#endif