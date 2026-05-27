#ifndef FFTSCREENVIEW_HPP
#define FFTSCREENVIEW_HPP

#include <gui_generated/fftscreen_screen/FFTScreenViewBase.hpp>
#include <gui/fftscreen_screen/FFTScreenPresenter.hpp>

class FFTScreenView : public FFTScreenViewBase
{
	void ProcessFFT(volatile uint16_t* ptr, int len);
public:
    FFTScreenView();
    virtual ~FFTScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void updateFFT(volatile uint16_t* ptr, int len);
protected:
};

#endif // FFTSCREENVIEW_HPP
