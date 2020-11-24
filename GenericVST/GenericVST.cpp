#include "GenericVST.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

#include <windows.h>


PLUG_CLASS_NAME::GenericVST(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  pluginPath = "PluginVolumeControl.dll";

  GetParam(used_parameters)->InitInt("Used parameters", 1, 0, 10, "params");
  GetParam(param01)->InitDouble("Param 01", 0., 0., 100.0, 0.01, "%");
  GetParam(param02)->InitDouble("Param 02", 0., 0., 100.0, 0.01, "%");
  GetParam(param03)->InitDouble("Param 03", 0., 0., 100.0, 0.01, "%");
  GetParam(param04)->InitDouble("Param 04", 0., 0., 100.0, 0.01, "%");
  GetParam(param05)->InitDouble("Param 05", 0., 0., 100.0, 0.01, "%");
  GetParam(param06)->InitDouble("Param 06", 0., 0., 100.0, 0.01, "%");
  GetParam(param07)->InitDouble("Param 07", 0., 0., 100.0, 0.01, "%");
  GetParam(param08)->InitDouble("Param 08", 0., 0., 100.0, 0.01, "%");
  GetParam(param09)->InitDouble("Param 09", 0., 0., 100.0, 0.01, "%");
  GetParam(param10)->InitDouble("Param 10", 0., 0., 100.0, 0.01, "%");
  
#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachPanelBackground(COLOR_GRAY);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const IRECT b = pGraphics->GetBounds();

    pGraphics->AttachControl(new ITextControl(b.GetGridCell(0, 5, 10, EDirection::Horizontal, 6), "GenericVST", IText(50)));

    auto buttonAction = [pGraphics, this](IControl* pCaller) {
        SplashClickActionFunc(pCaller);
        WDL_String fileName;
        WDL_String path;
        pGraphics->PromptForFile(fileName, path, EFileAction::Open, "dll");

        pluginPath = fileName.Get();
        OnReset();
    };

    pGraphics->AttachControl(new IVButtonControl(b.GetGridCell(6, 5, 10, EDirection::Horizontal, 2), buttonAction, "Load Plugin"));

    pGraphics->AttachControl(new IVKnobControl(b.GetGridCell(8, 5, 10, EDirection::Horizontal, 2), used_parameters));
    pGraphics->AttachControl(new IVKnobControl(b.GetGridCell(20, 5, 10, EDirection::Horizontal, 1), param01));
    pGraphics->AttachControl(new IVKnobControl(b.GetGridCell(21, 5, 10, EDirection::Horizontal, 1), param02));
    pGraphics->AttachControl(new IVKnobControl(b.GetGridCell(22, 5, 10, EDirection::Horizontal, 1), param03));
    pGraphics->AttachControl(new IVKnobControl(b.GetGridCell(23, 5, 10, EDirection::Horizontal, 1), param04));
    pGraphics->AttachControl(new IVKnobControl(b.GetGridCell(24, 5, 10, EDirection::Horizontal, 1), param05));
    pGraphics->AttachControl(new IVKnobControl(b.GetGridCell(25, 5, 10, EDirection::Horizontal, 1), param06));
    pGraphics->AttachControl(new IVKnobControl(b.GetGridCell(26, 5, 10, EDirection::Horizontal, 1), param07));
    pGraphics->AttachControl(new IVKnobControl(b.GetGridCell(27, 5, 10, EDirection::Horizontal, 1), param08));
    pGraphics->AttachControl(new IVKnobControl(b.GetGridCell(28, 5, 10, EDirection::Horizontal, 1), param09));
    pGraphics->AttachControl(new IVKnobControl(b.GetGridCell(29, 5, 10, EDirection::Horizontal, 1), param10));
  };
#endif
}

#if IPLUG_DSP
void PLUG_CLASS_NAME::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChans = NOutChansConnected();
  const int nParams = GetParam(used_parameters)->Value();
  double* params = new double[nParams];

  if (nParams > 0)
    params[0] = GetParam(param01)->Value();
  if (nParams > 1)
    params[1] = GetParam(param02)->Value();
  if (nParams > 2)
    params[2] = GetParam(param03)->Value();
  if (nParams > 3)
    params[3] = GetParam(param04)->Value();
  if (nParams > 4)
    params[4] = GetParam(param05)->Value();
  if (nParams > 5)
    params[5] = GetParam(param06)->Value();
  if (nParams > 6)
    params[6] = GetParam(param07)->Value();
  if (nParams > 7)
    params[7] = GetParam(param08)->Value();
  if (nParams > 8)
      params[8] = GetParam(param09)->Value();
  if (nParams > 9)
      params[9] = GetParam(param10)->Value();

  if (GenericVSTProcessBlock != nullptr)
    GenericVSTProcessBlock(inputs, outputs, nFrames, nChans, params, nParams);
}

void PLUG_CLASS_NAME::OnReset()
{
  GenericVSTModuleHandle = LoadLibraryA(pluginPath.c_str());
  GenericVSTProcessBlock = (GenericVSTProcessBlockFunction)GetProcAddress(GenericVSTModuleHandle, MAKEINTRESOURCEA(1));
}
#endif
