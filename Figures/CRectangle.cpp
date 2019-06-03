#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

bool CRectangle::IsInside(Point P)
{
	int x1 = min(Corner1.x, Corner2.x);
	int x2 = max(Corner1.x, Corner2.x);
	int y1 = min(Corner1.y, Corner2.y);
	int y2 = max(Corner1.y, Corner2.y);

	if (P.x >= x1 && P.x <= x2 && P.y >= y1 && P.y <= y2) {
		SetSelected(!Selected);
		return true;
	}
	return false;
}