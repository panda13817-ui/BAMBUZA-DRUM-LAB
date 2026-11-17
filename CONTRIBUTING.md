# Contributing

## Workflow
1. Create a feature branch from `main`.
2. Keep changes focused and document architectural decisions.
3. Add or update tests.
4. Run formatting, unit tests and target builds.
5. Open a pull request with scope, test evidence and known limitations.

## Branch naming
- `feat/<short-name>`
- `fix/<short-name>`
- `docs/<short-name>`
- `build/<short-name>`

## Commit convention
Use concise messages such as:
- `feat(sampler): add MIDI pad triggering`
- `fix(audio): prevent invalid sample bounds`
- `docs(architecture): describe analysis thread`

## Audio-thread safety
Any change to the audio callback must explicitly state whether it allocates, locks, performs I/O, calls UI code or invokes inference. Such operations must not occur in the real-time callback.

## Pull request checklist
- [ ] Scope and behavior explained.
- [ ] Build/test evidence included.
- [ ] Realtime safety reviewed.
- [ ] State compatibility considered.
- [ ] Third-party content/licenses checked.
