#!/data/data/com.termux/files/usr/bin/bash
# PanVK Custom Driver Installer
# Usage: bash install.sh [target_dir]
# Default: ~/panvk-custom

set -e

BUNDLE_DIR="$(cd "$(dirname "$0")/.." && pwd)"
TARGET="${1:-$HOME/panvk-custom}"

echo "=========================================="
echo " PanVK Custom Driver Installer"
echo "=========================================="
echo "Bundle: $BUNDLE_DIR"
echo "Target: $TARGET"
echo ""

# Check existing
if [ -d "$TARGET" ]; then
    echo "⚠ Target wujud. Backup ke ${TARGET}.bak.$(date +%s)"
    mv "$TARGET" "${TARGET}.bak.$(date +%s)"
fi

# Copy
mkdir -p "$TARGET"
cp -r "$BUNDLE_DIR/panvk" "$TARGET/"
cp -r "$BUNDLE_DIR/tests" "$TARGET/" 2>/dev/null

# Patch ICD
sed "s|__INSTALL_DIR__|$TARGET|g" \
    "$BUNDLE_DIR/panvk/panvk_icd.template.json" \
    > "$TARGET/panvk/panvk_icd.json"

# Buat env.sh
cat > "$TARGET/env.sh" <<EOF
#!/data/data/com.termux/files/usr/bin/bash
# PanVK Custom Driver — Environment Setup
# Source file ni untuk aktifkan PanVK + Zink

export PANVK_DIR="$TARGET"
export VK_ICD_FILENAMES="\$PANVK_DIR/panvk/panvk_icd.json"
export VK_DRIVER_FILES="\$PANVK_DIR/panvk/panvk_icd.json"
export LD_LIBRARY_PATH="\$PANVK_DIR/panvk:\$LD_LIBRARY_PATH"

# Zink as OpenGL driver (opsional)
export MESA_LOADER_DRIVER_OVERRIDE=zink
export GALLIUM_DRIVER=zink
export LIBGL_ALWAYS_SOFTWARE=0

unset LD_PRELOAD
EOF
chmod +x "$TARGET/env.sh"

echo ""
echo "✅ Install siap!"
echo ""
echo "=== Cara guna ==="
echo "  source $TARGET/env.sh"
echo "  vulkaninfo | grep deviceName"
echo ""
echo "=== Test ==="
echo "  cd $TARGET/tests"
echo "  clang -o test_zink_triangle test_zink_triangle.c -lEGL -lGLESv2"
echo "  ./test_zink_triangle"
echo ""
echo "=== Verify ICD ==="
cat "$TARGET/panvk/panvk_icd.json"
