#pragma once
/*
	Copyright (C) 2022  Barth.Feudong
	Author can be contacted here: <https://github.com/mrSchaffman/Cpp-Calculator>

	This file is part of the Calculator project.
	using the COM, the win32 API for the GUI,
	the MVC Architecture.

	Calculator is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Calculator is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef COMMAND_BUTTON_H
#define COMMAND_BUTTON_H
#include"Control.h"
#include<assert.h>
#include<string>

using std::string;

class CommandButton//: public Control
{
public:
	CommandButton() : m_hwnd(0), m_primaryCmd{}, m_shftCmd{}{}

	HRESULT Create(HWND hParent, const TCHAR* szCaption, int nID, const Rect& rcBound);

    HRESULT Create(
		HWND hParent, 
		const TCHAR* dispPrimaryCmd, 
		const TCHAR* primaryCmd, 
		const TCHAR* dispShftCmd,
		const TCHAR* shftCmd,
		int nID, 
		const Rect& rcBound
	);
    HRESULT Create(
		HWND hParent, 
		const TCHAR* dispPrimaryCmd, 
		const TCHAR* primaryCmd, 
		int nID, 
		const Rect& rcBound
	);

    void SetWindow(HWND hwnd) { m_hwnd = hwnd; }
    HWND getWindow() const { return m_hwnd; }

    LRESULT SendMessage(UINT msg, WPARAM wParam, LPARAM lParam) const
    {
        assert(m_hwnd);
        return ::SendMessage(m_hwnd, msg, wParam, lParam);
    }

private:
    HWND m_hwnd;
	string m_primaryCmd;
	string m_shftCmd;

};

HINSTANCE	GetInstance();

#endif // !COMMAND_BUTTON_H


