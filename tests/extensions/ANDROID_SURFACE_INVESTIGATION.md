# PanVK Android Surface Investigation

## Verdict
`VK_KHR_android_surface` **NOT applicable** for Termux use case.

## Why
1. Termux cannot access `ANativeWindow` (Android app API only)
2. Fork deliberately targets Termux-X11 (`WSI_X11_TERMUX` env)
3. Would require Android HAL module registration (system-level)

## What PanVK HAS
- `panvk_android.c` (392 lines) — AHB/ANB memory sharing
- `panvk_android.h` — gralloc image support
- AHB import: `panvk_android_create_gralloc_image()`
- Conditional compile: `with_platform_android`

## What PanVK MISSING
- `VK_KHR_android_surface` extension
- HAL module (`HAL_MODULE_INFO_SYM`)
- `vkCreateAndroidSurfaceKHR` entry point
- WSI backend for Android surface

## Reference
- Turnip: `tu_android.c` (HAL module, gralloc)
- Turnip: `tu_wsi.cc` (WSI dispatch)
- Common WSI: `wsi_common.c:3705` marks android as `req_unsupported`

## When It Would Matter
Only if:
- Building PanVK as system Vulkan HAL
- Developing native Android APK with Vulkan
- Replacing Mali stock driver system-wide

For Termux: stick with X11 path.

## Saved
$(date)
