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

#include "Observers.h"
#include"Exception.h"
#include<memory>

namespace view
{
	CommandIssuedObserver::CommandIssuedObserver(control::CommandDispatcher& ce)
		: Observer("CommandEntered")
		, m_ce(ce)
	{ }

	void CommandIssuedObserver::notifyImpl(std::shared_ptr<utility::EventData> eventData)
	{
		auto data = std::dynamic_pointer_cast<view::UIEventData>(eventData);
		if (!data)
		{
			throw utility::Exception("Could not convert CommandData to a command");
		}
		else
		{
			m_ce.commandEntered(data->getEventData());
		}

		return;
	}


}

namespace model
{
	StackUpdatedObserver::StackUpdatedObserver(view::UserInterface& ui)
		: Observer("StackUpdated")
		, m_ui(ui)
	{ }

	void StackUpdatedObserver::notifyImpl(std::shared_ptr<utility::EventData>)
	{
		m_ui.stackChanged();

		return;
	}

}