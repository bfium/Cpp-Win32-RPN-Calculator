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

#include "Tokenizer.h"
#include<iterator>
#include<algorithm>
#include<sstream>

using std::string;

namespace utility
{
	Tokenizer::Tokenizer(const string& s)
	{
		std::istringstream iss{ s };

		tokenize(iss);
	}

	Tokenizer::Tokenizer(std::istream& is)
	{
		tokenize(is);
	}


	Tokenizer::~Tokenizer()
	{ }

	void Tokenizer::tokenize(std::istream& is)
	{
		tokens_.assign(std::istream_iterator<string>{is}, std::istream_iterator<string>{});

		for (auto& i : tokens_)
			std::transform(i.begin(), i.end(), i.begin(), ::tolower);
	}
}
