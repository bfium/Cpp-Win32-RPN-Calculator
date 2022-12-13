#include "Display.h"
#include<sstream>
#include<string>

using std::ostringstream;

namespace view
{
	HRESULT Display::Create(HWND parent, int nID, int nLinesStack, int minCharWide)
	{
		if (hwndDisplay != NULL) return E_FAIL;
		if (parent == NULL) return E_INVALIDARG;

		HWND hwnd = CreateWindowEx(
			0,
			TEXT("STATIC"),
			L"6:\n5:\n4:\n3:\n2:\n1:\n",
			WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
			5, 5,
			250, 110,
			parent,
			(HMENU)(INT_PTR)nID,
			GetModuleHandle(NULL),
			NULL
		);
		if (hwnd == 0)
			return __HRESULT_FROM_WIN32(GetLastError());

		hwndDisplay= hwnd;
		return S_OK;

	}
	void Display::showMessage(const std::string& m)
	{
		// set statusbar message...
	}
	void Display::onModelChanged()
	{
		const GuiModel::State& state = model.getState();
		if (state.filter == GuiModel::Filter::SHIFTED)
		{
			printf("GUI in Shift mode");
			//shiftIndicator_->show();
		}
		else
		{
			printf("GUI in UnShift mode");
			//shiftIndicator_->hide();
		}

		ostringstream oss;
		auto hasInput = state.currentInput.size() != 0;
		auto start = nLinesStack - (hasInput ? 1 : 0);

		for (int i = start - 1; i > -1; --i)
		{
			bool valueExists = i < static_cast<int>(state.currentStack.size());
			oss << createLine(
				i, 
				(valueExists ? state.currentStack[i] : 0 /*dummy value*/), 
				state.currentStack.size()) 
				<< (i != 0 ? "\n" : "");
		}

		if (hasInput)
		{
			oss << "\n"
				<< state.currentInput;
		}
		string vb = oss.str();
		std::wstring wstr = std::wstring(vb.begin(), vb.end());
		const wchar_t* v = wstr.c_str();

		SetWindowText(hwndDisplay,v);

	}
	void Display::onSize()
	{
	}
	string Display::createLine(int lineNumber, double sv, int stackSize)
	{
		string value{ "" };
		if (lineNumber < stackSize)
		{
			ostringstream t;
			t.precision(12);
			t << sv;
			value = t.str();
		}

		ostringstream oss;
		oss << lineNumber + 1 << ":";
		int lineLabelSize{ static_cast<int>(oss.str().size()) };
		for (int i = 0; i < nCharWide - static_cast<int>(value.length()) - lineLabelSize; ++i)
		{
			oss << ' ';
		}
		oss << value;
		return oss.str();
	}

}