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
