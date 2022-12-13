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
#ifndef TOKENIZER_H
#define TOKENIZER_H
#include<string>
#include<vector>
namespace utility
{

	class Tokenizer
	{
	public:
		using Token = std::string;
		using Tokens = std::vector<Token>;
		using const_iterator = Tokens::const_iterator;

		explicit Tokenizer(const std::string&);
		explicit Tokenizer(std::istream&);
		~Tokenizer();

		size_t nTokens() const { return tokens_.size(); }


		// in order to use this class in a range for loop
		const_iterator begin() const { return tokens_.begin(); }
		const_iterator end() const { return tokens_.end(); }

		const Token& operator[](size_t i) const { return tokens_[i]; }

	private:
		void tokenize(std::istream&);

		Tokenizer() = delete;
		Tokenizer(const Tokenizer&) = delete;
		Tokenizer(Tokenizer&&) = delete;
		Tokenizer& operator=(const Tokenizer&) = delete;
		Tokenizer& operator=(Tokenizer&&) = delete;

		Tokens tokens_;

	};
}
#endif // !TOKENIZER_H

