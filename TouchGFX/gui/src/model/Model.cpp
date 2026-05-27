#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/common/FrontendApplication.hpp>

#include "main.h"

Model::Model() : modelListener(0)
{

}

void Model::HandleButtonPress()
{
	if (IsUserButtonPressed)
	{
		IsUserButtonPressed = 0b0;

		if (!IsFFTMode)
		{
			IsFFTMode = 0b1;
			static_cast<FrontendApplication*>
				(Application::getInstance())->gotoFFTScreenScreenNoTransition();
		}
		else
		{
			IsFFTMode = 0b0;
			static_cast<FrontendApplication*>
				(Application::getInstance())->gotoScopeScreenScreenNoTransition();
		}
	}
}

void Model::HandleProcess()
{
	if (!IsFFTMode)
	{
		if (IsADCHalfReady)
		{
			IsADCHalfReady = 0b0;
			modelListener->requestPlotUpdate(&ADC_BUFFER[0], ADC_BUFFER_SIZE / 2);
		}
		if (IsADCFullReady)
		{
			IsADCFullReady = 0b0;
			modelListener->requestPlotUpdate(&ADC_BUFFER[ADC_BUFFER_SIZE / 2], ADC_BUFFER_SIZE / 2);

		}
	}
	else
	{
		if (IsFFTReady)
		{
			IsFFTReady = 0b0;
			modelListener->requestFFTUpdate(&FFT_BUFFER[0], FFT_BUFFER_SIZE);
		}
	}
}

void Model::tick()
{
#ifndef SIMULATOR
	HandleButtonPress();
	HandleProcess();
#endif
}
