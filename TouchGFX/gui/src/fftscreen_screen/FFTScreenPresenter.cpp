#include <gui/fftscreen_screen/FFTScreenView.hpp>
#include <gui/fftscreen_screen/FFTScreenPresenter.hpp>

FFTScreenPresenter::FFTScreenPresenter(FFTScreenView& v)
    : view(v)
{

}

void FFTScreenPresenter::requestFFTUpdate(volatile uint16_t* ptr, int len)
{
	view.updateFFT(ptr, len);
}

void FFTScreenPresenter::activate()
{

}

void FFTScreenPresenter::deactivate()
{

}
