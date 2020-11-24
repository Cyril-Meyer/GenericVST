#include <iostream>
#include <windows.h>

typedef void (__stdcall* GenericVSTProcessBlockFunction)(double** inputs, double** outputs, int nFrames, int nChans, double* params, int nParams);

int main()
{
    // Setup parameters
    int nFrames = 256;
    int nChans = 2;
    int nParams = 1;
    double gain = 10. / 100.;

    double** input = new double* [nFrames];
    for (int i = 0; i < nFrames; ++i)
        input[i] = new double[nFrames];

    double** output = new double* [nFrames];
    for (int i = 0; i < nFrames; ++i)
        output[i] = new double[nFrames];

    double* params = new double[nParams];
    params[0] = gain;

    for (int c = 0; c < nChans; c++) {
        for (int s = 0; s < nFrames; s++) {
            if (c == 0)
                input[c][s] = 100;
            else
                input[c][s] = s%200;
        }
    }

    // Load DLL
    HINSTANCE handleModule = LoadLibrary(L"..\\PluginVolumeControl\\Release\\PluginVolumeControl.dll");

    if (!handleModule) {
        std::cout << "could not load the dynamic library" << std::endl;
        return EXIT_FAILURE;
    }

    // Get function
    GenericVSTProcessBlockFunction func = (GenericVSTProcessBlockFunction)GetProcAddress(handleModule, MAKEINTRESOURCEA(1));

    if (!func) {
        std::cout << "could not locate the function" << std::endl;
        return EXIT_FAILURE;
    }

    // Process input
    func(input, output, nFrames, nChans, params, nParams);

    // Print input and output
    for (int c = 0; c < nChans; c++) {
        for (int s = 0; s < nFrames; s++) {
            std::cout << input[c][s] << " ";
        }
    }

    std::cout << std::endl;

    for (int c = 0; c < nChans; c++) {
        for (int s = 0; s < nFrames; s++) {
            std::cout << output[c][s] << " ";
        }
    }
}
