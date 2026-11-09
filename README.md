# Soundhead Development

Native audio plug-in development workspace.

## First project: Soundhead Gain

A minimal, original JUCE gain plug-in used to validate the complete cross-platform build pipeline. This is **source code**, not yet an installable release.

### Planned targets
- Windows: VST3, then a verified EXE installer
- macOS: VST3 and Audio Unit, then a verified PKG installer
- AAX is out of scope until its SDK and licensing/signing prerequisites are available.

### Build locally

Requirements: CMake 3.22+, C++17 compiler, Git, and an internet connection for fetching JUCE.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

GitHub Actions is configured to attempt native builds on Windows and macOS. A successful compilation alone **does not prove installation or DAW compatibility**. Release installers must be separately generated and verified.

Project name and repository name intentionally differ: this shared repository is currently named `smiley-nan`.
