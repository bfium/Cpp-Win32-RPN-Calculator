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

#include"CommandDispatcher.h"
#include"Observer.h"

namespace view
{
	class CommandIssuedObserver : public utility::Observer
	{
	public:
		explicit CommandIssuedObserver(control::CommandDispatcher& ce);

	private:
		void notifyImpl(std::shared_ptr<utility::EventData>) override;

		control::CommandDispatcher& m_ce;
	};

}

namespace model
{
	class StackUpdatedObserver : public utility::Observer
	{
	public:
		explicit StackUpdatedObserver(view::UserInterface& ui);

	private:
		void notifyImpl(std::shared_ptr<utility::EventData>) override;

		view::UserInterface& m_ui;
	};

}

