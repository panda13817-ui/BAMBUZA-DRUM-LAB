# Licensing, dependencies and content provenance

This document is an engineering checklist, not legal advice. Obtain qualified review before commercial distribution.

## Project ownership
No project-wide open-source license is granted by this repository at this stage. Do not assume public visibility means permission to reuse, redistribute or relicense the code.

## Dependencies to audit
- JUCE: select the correct commercial/open-source license for Bambuza's distribution model; record version, license, notices and any obligations.
- VST3 SDK: record the exact version and applicable MIT license text/notices.
- ONNX Runtime: record release, license, bundled binaries and platform-specific dependencies.
- Any DSP, UI, codec or utility libraries: add to a software bill of materials (SBOM).

## AI models
Before shipping a model:
- Record model name, source URL, version and checksum.
- Keep the model card and training-data statements.
- Verify commercial-use, redistribution and derivative restrictions.
- Record required notices and attribution.
- Test whether model weights may be redistributed inside a commercial plugin.
- Do not download or bundle model weights until these checks pass.

## Audio content
- Keep source provenance for all bundled samples and test corpus files.
- Use original recordings, properly licensed libraries or explicit permissions.
- User-imported material remains the user's responsibility; do not repackage it into Bambuza sample packs without rights.
- Separate test-only copyrighted references from distributable assets.

## Release checklist
- [ ] Dependency manifest and SBOM.
- [ ] License texts and third-party notices.
- [ ] JUCE license verified for company revenue and use.
- [ ] Model weights and model cards cleared.
- [ ] Sample and test corpus provenance recorded.
- [ ] EULA and privacy statement reviewed.
