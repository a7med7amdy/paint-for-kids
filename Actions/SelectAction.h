#pragma once
#include "Action.h"
#include <vector>
#include "..\Figures\CFigure.h"

class SelectAction : public Action
{
private:
	vector <CFigure*> Selected;
	Point P;
public:
	SelectAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};