# PanVK Binary Optimization Report

**Date:** 2026-09-17
**Driver:** libvulkan_panfrost.so (Mesa 26.3.0-devel)

## Summary

| Metric | Before | After | Change |
|--------|--------|-------|--------|
| Binary size | 110 MB | 31 MB | -72% |
| Bundle size | 97 MB (5 parts) | ~31 MB (1 part) | -68% |
| Disk footprint | 143 MB | 33 MB | -77% |
| Functional | PASS | PASS | No regression |

## Strip Details

### Command
llvm-strip --strip-debug libvulkan_panfrost.so

### What It Removes
- DWARF debug sections
- Line number tables
- Debug string tables
- KEEPS: dynamic symbols (.dynsym), code sections, data

### Why --strip-debug (not --strip-all)
- Shared libraries need dynamic symbols for linking
- --strip-all removes .dynsym, can break runtime loading
- --strip-debug is safe for .so

## Verification

| Test | Result |
|------|--------|
| vkcube --c 300 | PASS |
| compute_smoke | PASS |
| barrier_smoke | PASS |
| atomic_smoke | PASS |
| image_smoke | PASS |
| push_smoke | PASS |
| multibuf_smoke | PASS |

Total: 7/7 PASS

## Reproduce

cp libvulkan_panfrost.so libvulkan_panfrost.so.original
$PREFIX/bin/llvm-strip --strip-debug libvulkan_panfrost.so
ls -lh libvulkan_panfrost.so
vulkaninfo --summary | grep -E "deviceName|driverName"
vkcube --c 300

## Notes

- file command may still report "not stripped" - normal
- Dynamic symbol table (.dynsym) preserved intentionally
- Same BuildID: 1c8701564669191d7f86d77ec820d3365f3a8d08
