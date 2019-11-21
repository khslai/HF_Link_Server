//=============================================================================
//
// ”wŒiƒNƒ‰ƒX [Background.h]
// Author : HAL“Œ‹ž GP12B332 41 —ŠŠM‹»
//
//=============================================================================
#ifndef _Background_H_
#define _Background_H_

#include <string>
#include <vector>

using namespace std;

class PolygonDrawer;

//*****************************************************************************
// ƒNƒ‰ƒX’è‹`
//*****************************************************************************
class Background
{
private:
	int CountFrame;

	PolygonDrawer *BG;
	PolygonDrawer *LeftWall;
	PolygonDrawer *RightWall;
	PolygonDrawer *Ground;


public:
	Background();
	~Background();
	void Update(void);
	void Draw(void);
};

#endif
