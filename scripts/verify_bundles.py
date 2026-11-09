"""Fail CI if a native VST3 is missing or contains no meaningful binary."""
from pathlib import Path
import sys

root = Path(sys.argv[1] if len(sys.argv) > 1 else "build")
bundles = list(root.rglob("*.vst3"))
if not bundles:
    raise SystemExit("ERROR: No VST3 plugin found. Do not publish this build.")

for bundle in bundles:
    if bundle.is_file():
        binaries = [bundle]
    else:
        binaries = [p for p in bundle.rglob("*") if p.is_file() and p.suffix.lower() in {".dll", ".so", ".dylib", ".vst3"}]
        binaries += [p for p in bundle.rglob("Contents/MacOS/*") if p.is_file()]
    if not any(p.stat().st_size > 20_000 for p in binaries):
        raise SystemExit(f"ERROR: {bundle} has no plausible compiled native binary")
    print(f"Verified compiled bundle present: {bundle}")
print("NOTE: This does not verify DAW loading, sound, installer behavior, or signing.")
