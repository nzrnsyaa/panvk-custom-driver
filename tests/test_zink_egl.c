#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <stdio.h>

int main() {
    EGLDisplay dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (!eglInitialize(dpy, NULL, NULL)) {
        printf("eglInitialize failed\n"); return 1;
    }

    EGLint cfg_attr[] = {
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8,
        EGL_NONE
    };
    EGLConfig cfg; EGLint n;
    eglChooseConfig(dpy, cfg_attr, &cfg, 1, &n);

    EGLint ctx_attr[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext ctx = eglCreateContext(dpy, cfg, EGL_NO_CONTEXT, ctx_attr);
    if (ctx == EGL_NO_CONTEXT) { printf("ctx failed\n"); return 1; }

    EGLint pb_attr[] = { EGL_WIDTH, 256, EGL_HEIGHT, 256, EGL_NONE };
    EGLSurface surf = eglCreatePbufferSurface(dpy, cfg, pb_attr);
    if (surf == EGL_NO_SURFACE) { printf("surface failed\n"); return 1; }

    eglMakeCurrent(dpy, surf, surf, ctx);

    printf("GL_VENDOR:   %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION:  %s\n", glGetString(GL_VERSION));

    glClearColor(0.5, 0.2, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    printf("Clear OK\n");

    eglTerminate(dpy);
    return 0;
}
