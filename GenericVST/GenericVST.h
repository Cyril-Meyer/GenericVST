#pragma once

#include "IPlug_include_in_plug_hdr.h"

const int kNumPresets = 1;

enum EParams
{
  used_parameters = 0,
  param01,
  param02,
  param03,
  param04,
  param05,
  param06,
  param07,
  param08,
  param09,
  param10,
  kNumParams
};

using namespace iplug;
using namespace igraphics;

typedef void(__stdcall* GenericVSTProcessBlockFunction)(double** inputs, double** outputs, int nFrames, int nChans, double* params, int nParams);

class PLUG_CLASS_NAME final : public Plugin
{
public:
    PLUG_CLASS_NAME(const InstanceInfo& info);

#if IPLUG_DSP // http://bit.ly/2S64BDd
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void OnReset() override;
#endif

private:
    std::string pluginPath;
    HINSTANCE GenericVSTModuleHandle;
    GenericVSTProcessBlockFunction GenericVSTProcessBlock = nullptr;
};
