# Spectrum Meter — macOS source project

A JUCE starter project inspired by the supplied purple/black reference. This is source code, NOT a compiled or tested installer.

## Requirements
macOS, Xcode Command Line Tools, CMake and Git. Install tools with:
`xcode-select --install`
`brew install cmake git`

## Build
Open Terminal in this folder and run:
`cmake -S . -B build -DCMAKE_BUILD_TYPE=Release`
`cmake --build build --config Release`

CMake fetches JUCE from its official GitHub repository, so internet is required. Outputs are under `build/SpectrumMeter_artefacts/Release/`.

Install VST3 in `~/Library/Audio/Plug-Ins/VST3/` or AU in `~/Library/Audio/Plug-Ins/Components/`, then rescan plugins in your DAW.

## Honest status
This starter code has not been compiled or tested on a Mac here. It currently implements live FFT drawing and a resizable purple/black interface. Several dropdowns are visual placeholders; channel selection is not yet separated, and the waterfall/sonogram buttons are not yet implemented as true history views. Treat it as a starting point, not a finished professional analyzer.
