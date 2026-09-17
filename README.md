# PanVK Custom Driver — Mali-G615 MC6

Custom PanVK kbase CSF driver for **Mali-G615 MC6** (Dimensity 8300/8350).
Optimized for **Termux on Android 16**.

## Status: v1.0.0 Stable

| Metric | Value |
|--------|-------|
| Binary size | 31 MB (was 110 MB, -72%) |
| Vulkan API | 1.4.354 |
| Device extensions | 181 |
| Instance extensions | 17 |
| Test pass rate | 100% |
| Thermal (load) | 50-57 C |
| GPU faults | 0 |

**Verified on:**
- Device: Infinix X6873
- SoC: MediaTek Dimensity 8350
- GPU: Mali-G615 MC6 (Valhall v11)
- OS: Android 16 (SDK 36), Termux
- Root: KernelSU

## Features

| Feature | Status |
|---------|--------|
| Vulkan 1.4 | Working |
| Vulkan Compute | 8/8 PASS |
| vkcube | 119.93 FPS |
| Zink OpenGL 3.3 | Working |
| Zink GLES 3.1 | Working |
| MPV 720p | <1% drop |
| MPV 1080p | Working |

## Test Results

### Compute (8/8 PASS)
- compute_smoke
- barrier_smoke
- atomic_smoke
- image_smoke
- push_smoke
- multibuf_smoke

### Graphics
- vkcube: 119.93 FPS
- Zink triangle: PASS
- Zink OpenGL 3.3: PASS
- Zink GLES 3.1: PASS

### Apps
- MPV 720p: PASS
- MPV 1080p (SW): PASS (27% drop)
- MPV 1080p (mediacodec): Partial

### Stability
- 120/120 compute runs: 100%
- 24h long-run: In progress
- Thermal: 50-57 C, no throttle
- GPU faults: Zero

## Installation

### Prerequisites
```
pkg install -y x11-repo tur-repo
pkg install -y vulkan-loader-generic vulkan-tools
pkg install -y mesa-demos mesa-dev
pkg install -y libdrm libandroid-shmem libc++
pkg install -y libx11 libxcb libxshmfence libxrandr
pkg install -y xorgproto libxfixes libxext xcb-util
pkg install -y xorg-server-xvfb imagemagick
```

### Install
```
tar -xzf panvk-custom-driver.tar.gz
cd panvk-custom-driver
bash scripts/install.sh
```

### Activate
```
source ~/panvk-custom/env.sh
```

### Verify
```
vulkaninfo --summary | grep -E "deviceName|driverName"
```

Expected: deviceName=Mali-G615 MC6, driverName=panvk

## Extension Support

Instance: 17 | Device: 181 | Total: 198

Notable supported: VK_EXT_vertex_attribute_divisor, VK_EXT_robustness2, VK_KHR_dynamic_rendering, VK_EXT_extended_dynamic_state

Missing (hardware): VK_EXT_geometry_shader, VK_EXT_shader_viewport_index_layer

## Known Limitations

Hardware (Mali-G615):
- geometryShader = false
- tessellationShader = false
- multiViewport = false

Software:
- MediaCodec AHB interop fails
- VK_KHR_android_surface not supported (Termux)
- Winlator + PanVK stuck at present

## Emulator Status

| Emulator | Driver | Result |
|----------|--------|--------|
| STORM SWITCH | MediaTek | 29 FPS |
| Nyushu | MediaTek | 33 FPS |
| Winlator | Turnip | 1420 FPS |
| Winlator | PanVK | FAIL |

## Credits

- PanVK source: wonderkast02/panvk-g720-kbase-csf
- Contributor: funnymdzz
- Mesa + Zink teams
- dma-heap fix + bundle: @nzrnsyaa

## License
MIT

## Links
- Repo: github.com/nzrnsyaa/panvk-custom-driver
- dma-heap fix: github.com/nzrnsyaa/mali-panvk-dmaheap-fix
- Source: github.com/wonderkast02/panvk-g720-kbase-csf

Last updated: 2026-09-17

## Repo Structure

```
panvk-custom-driver/
├── README.md
├── RELEASE_NOTES.md
├── CREDITS.md
├── LICENSE
├── docs/
│   ├── OPTIMIZATION_REPORT.md
│   └── extensions/
├── panvk/                     (libvulkan_panfrost.so 31 MB)
├── scripts/                   (install.sh, run_tests.sh)
├── tests/                     (test_zink_*.c)
├── modules/                   (dma_heap_selinux_fix)
└── logs/                      (evidence)
```

