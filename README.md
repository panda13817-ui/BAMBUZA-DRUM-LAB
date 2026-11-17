# BAMBUZA DRUM LAB

**Bambuza Components** · Professional tools for modern music producers.

Bambuza Drum Lab is a cross-platform drum-sampling instrument designed to turn audio references into editable, playable drum kits.

> Product direction: Audio to Kit. Detect, classify, organize, edit, play and export.

## Project status

**Foundation / Build 0.1 — repository initialized.** This repository currently contains the product and engineering specifications. The first implementation milestone is a JUCE-based sampler plugin with 16 pads, WAV import, MIDI triggering, kit persistence and WAV export.

## Initial targets

- macOS: VST3, Audio Units (AU), Standalone
- Windows x64: VST3, Standalone
- Primary DAW validation: Ableton Live 12
- Language: C++17 initially (C++20 where toolchain support is verified)
- Build system: CMake
- Audio framework: JUCE
- Future local ML runtime: ONNX Runtime, behind an optional analysis module

## Repository map

- `docs/PRODUCT_SPEC.md` — product definition and scope
- `docs/ARCHITECTURE.md` — software and audio-thread architecture
- `docs/ROADMAP.md` — milestones and acceptance criteria
- `docs/TEST_PLAN.md` — functional, audio and compatibility tests
- `docs/LICENSING.md` — dependency and distribution checks
- `CONTRIBUTING.md` — development workflow
- `CMakeLists.txt` — initial build configuration
- `Source/` — C++ source tree

## Development principles

1. Audio playback must remain independent from offline analysis and AI inference.
2. No blocking I/O, locks, memory allocation or model inference in the real-time audio callback.
3. Every analysis result must be reviewable and editable by the user.
4. AI modules are optional and local-first; the base sampler must work without them.
5. Third-party licenses and model/data provenance must be recorded before distribution.
6. Product claims must be backed by repeatable tests.

## Build status

The repository foundation is being established. A successful plugin build has **not** yet been claimed. See the roadmap for the first compile-and-test milestone.

## License

No project-wide open-source license is granted yet. See [docs/LICENSING.md](docs/LICENSING.md).