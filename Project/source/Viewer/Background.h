//=============================================================================
//
// �w�i�N���X [Background.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _Background_H_
#define _Background_H_

#include <string>
#include <vector>

using namespace std;

class BoardPolygon;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Background
{
private:
	BoardPolygon *BG;
	BoardPolygon *Wall;

public:
	Background();
	~Background();
	void Update(void);
	void Draw(void);
};

#endif
