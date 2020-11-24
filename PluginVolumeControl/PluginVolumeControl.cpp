#include "pch.h"
#include "PluginVolumeControl.h"

void __stdcall GenericVSTProcessBlock(double** inputs, double** outputs, int nFrames, int nChans, double* params, int nParams)
{
    if (nParams == 1)
    {
        const double gain = params[0] / 100.0;

        for (int s = 0; s < nFrames; s++) {
            for (int c = 0; c < nChans; c++) {
                outputs[c][s] = inputs[c][s] * gain;
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

