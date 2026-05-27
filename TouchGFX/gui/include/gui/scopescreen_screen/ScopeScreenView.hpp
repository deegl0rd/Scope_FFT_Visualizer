#ifndef SCOPESCREENVIEW_HPP
#define SCOPESCREENVIEW_HPP

#include <gui_generated/scopescreen_screen/ScopeScreenViewBase.hpp>
#include <gui/scopescreen_screen/ScopeScreenPresenter.hpp>

class ScopeScreenView : public ScopeScreenViewBase
{
public:
    ScopeScreenView();
    virtual ~ScopeScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void updatePlot(volatile uint16_t* ptr, int len);
    virtual void pointsButton_clicked() override;
protected:
};

#endif // SCOPESCREENVIEW_HPP
