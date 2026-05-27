#include <gui/fftscreen_screen/FFTScreenView.hpp>

#include "arm_math.h"
#include "main.h"

static float window[FFT_BUFFER_SIZE];
float in[FFT_BUFFER_SIZE];
float out[FFT_BUFFER_SIZE];
float magnitudes[FFT_BUFFER_SIZE / 2];
arm_rfft_fast_instance_f32 engine;

const float FFT_MIN_FREQ = 50.0f;
const float FFT_MAX_FREQ = 20000.0f;

FFTScreenView::FFTScreenView()
{
    arm_rfft_fast_init_f32(&engine, FFT_BUFFER_SIZE);

	// Hann window function, to avoid spectral leakage
    for (int i = 0; i < FFT_BUFFER_SIZE; i++)
    {
    	window[i] = 0.5f * (1.0f - cosf(2.0f * PI * i / (FFT_BUFFER_SIZE - 1)));
    }
}

void FFTScreenView::ProcessFFT(volatile uint16_t* ptr, int len)
{
	for (int i = 0; i < len; i++)
	{
		const int correction = 40;
		in[i] = (ptr[i] - 2048 - correction) / 2048.0f;
		in[i] *= window[i];
	}

    arm_rfft_fast_f32(&engine, in, out, 0);
    // Calculate standard complex magnitude for bins 1 through (N/2 - 1)
    arm_cmplx_mag_f32(out + 2, magnitudes + 1, (FFT_BUFFER_SIZE / 2) - 1);

    // Unpack DC manually
    magnitudes[0] = fabsf(out[0]);
}

void FFTScreenView::updateFFT(volatile uint16_t* ptr, int len)
{
	ProcessFFT(ptr, len);

	for (int x = 0; x < FFT_BINS; x++)
	{
		// Logarithmic bin selection
		float f0 = FFT_MIN_FREQ * powf(FFT_MAX_FREQ / FFT_MIN_FREQ, (float) x      / (float) FFT_BINS);
		float f1 = FFT_MIN_FREQ * powf(FFT_MAX_FREQ / FFT_MIN_FREQ, (float)(x + 1) / (float) FFT_BINS);
		int bin0 = (int)(f0 * FFT_BUFFER_SIZE / FFT_SAMPLE_RATE);
		int bin1 = (int)(f1 * FFT_BUFFER_SIZE / FFT_SAMPLE_RATE);

		bin0 = fmax(0, bin0);
		bin1 = fmin(FFT_BUFFER_SIZE / 2 - 1, bin1);

		// RMS based weighted sum
		float sum = 0;
		for (int k = bin0; k <= bin1; k++)
		{
			sum += magnitudes[k] * magnitudes[k];
		}
		float val = sqrtf(sum / (bin1 - bin0 + 1));

		// Scaling according to the FFT buffer's size
		volatile float mag = (2.0f * val) / FFT_BUFFER_SIZE;

		// dBFS conversion
		volatile float dB = 20.0f * log10f(mag + 1e-6f);
		dB = fmaxf(dB, -100.0f);
		dB = fminf(dB, 0.0f);

		// Add +100 due to GUI limits (100 = full scale)
		fft.addDataPoint(dB + 100.0f);
	}

	fft.invalidate();
}

void FFTScreenView::setupScreen()
{
    FFTScreenViewBase::setupScreen();
}

void FFTScreenView::tearDownScreen()
{
    FFTScreenViewBase::tearDownScreen();
}
