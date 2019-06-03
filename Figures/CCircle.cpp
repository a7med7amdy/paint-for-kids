#include "CCircle.h"



CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Center = P1;
	Radius = sqrt(pow(P2.x - P1.x, 2) + pow(P2.y - P1.y, 2));
}

void CCircle::Draw(Output* pOut) const
{
	pOut->DrawCircle(Center, Radius, FigGfxInfo, Selected);
}

bool CCircle::IsInside(Point P)
{
	if (pow(P.x - Center.x, 2) + pow(P.y - Center.y, 2) <= pow(Radius, 2)) {
		SetSelected(!Selected);
		return true;
	}
	return false;
}