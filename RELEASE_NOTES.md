# Release v1.0-beta

Date: 2026-09-14

## Summary

First public release of PanVK Custom Driver for Mali-G615 MC6.

## What is Included

- PanVK driver (libvulkan_panfrost.so) - Vulkan 1.4 driver
- Install script - Auto-install to ~/panvk-custom/
- Test suite - Verify installation works
- Documentation - README, LICENSE, CREDITS

## Verified Working

| Feature | Status |
|---------|--------|
| Vulkan compute | 8/8 tests PASS |
| vkcube graphics | 100 FPS |
| OpenGL 3.3 (via Zink) | PASS |
| OpenGL ES 3.1 (via Zink) | PASS |
| Triangle shader | Pixel correct |
| MPV video playback | Works |

## Tested Hardware

- Device: Infinix X6873
- SoC: MediaTek Dimensity 8350
- GPU: Mali-G615 MC6
- OS: Android 16, Termux

## Known Issues

- shaderClipDistance not supported (Zink warning)
- dma-heap permission denied (software present)
- Xvfb screenshot limitations
- Not for Windows emulation (Winlator stuck)

## Credits

- PanVK: wonderkast02/panvk-g720-kbase-csf
- Zink: Mesa project
- Bundle: PanVK Custom (community)

## License

MIT

## v1.0.0-stable (2026-09-17)

### 🎯 Binary Optimization
- **Size:** 110 MB → 31 MB (**72% reduction**)
- **Tool:** `llvm-strip --strip-debug`
- **Method:** Removed DWARF debug sections, kept dynamic symbols
- **Why --strip-debug:** Safe for shared libraries (`.so`)

### ✅ Post-Strip Verification
All tests PASS:
- vkcube: EXIT 0
- compute_smoke: PASS (1024 elements correct)
- barrier_smoke: PASS
- atomic_smoke: PASS
- image_smoke: PASS
- push_smoke: PASS
- multibuf_smoke: PASS

**Total:** 7/7 tests PASS

### 📦 Impact
- Bundle size reduced from ~97 MB (5 parts) → **~31 MB (1 part)**
- Faster download
- Same functionality
- Easier distribution
