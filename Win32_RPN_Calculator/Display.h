#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H
#include"GuiModel.h"

namespace view
{

	// the View of The View Subsystem
	class Display
	{
	
	public:
		Display(const GuiModel& g, HWND parent, int nID, int nLStack = 6, int minCharWide = 25)
			:model{g},
			hwndDisplay{ NULL },
			parent{ parent },
			hwndStatusBar{ NULL },
			hwndLabelShiftIndicator{ NULL },
			nLinesStack{ nLStack },
			nCharWide{ minCharWide },
			ID{ nID }
		{
			Create(parent, nID, nLStack, minCharWide); 
		};
		HRESULT Create(HWND parent, int nID, int nLinesStack = 6, int minCharWide = 25);
		HWND getWindow() const { return hwndDisplay; }
		void setParent(HWND p) { parent = p; }
		void showMessage(const std::string& m);

	public:
		void onModelChanged();
		void onSize();

	private:
		string createLine(int lineNumber, double value, int stackSize);

	private:
		const GuiModel& model;

		HWND hwndDisplay;
		HWND parent;
		HWND hwndStatusBar;
		HWND hwndLabelShiftIndicator;
		int nLinesStack;
		int nCharWide;
		int ID;
	};

}
#endif // !DISPLAY_H


