#pragma once

#ifndef BASE_WINDOW_H
#define BASE_WINDOW_H
#include<Windows.h>

namespace view
{
	class BaseWindow
	{
	public:

		BaseWindow();
		virtual ~BaseWindow() {}

		static LRESULT CALLBACK	WindowProc(HWND, UINT, WPARAM, LPARAM);

		HRESULT Create(HINSTANCE hInstance);
		HRESULT Show(int nCmdShow);


	protected:

		virtual HRESULT Register();
		virtual LRESULT OnReceiveMessage(UINT msg, WPARAM wparam, LPARAM lparam) = 0;
		virtual LPCTSTR ClassName() const = 0;
		virtual LPCTSTR MenuName() const { return NULL; }
		virtual LPCTSTR WindowName() const = 0;

		virtual void OnPaint() = 0;


		HWND		m_hwnd;
		HINSTANCE	m_hInstance;

	};
}
#endif // !BASE_WINDOW_H


