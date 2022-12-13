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

#include "CommandDispatcher.h"
#include "CommandRepository.h"
#include "CommandManager.h"
#include "Command.h"
#include "Exception.h"
#include <sstream>
#include <regex>
#include <cassert>
#include <algorithm>
#include "UserInterface.h"
#include <fstream>
#include "Tokenizer.h"

using std::string;
using std::ostringstream;
using std::unique_ptr;
using std::set;
using std::istringstream;

namespace control {

class CommandDispatcher::CommandDispatcherImpl
{
public:
    explicit CommandDispatcherImpl(view::UserInterface& ui);

    void executeCommand(const string& command);


private:
    bool isNum(const string&, double& d);
    void handleCommand(CommandPtr command);
    void printHelp() const;

    CommandManager manager_;
	view::UserInterface& m_ui;
};

CommandDispatcher::CommandDispatcherImpl::CommandDispatcherImpl(view::UserInterface& ui)
: m_ui(ui)
{ }

void CommandDispatcher::CommandDispatcherImpl::executeCommand(const string& command)
{
    // entry of a number simply goes onto the the stack
    double d;
    if( isNum(command, d) )
        manager_.executeCommand(MakeCommandPtr<EnterNumber>(d));
    else if(command == "undo")
        manager_.undo();
    else if(command == "redo")
        manager_.redo();
    else if(command == "help")
        printHelp();
    else
    {
        auto c = CommandRepository::getInstance().getCommandByName(command);
        if(!c)
        {
            ostringstream oss;
            oss << "Command " << command << " is not a known command";
            m_ui.displayMessage( oss.str() );
        }
        else handleCommand( std::move(c) );
    }

    return;
}

void CommandDispatcher::CommandDispatcherImpl::handleCommand(CommandPtr c)
{
    try
    {
        manager_.executeCommand( std::move(c) );
    }
    catch(utility::Exception& e)
    {
        m_ui.displayMessage( e.what() );
    }

    return;
}

void CommandDispatcher::CommandDispatcherImpl::printHelp() const
{
    ostringstream oss;
    set<string> allCommands = CommandRepository::getInstance().getAllCommandNames();
    oss << "\n";
    oss << "undo: undo last operation\n"
        << "redo: redo last operation\n";

    for(auto i : allCommands)
    {
        CommandRepository::getInstance().printHelp(i, oss);
        oss << "\n";
    }

    m_ui.displayMessage( oss.str() );

}

bool CommandDispatcher::CommandDispatcherImpl::isNum(const string& s, double& d)
{
     if(s == "+" || s == "-") return false;

     std::regex dpRegex("((\\+|-)?[[:digit:]]*)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
     bool isNumber{ std::regex_match(s, dpRegex) };

     if(isNumber)
     {
         d = std::stod(s);
     }

     return isNumber;
}

void CommandDispatcher::commandEntered(const std::string& command)
{
    pimpl_->executeCommand(command);

    return;
}

CommandDispatcher::CommandDispatcher(view::UserInterface& ui)
{
    pimpl_ = std::make_unique<CommandDispatcherImpl>(ui);
}

CommandDispatcher::~CommandDispatcher()
{ }

}
