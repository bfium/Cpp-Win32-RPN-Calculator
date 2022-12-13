#pragma once
/*
	Copyright (C) 2022  Barth.Feudong
	Author can be contacted here: <https://github.com/mrSchaffman/Cpp-Nimpo-Calculator>

	This file is part of the Nimpo Command Line Calculator project.

	Nimpo is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Nimpo is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef UI_EVENT_DATA_H
#define UI_EVENT_DATA_H
#include"EventData.h"
#include<string>
namespace view
{
	class UIEventData : public utility::EventData
	{
	public:
		UIEventData(const std::string& userInput): uii{userInput}{}
		const std::string& getEventData()const { return uii; }

	private:
		std::string uii;
	};
}
#endif // !UI_EVENT_DATA_H


