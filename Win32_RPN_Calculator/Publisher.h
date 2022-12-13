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

#ifndef PUBLISHER_H
#define PUBLISHER_H
#include<string>
#include<memory>
#include<unordered_map>

using std::string;
using std::unique_ptr;
using std::shared_ptr;
namespace utility
{
	/*
		The Publisher that keep track of observers identify by name 
		andd notify them when a particular event is raised.
	*/
	class Observer;
	class EventData;

	class Publisher
	{
	public:
		Publisher();
		void subscribe(const string& eventName, unique_ptr<Observer> observer);
		void unsubscribe(const string& eventName, const string& observerName);

	protected:
		~Publisher();
		
		void notify(const string& eventName, shared_ptr<EventData>)const;

		void registerEvent(const string& eventName);
	private:
		class PublisherImpl;
		unique_ptr<PublisherImpl> impl;

	};
}
#endif // !PUBLISHER_H

