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

#include "Publisher.h"
#include"Observer.h"
#include"EventData.h"

#include"Exception.h"
#include<sstream>
namespace utility
{
	class Publisher::PublisherImpl
	{
	public:
		PublisherImpl() = default;
		~PublisherImpl() = default;

		void subscribe(const string& eventName, unique_ptr<Observer> observer);
		void unsubscribe(const string& eventName, const string& observerName);
		void notify(const string& eventName, shared_ptr<EventData>)const;

		void registerEvent(const string& eventName);

	private:
		using ObserversList = std::unordered_map<string, unique_ptr<Observer>>;
		using Observers = std::unordered_map<string, ObserversList > ;

		Observers m_observers;
	};

	Publisher::Publisher()
	{
		impl = std::make_unique<PublisherImpl>();
	}
	void Publisher::subscribe(const string& eventName, unique_ptr<Observer> observer)
	{
		impl->subscribe(eventName, std::move(observer));
	}
	void Publisher::unsubscribe(const string& eventName, const string& observerName)
	{
		return impl->unsubscribe(eventName, observerName);
	}
	Publisher::~Publisher()
	{
		// std::unique_ptr requires a definition of the destructor instead
// of using the default because the destructor must appear in a scope
// in which the complete definition of the template argument for
// std::unique_ptr is known

	}
	void Publisher::notify(const string& eventName, shared_ptr<EventData>data) const
	{
		impl->notify(eventName, data);
	}
	void Publisher::registerEvent(const string& eventName)
	{
		impl->registerEvent(eventName);
	}

	void Publisher::PublisherImpl::subscribe(const string& eventName, std::unique_ptr<Observer> observer)
	{
		auto ptr = m_observers.find(eventName);
		if (ptr == std::end(m_observers))
		{
			std::ostringstream oss;
			oss << "Event with name '" << eventName << "' not supported";
			throw Exception(oss.str());

		}
		else
		{
			auto iter = m_observers[eventName].insert(std::make_pair(observer->getName(), std::move(observer)));
			if (!iter.second)
			{
				std::ostringstream oss;
				oss << "Observer '" << observer->getName() << "' is already registered";
				throw Exception(oss.str());

			}

		}
	}

	void Publisher::PublisherImpl::unsubscribe(const string& eventName, const string& observerName)
	{
		auto count = m_observers.count(eventName);
		if (count)
		{
			auto found = m_observers[eventName].erase(observerName);
			if (!found)
			{
				std::ostringstream oss;
				oss << "Observer '" << observerName << "' not found registered";
				throw Exception(oss.str());

			}
		}
		else
		{
			std::ostringstream oss;
			oss << "Event with name '" << eventName << "' not supported";
			throw Exception(oss.str());

		}
	}

	void Publisher::PublisherImpl::notify(const string& eventName, shared_ptr<EventData> event_)const
	{
		auto ptr = m_observers.find(eventName);
		if (ptr != std::end(m_observers))
		{
			const auto& obsList = ptr->second;

			for (const auto& obs : obsList)
				obs.second->notify(event_);

		}
		else
		{
			std::ostringstream oss;
			oss << "Event with name '" << eventName << "' not supported";
			throw Exception(oss.str());

		}

	}

	void Publisher::PublisherImpl::registerEvent(const string& eventName)
	{
		auto i = m_observers.find(eventName);
		if (i != m_observers.end())
			throw Exception{ "Event already registered" };

		m_observers[eventName] = ObserversList{};

	}
}
