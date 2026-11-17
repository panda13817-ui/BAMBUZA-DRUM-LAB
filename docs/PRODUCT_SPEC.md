# Product specification — Bambuza Drum Lab

## 1. Product intent

Bambuza Drum Lab is a professional instrument and audio-analysis workflow for music producers. Its central workflow is:

**Import reference audio → detect candidate events → classify and group → review/edit → build a playable kit → perform via MIDI → export samples.**

The product is inspired by the general problem space of reference-to-kit tools. It must have original implementation, UX, branding and code. It must not copy proprietary source code, assets, interface layouts or undocumented implementation details from other products.

## 2. Primary users

- Beatmakers and producers working in reggaeton, trap, hip-hop, dancehall and electronic music.
- Recording and production studios.
- Sound designers and sample-library creators.

## 3. V1.0 feature scope

### Core sampler
- 16 playable pads in the initial view.
- Sample loading per pad.
- MIDI note mapping and velocity response.
- Per-pad gain, pan, pitch and amplitude envelope.
- Polyphonic playback with predictable voice stealing.
- Save/load kit state.
- WAV export for individual pads and complete kits.
- Drag-and-drop export where supported by the host/framework.

### Audio analysis
- Import WAV first; add AIFF, FLAC and compressed formats after verifying decoder and licensing choices.
- Waveform overview and zoomable timeline.
- Automatic transient/onset candidates.
- User-editable markers, trim points and audition.
- Analysis runs outside the real-time audio callback.
- Clear progress, cancellation and error states.

### Classification and grouping
- Instrument families: kick, snare, clap, closed hat, open hat, tom, cymbal and percussion.
- Confidence score and user correction.
- Similarity-based grouping must preserve distinct velocity/timbre layers.
- Never silently discard a detected event.

### Advanced intelligence
- Optional local classification model.
- Optional drum/source separation model.
- Reconstruction and cleanup tools.
- MIDI groove extraction only after timing evaluation.
- AI features must be separately benchmarked and may be disabled without affecting sampler operation.

## 4. Non-goals for the first prototype

- Cloud processing or mandatory account sign-in.
- Subscription enforcement.
- A full DAW or sequencer.
- Guaranteed perfect isolation of drum hits from arbitrary mastered songs.
- Commercial redistribution of samples extracted from copyrighted recordings without appropriate rights.

## 5. UX principles

- The sample is always accessible and auditionable.
- Show the detected event and its confidence; let the user correct it.
- Make destructive processing reversible or work on copies.
- Explain model limitations in plain language.
- Keyboard and MIDI workflows should be fast.
- Keep visual hierarchy clear at typical plugin sizes and high-DPI displays.

## 6. Initial product metrics

- Successful load/save round trips for kits.
- Correct MIDI note-to-pad mapping.
- No audio dropouts in the defined stress test.
- Detection precision/recall measured on a labeled test corpus.
- Analysis latency recorded by source duration and machine.
- Human listening review for separation artifacts.

No public accuracy or speed claim should be published until supported by a reproducible benchmark.
