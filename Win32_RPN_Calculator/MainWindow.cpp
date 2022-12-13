#include "MainWindow.h"
#include"CommandButton.h"
#include"Stack.h"
namespace view
{
	gid_map mainGuiId{};

	LRESULT MainWindow::OnReceiveMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_NCDESTROY:
			SetWindowLongPtr(m_hwnd, GWLP_USERDATA, 0);
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
		case WM_CREATE:
		{
			mainGuiId[MAIN_WINDOW] = m_hwnd;

			Rect rc{ 5,120,250,245 };

			model = new GuiModel{ m_hwnd };
			inptWin = new InputWidget( m_hwnd, INPUT_WIDGET,rc);
			display = new Display(*model,m_hwnd, DISPLAY);

		}
			return 0;
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{

			case IDM_EXIT:
				PostQuitMessage(0);
				break;
			default:
				break;
			}
		}
			break;
		case CALCM_SHIFT_PRESSED:
		{
			printf("Shift_button press!");
			model->onShift();
		}break;
		case CALCM_CHARACTER_ENTERED:
		{
			printf("character button press!");
			char v = (char)wParam;
			model->onCharactedEntered(v);
		}break;
		case CALCM_COMMAND_ENTERED:
		{
			printf("command button press!");
			const TCHAR* v = (TCHAR*)wParam;
			std::wstring wV = std::wstring(v);
			std::string sCmd = std::string(wV.begin(), wV.end());
			notify(UserInterface::CommandEntered, std::make_shared<UIEventData>(sCmd));
			printf("command transmited to the Dispatcher!");

		}break;
		case CALCM_ENTER_PRESSED:
		{
			printf("Enter button press!");
			model->onEnter();
		}break;
		case CALCM_PROCEDURE_PRESSED:
		{
			printf("Enter button press!");
			//model->on
		}break;
		case CALCM_PLUS_MINUS_PRESSED:
		{
			printf("+/- button press!");
			model->onPlusMinus();
		}break;
		case CALCM_BACKSPACE_ENTERED:
		{
			printf("BKSP button press!");
			model->onBackspace();
		}break;
		case CALCM_MODEL_CHANGED:
		{
			printf("send by the Gui model...!");
			display->onModelChanged();
		}break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
			OnPaint();
			return 0;
		default:
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
		}
		return TRUE;
	}

	void MainWindow::OnCreate()
	{
	}

	void MainWindow::OnPaint()
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(m_hwnd, &ps);

	}
	void MainWindow::displayMessage(const std::string& m)
	{
		display->showMessage(m);
	}
	void MainWindow::stackChanged()
	{
		int nLinesStack = 6;
		auto v = model::Stack::getInstance().getElements(nLinesStack);
		model->stackChanged(v);
	}


}
