#include "Output.h"
#include <iostream>
using namespace std;



Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy = 5;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 32;
	UI.MenuItemWidth = 65;

	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames

	UI.colorSide = UI.ToolBarHeight;
	UI.numberOfColors = 14; //UI.width / UI.colorSide + 1;
	UI.colors.push_back(BLACK);
	UI.colors.push_back(WHITE);
	UI.colors.push_back(RED);
	UI.colors.push_back(GREEN);
	UI.colors.push_back(BLUE);
	/*for (int i = 0; i < UI.numberOfColors - 5; i++) {
		cout << "UI.colors.push_back(color(" << rand() % 255 << ", " << rand() % 255 << ", " << rand() % 255 << "));" << endl;
		UI.colors.push_back(color(rand() % 255, rand() % 255, rand() % 255));
	}
	UI.colors.push_back(color(214, 107, 41));
	UI.colors.push_back(color(187, 33, 3));
	UI.colors.push_back(color(16, 252, 76));
	UI.colors.push_back(color(6, 81, 237));
	UI.colors.push_back(color(81, 142, 37));
	UI.colors.push_back(color(236, 51, 92));
	UI.colors.push_back(color(205, 34, 167));
	UI.colors.push_back(color(78, 243, 2));
	UI.colors.push_back(color(47, 238, 203));
	UI.colors.push_back(color(53, 109, 147));
	UI.colors.push_back(color(5, 230, 76));
	UI.colors.push_back(color(139, 17, 115));
	UI.colors.push_back(color(145, 99, 80));
	UI.colors.push_back(color(249, 233, 168));
	UI.colors.push_back(color(121, 110, 141));
	UI.colors.push_back(color(146, 54, 114));
	UI.colors.push_back(color(234, 42, 53));
	UI.colors.push_back(color(9, 78, 49));
	UI.colors.push_back(color(176, 201, 53));
	UI.colors.push_back(color(2, 219, 150));
	UI.colors.push_back(color(236, 30, 16));
	UI.colors.push_back(color(206, 19, 195));
	UI.colors.push_back(color(196, 49, 111));
	UI.colors.push_back(color(157, 117, 157));
	UI.colors.push_back(color(79, 239, 155));
	UI.colors.push_back(color(221, 211, 47));
	UI.colors.push_back(color(147, 206, 135));
	UI.colors.push_back(color(128, 137, 84));
	UI.colors.push_back(color(91, 125, 32));
	UI.colors.push_back(color(63, 51, 6));
	UI.colors.push_back(color(53, 144, 121));
	UI.colors.push_back(color(22, 218, 15));
	UI.colors.push_back(color(212, 43, 168));
	UI.colors.push_back(color(29, 79, 118));
	UI.colors.push_back(color(199, 149, 200));
	*/
	UI.colors.push_back(BISQUE);
	UI.colors.push_back(AZURE);
	UI.colors.push_back(DIMGREY);
	UI.colors.push_back(NAVY);
	UI.colors.push_back(DODGERBLUE);
	UI.colors.push_back(MEDIUMTURQUOISE);
	UI.colors.push_back(SEAGREEN);
	UI.colors.push_back(LIMEGREEN);
	UI.colors.push_back(GOLD);
	

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	CreateDrawToolBar();
	CreateStatusBar();
	colorSelectType = NOTHING;
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::read_directory(string name, vector<string> &v) const
{
	std::string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			if (data.cFileName[0] == '.')
				continue;
			v.push_back(name + "\\" + data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
}

void Output::drawToolBar(string dir) const {
	clearToolBar();
	vector<string> fileNames;
	read_directory("images\\MenuItems\\" + dir, fileNames);
	//Draw menu item one image at a time
	int size = fileNames.size();
	for (int i = 0; i < size; i++)
		pWind->DrawImage(fileNames[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	//Draw a line under the toolbar
	pWind->SetPen(RED, 1);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void Output::clearToolBar() const {
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

void Output::drawColorPalette(ColorSelectType colorSelectType) {
	UI.colorSelectType = colorSelectType;
	clearToolBar();
	for (int i = 0; i < UI.numberOfColors; i++) {
		pWind->SetBrush(UI.colors[i]);
		pWind->DrawRectangle(i * UI.colorSide, 0, i * UI.colorSide + UI.colorSide, UI.colorSide);
	}
}

ColorSelectType Output::getColorSelectType() {
	return colorSelectType;
}

void Output::setColorSelectType(ColorSelectType colorSelectType) {
	this->colorSelectType = colorSelectType;
}

void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;
	drawToolBar("Draw_Mode");
	return;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\Menu_Circ.jpg";
	MenuItemImages[ITM_EXIT_DRAW] = "images\\MenuItems\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	drawToolBar("Play_Mode");
	return;
	///TODO: write code to create Play mode menu
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight + 1, UI.width, UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drwawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}

void Output::DrawLine(Point P1, Point P2, GfxInfo lineGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = lineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (lineGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(lineGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);
}

void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo triangleGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = triangleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (triangleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(triangleGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}

void Output::DrawCircle(Point P1, int R, GfxInfo circleGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = circleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (circleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(circleGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawCircle(P1.x, P1.y, R, style);
	if (UI.InterfaceMode == MODE_DRAW) {
		CreateDrawToolBar();
	}
	else {
		CreatePlayToolBar();
	}

}



//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

