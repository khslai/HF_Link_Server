//=============================================================================
//
// wiNX [Background.h]
// Author : HAL GP12B332 41 M»
//
//=============================================================================
#ifndef _Background_H_
#define _Background_H_

#include <string>
#include <vector>

using namespace std;

class PolygonDrawer;

//*****************************************************************************
// NXθ`
//*****************************************************************************
class Background
{
private:
	int CountFrame;

	PolygonDrawer *BG;
	vector<PolygonDrawer*> LeftWall;
	vector<PolygonDrawer*> RightWall;
	vector<PolygonDrawer*> Ground;

public:
	Background();
	~Background();
	void Update(void);
	void Draw(void);
};

#endif
