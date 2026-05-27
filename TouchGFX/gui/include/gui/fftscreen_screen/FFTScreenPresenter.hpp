#ifndef FFTSCREENPRESENTER_HPP
#define FFTSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class FFTScreenView;

class FFTScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    FFTScreenPresenter(FFTScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual void requestFFTUpdate(volatile uint16_t* ptr, int len) override;

    virtual ~FFTScreenPresenter() {}

private:
    FFTScreenPresenter();

    FFTScreenView& view;
};

#endif // FFTSCREENPRESENTER_HPP
