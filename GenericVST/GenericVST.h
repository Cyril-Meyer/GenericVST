#pragma once

#include "IPlug_include_in_plug_hdr.h"

const int kNumPresets = 1;

enum EParams
{
  kGain = 0,
  kNumParams
};

using namespace iplug;
using namespace igraphics;

#include <iostream>
typedef void(__stdcall* GenericVSTProcessBlockFunction)(double** inputs, double** outputs, int nFrames, int nChans, double* params, int nParams);

class GenericVST final : public Plugin
{
public:
  GenericVST(const InstanceInfo& info);

#if IPLUG_DSP // http://bit.ly/2S64BDd
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void OnReset() override;
#endif

private:
    HINSTANCE GenericVSTModuleHandle;
    GenericVSTProcessBlockFunction GenericVSTProcessBlock;
};
