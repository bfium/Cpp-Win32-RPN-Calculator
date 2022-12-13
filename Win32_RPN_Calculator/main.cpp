#pragma comment(linker,"\"/manifestdependency:type='win32' \
	name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
	processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include"MainWindow.h"
#include"Command.h"
#include"Observers.h"
#include"Stack.h"
#include"CommandRepository.h"
#include"Exception.h"
using namespace model;
using namespace control;
using namespace utility;
using namespace view;

using namespace std;

void registerCommand(UserInterface& ui, const string& label, CommandPtr c)
{
	try
	{
		CommandRepository::getInstance().registerCommand(label, std::move(c));
	}
	catch (Exception& e)
	{
		ui.displayMessage(e.what());
	}

	return;
}

void RegisterCoreCommands(UserInterface& ui)
{
	registerCommand(ui, "+", MakeCommandPtr<AddCommand>());
	registerCommand(ui, "cos", MakeCommandPtr<CosineCommand>());
	registerCommand(ui, "-", MakeCommandPtr<SubstractCommand>());

	return;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPInstance, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow win;

	RegisterCoreCommands(win);

	CommandDispatcher ce{ win };

	win.subscribe(view::UserInterface::CommandEntered, make_unique<CommandIssuedObserver>(ce));

	Stack::getInstance().subscribe(Stack::StackChanged, make_unique<StackUpdatedObserver>(win));


	if (FAILED(win.Create(hInstance)))
	{
		return 0;
	}

	win.Show(nCmdShow);

	MSG message = {};
	while (GetMessage(&message, NULL, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return 0;
}
