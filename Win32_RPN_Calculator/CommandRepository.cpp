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

#include "CommandRepository.h"
#include "Command.h"
#include <unordered_map>
#include "Exception.h"
#include <sstream>

using std::string;
using std::unordered_map;
using std::set;

namespace control {

	class CommandRepository::CommandRepositoryImpl
	{
	public:
		CommandRepositoryImpl();
		void registerCommand(const string& name, CommandPtr c);
		CommandPtr deregisterCommand(const string& name);

		size_t count() const { return m_repository.size(); }
		CommandPtr getCommandByName(const string& name) const;

		bool hasKey(const string& s) const;
		set<string> getAllCommandNames() const;

		void printHelp(const std::string& command, std::ostream& os);

		void clearAllCommands();

	private:
		using Repository = unordered_map<string, CommandPtr>;
		Repository m_repository;
	};

	CommandRepository::CommandRepositoryImpl::CommandRepositoryImpl()
	{
	}

	bool CommandRepository::CommandRepositoryImpl::hasKey(const string& s) const
	{
		return m_repository.find(s) != m_repository.end();
	}

	set<string> CommandRepository::CommandRepositoryImpl::getAllCommandNames() const
	{
		set<string> tmp;

		for (auto i = m_repository.begin(); i != m_repository.end(); ++i)
			tmp.insert(i->first);

		return tmp;
	}

	void CommandRepository::CommandRepositoryImpl::printHelp(const std::string& command, std::ostream& os)
	{
		auto it = m_repository.find(command);
		if (it != m_repository.end())
			os << command << ": " << it->second->getHelpMessage();
		else
			os << command << ": no help entry found";

		return;
	}

	void CommandRepository::CommandRepositoryImpl::clearAllCommands()
	{
		m_repository.clear();
		return;
	}

	void CommandRepository::CommandRepositoryImpl::registerCommand(const string& name, CommandPtr c)
	{
		if (hasKey(name))
		{
			std::ostringstream oss;
			oss << "Command " << name << " already registered";
			throw utility::Exception{ oss.str() };
		}
		else
			m_repository.emplace(name, std::move(c));

		return;
	}

	CommandPtr CommandRepository::CommandRepositoryImpl::deregisterCommand(const string& name)
	{
		if (hasKey(name))
		{
			auto i = m_repository.find(name);
			auto tmp = MakeCommandPtr(i->second.release());
			m_repository.erase(i);
			return tmp;
		}
		else return MakeCommandPtr(nullptr);
	}

	CommandPtr CommandRepository::CommandRepositoryImpl::getCommandByName(const string &name) const
	{
		if (hasKey(name))
		{
			const auto& command = m_repository.find(name)->second;
			return MakeCommandPtr(command->clone());
		}
		else return MakeCommandPtr(nullptr);
	}

	CommandRepository::CommandRepository()
		: pimpl_{ new CommandRepositoryImpl }
	{
	}

	CommandRepository::~CommandRepository()
	{ }

	CommandRepository& CommandRepository::getInstance()
	{
		static CommandRepository instance;
		return instance;
	}

	void CommandRepository::registerCommand(const string& name, CommandPtr c)
	{
		pimpl_->registerCommand(name, std::move(c));

		return;
	}
	CommandPtr CommandRepository::deregisterCommand(const string& name)
	{
		return pimpl_->deregisterCommand(name);
	}

	size_t CommandRepository::count() const
	{
		return pimpl_->count();
	}

	CommandPtr CommandRepository::getCommandByName(const string& name) const
	{
		return pimpl_->getCommandByName(name);
	}

	bool CommandRepository::hasKey(const string& s) const
	{
		return pimpl_->hasKey(s);
	}

	set<string> CommandRepository::getAllCommandNames() const
	{
		return pimpl_->getAllCommandNames();
	}

	void CommandRepository::printHelp(const std::string& command, std::ostream& os) const
	{
		pimpl_->printHelp(command, os);
		return;
	}

	void CommandRepository::clearAllCommands()
	{
		pimpl_->clearAllCommands();
		return;
	}

}

