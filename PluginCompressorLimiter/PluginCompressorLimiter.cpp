#include "pch.h"
#include "PluginCompressorLimiter.h"

#include <cstdlib>

void __stdcall GenericVSTProcessBlock(double** inputs, double** outputs, int nFrames, int nChans, double* params, int nParams)
{
    auto absmin = [](double a, double b)
    {
        return min(abs(a), abs(b));
    };

    auto sign = [](double a)
    {
        if (a < 0)
            return -1;
        else
            return 1;
    };


    if (nParams == 2)
    {
        const double compressor = params[0] / 10.;
        const double limiter = params[1] / 100;

        for (int s = 0; s < nFrames; s++) {
            for (int c = 0; c < nChans; c++) {
                outputs[c][s] = absmin(inputs[c][s] * compressor, limiter) * sign(inputs[c][s]);
            }
        }
    }
    else
    {
        for (int s = 0; s < nFrames; s++) {
            for (int c = 0; c < nChans; c++) {
                outputs[c][s] = inputs[c][s];
            }
        }
    }
}

