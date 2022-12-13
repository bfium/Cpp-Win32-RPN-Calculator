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

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include"Publisher.h"
#include"UIEventData.h"			// so the the child will gain access directly
namespace view
{
	class UserInterface : protected utility::Publisher
	{
	public:
		// the Name to be used by observer to register to event comming from this class.
		UserInterface() { registerEvent(CommandEntered); } // Register the Command Name
		virtual~UserInterface() = default;

		static const std::string CommandEntered;
	public:
		virtual void stackChanged() = 0;
		virtual void displayMessage(const std::string&) = 0; // postMessage() in the Docu

		using Publisher::subscribe;
		using Publisher::unsubscribe;
	private:

	};
}
#endif // !USER_INTERFACE_H
