#!/data/data/com.termux/files/usr/bin/bash
# PanVK Custom Driver — Test Runner

PANVK_DIR="${PANVK_DIR:-$HOME/panvk-custom}"
cd "$PANVK_DIR"
source ./env.sh

echo "=========================================="
echo " PanVK Custom Driver — Test Suite"
echo "=========================================="
echo ""

# Test 1: Vulkan device
echo "[1/5] Vulkan device detection..."
vulkaninfo 2>&1 | grep -E "deviceName|driverName" | head -3

echo ""
echo "[2/5] Zink detection..."
eglinfo 2>&1 | grep -E "EGL driver name|renderer" | head -3

echo ""
echo "[3/5] Triangle shader test..."
cd "$PANVK_DIR/tests"
if [ ! -f test_zink_triangle ]; then
    clang -o test_zink_triangle test_zink_triangle.c -lEGL -lGLESv2 2>&1 | head -3
fi
./test_zink_triangle 2>&1 | grep -vE "MESA-PANVK|kbase|subqueue" | tail -10

echo ""
echo "[4/5] Zink EGL test..."
if [ ! -f test_zink_egl ]; then
    clang -o test_zink_egl test_zink_egl.c -lEGL -lGLESv2 2>&1 | head -3
fi
./test_zink_egl 2>&1 | grep -vE "MESA-PANVK|kbase|subqueue" | tail -5

echo ""
echo "[5/5] MPV test (opsional)..."
if command -v mpv >/dev/null; then
    if [ -f "$PANVK_DIR/tests/testsrc.mp4" ]; then
        mpv --vo=gpu --gpu-api=opengl --gpu-context=x11egl \
            --no-audio --frames=10 --no-osc \
            "$PANVK_DIR/tests/testsrc.mp4" 2>&1 | \
            grep -vE "MESA-PANVK|kbase|subqueue" | tail -5
    else
        echo "  (skip — testsrc.mp4 takde)"
    fi
else
    echo "  (skip — mpv tak installed)"
fi

echo ""
echo "=========================================="
echo " Test Suite Complete"
echo "=========================================="
