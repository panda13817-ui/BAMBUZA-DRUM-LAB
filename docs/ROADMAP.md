# Roadmap and acceptance criteria

## Build 0.1 — repository and sampler foundation
- [x] Create repository documentation and module structure.
- [ ] Configure JUCE dependency strategy and CMake targets.
- [ ] Build empty plugin shell for macOS and Windows.
- [ ] Implement 16-pad sampler.
- [ ] Load WAV into a pad.
- [ ] Trigger pads by MIDI note and velocity.
- [ ] Save/restore basic kit state.
- [ ] Add standalone target.

**Exit criteria:** plugin loads in at least one VST3 host on each target OS; MIDI triggers samples with no audible glitches in the defined test; state survives save/reopen.

## Build 0.2 — editing and export
- [ ] Per-pad gain, pan and pitch.
- [ ] ADSR amplitude envelope.
- [ ] Sample start/end and audition.
- [ ] Export individual pad WAV and full kit.
- [ ] Drag-and-drop export where supported.
- [ ] Automated tests for state and MIDI mapping.

**Exit criteria:** create, save, reopen and export a 16-pad kit without losing pad assignments or settings.

## Build 0.3 — audio import and analysis
- [ ] Import reference audio.
- [ ] Waveform overview and zoom.
- [ ] Offline onset/transient candidate detection.
- [ ] Editable markers and audition.
- [ ] Cancellation, progress and error handling.

**Exit criteria:** detector output is reproducible and editable; benchmark results are recorded against a labeled evaluation set.

## Build 0.4 — classification and grouping
- [ ] Establish labeled, rights-cleared evaluation corpus.
- [ ] Add classifier adapter and baseline model.
- [ ] Display labels and confidence.
- [ ] Allow manual relabeling.
- [ ] Similarity grouping and split/merge controls.

**Exit criteria:** per-class precision/recall and confusion matrix reviewed; no events silently removed.

## Build 0.5 — advanced isolation research
- [ ] Compare candidate open models and licenses.
- [ ] Prototype local inference outside realtime thread.
- [ ] Evaluate drum separation on licensed test material.
- [ ] Add quality controls and artifact review.
- [ ] Keep feature optional if quality or performance is insufficient.

**Exit criteria:** documented benchmark, model provenance and reproducible installation; users can bypass the feature.

## Build 1.0 — release candidate
- [ ] macOS Intel and Apple Silicon builds.
- [ ] Windows x64 build.
- [ ] VST3 and AU (macOS), Standalone.
- [ ] Host compatibility test matrix.
- [ ] Installer, signing/notarization and release packaging.
- [ ] License audit, privacy note and EULA.
- [ ] User manual and demo project.
- [ ] Closed beta and issue triage.

## Priority policy

P0: crashes, audio glitches, data loss, host incompatibility.
P1: core sampler, MIDI, state, import/export defects.
P2: analysis quality, usability and performance improvements.
P3: visual polish and optional convenience features.
