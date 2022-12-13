#pragma once

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include"BaseWindow.h"
#include"Resource.h"
#include"InputWidget.h"
#include"Display.h"
#include"GuiModel.h"
#include"CalculatorMessage.h"
#include"UserInterface.h"
#include<map>

using std::map;


#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#define MAX_BYTE 256
typedef map<size_t, HWND> gid_map;

namespace view
{
	enum MainWinGUIId
	{
		MAIN_WINDOW = 500,
		INPUT_WIDGET,
		DISPLAY,
		GUI_MODEL
	};
	class MainWindow : public BaseWindow,public UserInterface
	{
	public:

	private:
		LRESULT OnReceiveMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
		LPCTSTR  ClassName() const override { return L"Main Window Class"; }
		LPCTSTR WindowName() const override { return L"Calculator"; }
		LPCTSTR MenuName() const override{ return MAKEINTRESOURCE(IDC_APP_MENU); }
		
		void displayMessage(const std::string& m) override;
		void stackChanged() override;

		void OnCreate();
		void OnPaint() override;
	private:
		InputWidget* inptWin;
		GuiModel* model;
		Display* display;
		static map<size_t, HWND>gid;
	};
}
#endif // !MAIN_WINDOW_H


