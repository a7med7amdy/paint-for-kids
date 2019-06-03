#include "CLine.h"



CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Start = P1;
	End = P2;
}

void CLine::Draw(Output* pOut) const
{
	pOut->DrawLine(Start, End, FigGfxInfo, Selected);
}

bool CLine::IsInside(Point P)
{
	int x = End.x - Start.x;
	int y = End.y - Start.y;

	if (((x*P.y + y*P.x + y*Start.x - x*Start.y) / sqrt(pow(x, 2) + pow(y, 2))) <= 25) {
		SetSelected(!Selected);
		return true;
	}
	return false;
}