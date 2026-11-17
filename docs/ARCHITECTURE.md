# Architecture — Bambuza Drum Lab

## 1. High-level components

- **Plugin/Host layer:** JUCE AudioProcessor, bus layout, parameters, state serialization and host integration.
- **Sampler engine:** preloaded sample data, voices, envelopes, interpolation, gain/pan and voice management.
- **MIDI layer:** note mapping, velocity curves, note-off and controller handling.
- **Analysis service:** asynchronous file decoding, waveform peak cache, onset detection and event metadata.
- **Classification service:** optional inference adapter; no dependency in the audio callback.
- **Kit persistence:** versioned JSON metadata plus referenced audio assets (or documented embedded-state policy).
- **Export service:** offline WAV rendering and filesystem operations.
- **UI:** source browser, detection timeline, 4×4 pad grid, selected-pad editor and kit manager.

## 2. Threading contract

### Real-time audio thread
Allowed:
- Read immutable/prepared sample buffers.
- Read lock-free or host-safe parameter values.
- Process MIDI events.
- Mix active voices into output buffers.

Forbidden:
- File I/O or directory traversal.
- Network calls.
- Model inference.
- Blocking mutex acquisition.
- Unbounded allocation/deallocation.
- UI calls or message-thread waits.
- Logging that can block.

### Background workers
- Decode/import files.
- Compute waveform caches and onset candidates.
- Run classification or separation inference.
- Create exports and write kit files.
- Publish immutable results to the message thread through safe queues or message posting.

## 3. Data flow

1. User selects an audio file.
2. Background importer validates and decodes it.
3. Analysis worker computes duration, sample rate, channel count and waveform peaks.
4. Detection worker creates timestamped event candidates.
5. User reviews, edits and accepts candidates.
6. Optional classification/grouping runs against accepted segments.
7. Selected segments are copied/rendered into prepared sample buffers.
8. Sampler engine plays those buffers using MIDI.
9. Persistence/export workers write kit data and WAV files.

## 4. Data model (initial)

### SampleAsset
- Stable ID.
- Name and source reference.
- Sample rate, channels, frame count.
- Audio buffer or managed asset path.
- Root MIDI note and tuning metadata.
- Trim start/end.
- Optional provenance and license metadata.

### Pad
- Stable ID and pad index (0–15).
- MIDI note and channel policy.
- One or more velocity layers (future).
- Gain, pan, pitch.
- Attack, hold, decay, sustain, release.
- Choke group (future).

### DetectionEvent
- Start/end frame.
- Confidence.
- User-accepted state.
- Optional family label and classifier confidence.
- Group ID.

### KitDocument
- Schema version.
- Product version.
- Pad list and parameters.
- Asset references or embedded asset manifest.
- User metadata.

## 5. Plugin formats and targets

- macOS: VST3, AU and Standalone.
- Windows x64: VST3 and Standalone.
- Validate host behavior with Ableton Live 12; AU validation additionally requires a compatible AU host such as Logic Pro.
- Do not claim Windows ARM compatibility in the initial release.

## 6. Dependency boundaries

- JUCE for plugin wrapper, UI, audio utilities and supported file formats, subject to its applicable license.
- Steinberg VST3 SDK as required by the selected JUCE/toolchain configuration and its license terms.
- ONNX Runtime only behind a separate optional inference interface.
- Keep model files, model cards, source licenses and checksums outside the core sampler binary where practical.

## 7. Reliability

- Version all persisted state.
- Validate sample format, size and duration before allocation.
- Guard against malformed files and oversized input.
- Handle missing sample assets gracefully.
- Make analysis cancellable.
- Maintain deterministic sampler behavior for the same state and MIDI sequence.
