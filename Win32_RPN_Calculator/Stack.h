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

#ifndef STACK_H
#define STACK_H
#include<memory>
#include<string>
#include<vector>

#include"Publisher.h"
#include"EventData.h"

namespace model
{
	enum class ErrorType
	{
		EMPTY,
		TOO_FEW_ARGUMENT
	};
	class StackEventData : public utility::EventData
	{
	public:
		explicit StackEventData(ErrorType e): er{e}{}
		static const char* getMessage(ErrorType e);
		const char* getMessage()const;

		ErrorType getErrorType()const { return er; }
	private:
		ErrorType er;
	};

	class Stack : private utility::Publisher
	{
	public:
		static Stack& getInstance();
		void push(double, bool notify = true);
		double pop(bool notify = true);
		double top()const;
		void swap();

		// returns first min(n, stackSize) elements of the stack with the top of stack at position 0
		std::vector<double> getElements(size_t n) const;
		void getElements(size_t n, std::vector<double>&) const;

		using Publisher::subscribe;
		using Publisher::unsubscribe;

		// these are just needed for testing
		size_t size() const;
		void clear() const;

		static const std::string StackChanged;
		static const std::string StackError;


	private:

		Stack();
		~Stack();
		Stack(const Stack&) = delete;
		Stack(Stack&&) = delete;
		Stack& operator=(const Stack&) = delete;
		Stack& operator=(const Stack&&) = delete;

		class StackImpl;
		std::unique_ptr<StackImpl> impl;
	};

}
#endif // !STACK_H


