# PanVK Extension Report

**Driver:** Mesa 26.3.0-devel (git-1d3fa42c49)
**Source:** wonderkast02/panvk-g720-kbase-csf fork
**Build:** NDK r29, Android API 24, aarch64
**Binary:** libvulkan_panfrost.so (110 MB, not stripped)

## Extension Counts

| Layer | Count |
|-------|-------|
| Instance | 17 |
| Device | 181 |
| Total | 198 |

## Gaps (Known Limitations)

### Hardware-limited (Mali GPU architecture)
- `VK_EXT_geometry_shader` — NOT supported on Mali Valhall
- `VK_EXT_shader_viewport_index_layer` — depends on GS

### Software-gap (progressively being added upstream)
- `VK_EXT_shader_object`
- `VK_EXT_multi_draw`
- `VK_EXT_descriptor_buffer`
- `VK_EXT_shader_atomic_float2`
- `VK_KHR_portability_subset`

## Emulator Compatibility

- Yuzu / STORM SWITCH: 12 missing features (see gaps above)
- Winlator: fails at vkAcquireNextImageKHR (WSI issue, not extension)
- MediaCodec interop: AHB external memory not supported

## Verdict

181 device extensions is above-average for Mesa PanVK.
Fork is well-maintained and feature-complete for compute + graphics workload.
Only hard limit is Mali's lack of geometry shader hardware.
