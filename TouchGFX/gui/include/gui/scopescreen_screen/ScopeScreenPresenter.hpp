#ifndef SCOPESCREENPRESENTER_HPP
#define SCOPESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScopeScreenView;

class ScopeScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScopeScreenPresenter(ScopeScreenView& v);

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

    virtual void requestPlotUpdate(volatile uint16_t* ptr, int len) override;

    virtual ~ScopeScreenPresenter() {}

private:
    ScopeScreenPresenter();

    ScopeScreenView& view;
};

#endif // SCOPESCREENPRESENTER_HPP
