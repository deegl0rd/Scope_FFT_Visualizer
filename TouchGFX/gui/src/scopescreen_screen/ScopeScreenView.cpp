#include <gui/scopescreen_screen/ScopeScreenView.hpp>

#include <texts/TextKeysAndLanguages.hpp>

ScopeScreenView::ScopeScreenView()
{

}

unsigned scale = 0;
void ScopeScreenView::pointsButton_clicked()
{
	scope.clear();

	scale = (scale + 1) % 3;

	switch(scale)
	{
	case 0:
		scope.setGraphRangeY(-1.0f, 1.0f);
		pointsButton.setLabelText(touchgfx::TypedText(T_SCOPE_SCALE_UNITY));
		break;
	case 1:
		scope.setGraphRangeY(-0.5f, 0.5f);
		pointsButton.setLabelText(touchgfx::TypedText(T_SCOPE_SCALE_HALF));
		break;
	case 2:
		scope.setGraphRangeY(-0.25f, 0.25f);
		pointsButton.setLabelText(touchgfx::TypedText(T_SCOPE_SCALE_QUARTER));
		break;
	}

	pointsButton.invalidate();
}

void ScopeScreenView::updatePlot(volatile uint16_t* ptr, int len)
{
	for (int i = 0; i < len; ++i)
	{
		const int correction = 40;
		volatile int16_t val = ptr[i];
		float p = (val - 2048 - correction) / 2048.0f;
		scope.addDataPoint(p);
	}

	scope.invalidate();
}

void ScopeScreenView::setupScreen()
{
    ScopeScreenViewBase::setupScreen();
}

void ScopeScreenView::tearDownScreen()
{
    ScopeScreenViewBase::tearDownScreen();
}
