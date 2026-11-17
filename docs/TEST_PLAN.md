# Test plan

## 1. Unit tests
- MIDI note-to-pad mapping, including boundary notes.
- Velocity curve behavior.
- Gain/pan/pitch parameter ranges.
- Envelope stage transitions.
- Sample trim bounds and empty/invalid asset handling.
- Kit schema parsing, validation and version migration.
- WAV export frame count, sample rate, channel count and peak safety.

## 2. Audio engine tests
- One voice, 16 simultaneous voices and voice-limit stress.
- Repeated note-on/note-off and overlapping notes.
- Abrupt stop, transport stop and plugin release.
- Mono and stereo samples.
- Source sample rates differing from host sample rate.
- Host block sizes including small and variable block sizes.
- No allocations, blocking locks or file access in processBlock.

## 3. Host compatibility
Record OS, CPU architecture, DAW version, plugin format, sample rate, block size and result.
- Ableton Live 12 on macOS Intel.
- Ableton Live 12 on macOS Apple Silicon.
- Ableton Live 12 on Windows x64.
- Logic Pro on macOS for AU.
- Standalone on supported macOS and Windows versions.

## 4. Analysis evaluation
Create a rights-cleared, manually labeled corpus with:
- Clean isolated drum hits.
- Drum loops with overlapping instruments.
- Full mixes with bass, vocals and melodic content.
- Different tempos, dynamics and recording quality.

Measure:
- Onset precision, recall and F-score using a declared timing tolerance.
- False-positive rate by source type.
- Classification confusion matrix and per-class precision/recall.
- Analysis time per minute of source audio.
- Peak memory use.

## 5. Separation evaluation
- Use only licensed/consented test audio.
- Compare isolated estimates with known stems where available.
- Record objective metrics and blind listening notes.
- Check transient smearing, phase artifacts, residual vocals and bass leakage.
- Do not market results as perfect isolation.

## 6. Release gates
- No known data-loss or crash-level defects.
- No realtime-thread file I/O or blocking calls.
- Reproducible builds from documented instructions.
- Dependency and model licenses checked.
- All advertised features tested on the declared platforms.
