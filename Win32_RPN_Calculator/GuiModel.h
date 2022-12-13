#pragma once
#ifndef GUI_MODEL_H
#define GUI_MODEL_H
#include<vector>
#include<string>
#include<windows.h>
#include"CalculatorMessage.h"

using std::vector;
using std::string;

namespace view
{
	// The Controller of the View Subsystem
	LRESULT CALLBACK GuiModelProc(HWND, UINT, WPARAM, LPARAM);
	class GuiModel
	{
	public:
		enum class Filter { UNSHIFTED, SHIFTED, };
		struct State
		{
			State() :currentStack{}, currentInput{""}, filter{Filter::UNSHIFTED}{};
			vector<double> currentStack;
			string currentInput;
			Filter filter;
		};

		explicit GuiModel(HWND parent);

		~GuiModel() = default;
		HWND getWindow()const { return guiModelHandle; }
		void setParent(HWND p) { parent = p; }

		void stackChanged(const vector<double>& v);

		const State& getState()const;
		bool inputEmpty()const { return m_state.currentInput.empty(); }
		void clearInput();
		void onShift();

	public:
		void onEnter();
		void onCharactedEntered(char c);
		void onBackspace();
		void onPlusMinus();
		void onCommandEntered(string primaryCmd, string secondaryCmd);
	private:
		HWND guiModelHandle;
		HWND parent;
		State m_state;
	};

}
#endif // !GUI_MODEL_H


