#include <gui/scopescreen_screen/ScopeScreenView.hpp>
#include <gui/scopescreen_screen/ScopeScreenPresenter.hpp>

ScopeScreenPresenter::ScopeScreenPresenter(ScopeScreenView& v)
    : view(v)
{

}

void ScopeScreenPresenter::requestPlotUpdate(volatile uint16_t* ptr, int len)
{
	view.updatePlot(ptr, len);
}

void ScopeScreenPresenter::activate()
{

}

void ScopeScreenPresenter::deactivate()
{

}
