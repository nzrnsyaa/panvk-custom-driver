# PanVK Custom Driver — Mali-G615 MC6

Custom distribution of PanVK kbase CSF driver for Mali-G615 MC6
(Dimensity 8300/8350) with Zink OpenGL support.

## Status: Beta 1.0

Verified working on:
- Device: Infinix X6873
- SoC: MediaTek Dimensity 8350
- GPU: Mali-G615 MC6 (Valhall v11)
- OS: Android 15, Termux (Bionic arm64)
- Kernel: kbase CSF uAPI 1.21

## Features

| Feature | Status |
|---------|--------|
| Vulkan 1.4 (PanVK) | OK |
| Vulkan Compute | OK - 8/8 tests PASS |
| Vulkan Graphics (vkcube) | OK - 100 FPS |
| OpenGL 3.3 Core (via Zink) | OK |
| OpenGL ES 3.1 (via Zink) | OK |
| MPV video playback | OK |

## Installation

### Prerequisites

pkg install -y x11-repo tur-repo
pkg install -y vulkan-loader-generic vulkan-tools
pkg install -y mesa-demos mesa-dev
pkg install -y libdrm libandroid-shmem libc++
pkg install -y libx11 libxcb libxshmfence libxrandr
pkg install -y xorgproto libxfixes libxext xcb-util
pkg install -y xorg-server-xvfb imagemagick

### Install

tar -xzf panvk-custom-driver.tar.gz
cd panvk-custom-driver
bash scripts/install.sh

Or custom location:

bash scripts/install.sh /path/to/install

### Activate

source ~/panvk-custom/env.sh

### Verify

vulkaninfo | grep -E "deviceName|driverName"

Expected output:
  deviceName = Mali-G615 MC6
  driverName = panvk

## Testing

Run full suite:

bash scripts/run_tests.sh

Individual tests:

cd ~/panvk-custom/tests
clang -o test_zink_triangle test_zink_triangle.c -lEGL -lGLESv2
./test_zink_triangle

Expected output:

GL_RENDERER: zink Vulkan 1.4(Mali-G615 MC6 (MESA_PANVK))
GL_VERSION:  OpenGL ES 3.1 Mesa 26.0.6
[OK] Shader compiled
[OK] Program linked
[OK] Triangle drawn
[INFO] Pixel(128,128) = R=255 G=128 B=0 A=255
[PASS] Triangle rendered correctly (orange)

## Usage

### Environment variables

env.sh sets:
- VK_ICD_FILENAMES - PanVK ICD json
- VK_DRIVER_FILES - same (loader 1.4+)
- LD_LIBRARY_PATH - driver directory
- MESA_LOADER_DRIVER_OVERRIDE=zink - Zink as OpenGL
- GALLIUM_DRIVER=zink - Gallium frontend

### Running OpenGL apps

source ~/panvk-custom/env.sh
mpv --vo=gpu --gpu-api=opengl --gpu-context=x11egl video.mp4

## Known Limitations

1. shaderClipDistance not supported by Mali-G615
   - Zink warning, falls back gracefully
   - Minor visual artifacts possible

2. dma-heap permission denied
   - /dev/dma_heap/system inaccessible
   - Present path uses software copy

3. X11 platform limitations
   - Screenshot via import may fail
   - Use Termux-X11 app for proper display

4. Not for Windows emulation
   - Winlator stuck at vkAcquireNextImageKHR
   - Not yet supported

## Architecture

App (OpenGL/GLES)
    |
    v
Zink (translator)
    |
    v
Vulkan API + Loader
    |
    v
PanVK (ICD driver)
    |
    v
kbase CSF (kernel)
    |
    v
Mali-G615 MC6 GPU

## Credits

Original PanVK driver:
- wonderkast02/panvk-g720-kbase-csf
- Contributor: funnymdzz
- Based on Mesa project

Zink:
- Mesa project
- OpenGL-on-Vulkan translation layer

This distribution:
- Package + test suite + documentation

See CREDITS.md for full credits.

## License

MIT. See LICENSE file.

## Changelog

### 1.0-beta (2026-09-14)
- Initial release
- PanVK compute + graphics verified
- Zink OpenGL confirmed working
- Test suite included

## DMA Heap SELinux Module (KernelSU)

Solve dma-heap permission denied untuk hardware present path.

Location: modules/dma_heap_selinux_fix/

Result: vkcube FPS 98 → 130 (+32%) dengan SELinux Enforcing.
