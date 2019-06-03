#pragma once

#include "CFigure.h"

class CCircle : public CFigure
{
private:
	Point Center;
	int Radius;
public:
	CCircle(Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool IsInside(Point P);
};

