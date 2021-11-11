# Wicked Space Flight

Wicked Space Flight is an example project for the wicked engine

The one important bit that is different when building outside is to set
```cpp
wiRenderer::SetShaderSourcePath(WickedEngine_SHADER_DIR);
```
in your code, before the initialization of the MainComponent.


## Using CMAKE
### Requirements
Wicked Engine built with cmake somewhere in your system (does not matter where).
The build folder is going to be important in the next step.

### Build
```sh
$ cmake -B build -DWickedEngine_DIR=/path/to/wicked/build_folder/cmake .
$ cmake --build build -j8
```
The cmake build already defines the `WickedEngine_SHADER_DIR` to the correct path, 
no need to do anything manual aside from "Finding" the engine and linking to it.

## Using Microsoft Solution Files
At the moment it's not supported.
Need some help in how to make this because I don't know.
