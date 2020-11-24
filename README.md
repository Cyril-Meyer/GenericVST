# GenericVST
The GenericVST project aims to create an easy-to-use VST platform for developers who want to experience new things without having to use heavy VST architectures.

GenericVST is designed to make research and experimentation around sound processing more accessible and quick to set up, but it can be used in a professional production context.

To create a new audio processing effect, you only have to compile new plugin as a [dynamic link library](https://en.wikipedia.org/wiki/Dynamic-link_library) as in the example [PluginVolumeControl](https://github.com/Cyril-Meyer/GenericVST/tree/main/PluginVolumeControl). Only one exported function, and let's go!


### Projects
GenericVST is the name of the VST plugin, and of the name of the project as a whole. Here is a list of all the GenericVST related projects.
* [GenericVST](https://github.com/Cyril-Meyer/GenericVST/tree/main/GenericVST)
  * The VST plugin, to be used with your DAW.
  * Based on [iPlug2](https://github.com/iPlug2/iPlug2) framework.
* [PluginTest](https://github.com/Cyril-Meyer/GenericVST/tree/main/PluginTest)
  * A plugin test environment, easier for debugging than GenericVST.
* [PluginVolumeControl](https://github.com/Cyril-Meyer/GenericVST/tree/main/PluginVolumeControl)
  * An example plugin for GenericVST, copy of the [IPlugEffect](https://github.com/iPlug2/iPlug2/tree/master/Examples/IPlugEffect) example.
  
