#include "GenericVST.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

#include "PluginVolumeControl.h"    
#include <windows.h>
/*
#pragma comment(lib, "PluginVolumeControl.lib")
*/

GenericVST::GenericVST(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachPanelBackground(COLOR_GRAY);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const IRECT b = pGraphics->GetBounds();
    pGraphics->AttachControl(new ITextControl(b.GetMidVPadded(50), "Hello iPlug 2!", IText(50)));
    pGraphics->AttachControl(new IVKnobControl(b.GetCentredInside(100).GetVShifted(-100), kGain));
  };
#endif
}

#if IPLUG_DSP
void GenericVST::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const double gain = GetParam(kGain)->Value() / 100.;
  const int nChans = NOutChansConnected();

  int nParams = 1;
  double* params = new double[nParams];
  params[0] = gain;

  GenericVSTProcessBlock(inputs, outputs, nFrames, nChans, params, nParams);

}

void GenericVST::OnReset()
{
    GenericVSTModuleHandle = LoadLibrary("..\\..\\PluginVolumeControl\\Release\\PluginVolumeControl.dll");
    GenericVSTProcessBlock = (GenericVSTProcessBlockFunction)GetProcAddress(GenericVSTModuleHandle, MAKEINTRESOURCEA(1));
}
#endif
