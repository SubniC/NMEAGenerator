# Changelog

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2026-06-22

Documentation/packaging refresh of the original 2019 library, plus a few fixes to
long-standing defects.

### Fixed
- `print()` output garbage: it passed a `String*` to `printf("%s", ...)`. Now uses the
  portable `Stream::print(*_sentence)` (also avoids `Stream::printf`, unavailable on AVR cores).
- Checksum buffer overflow: `sprintf("%02X")` wrote 3 bytes (2 digits + NUL) into a
  `char[2]`. Buffer widened to `char[3]`.
- Memory mismatch in `_resetState()`: `_sentence` was allocated with `new` but released
  with `free()`. Now uses `delete`.
- Default constructor left member pointers uninitialized; they are now zero-initialized
  (so a stray `clear()` does `delete nullptr` safely).

### Added
- `keywords.txt` for Arduino IDE syntax highlighting.
- `examples/BasicSentence` sketch.
- Full README (features, installation, usage, API).
- This changelog.

### Changed
- Updated `library.properties` (author/maintainer `mdps`, version `1.0.0`,
  `category=Communication`, project URL).
- Cleaned up source comments and removed dead commented-out code and the unused
  `_tmpstr` member.
- Relicensed from GPL-3.0 to MIT © mdps.

### Removed
- Legacy `readme.txt` (Visual Micro boilerplate); content folded into README.

## [0.1.0] - 2019-02-13

First working version (legacy).

### Added
- `NMEAGenerator` class to assemble NMEA 0183 sentences field by field with
  overloaded `append()`, automatic checksum generation, and `getSentence()` /
  `print()` output.
