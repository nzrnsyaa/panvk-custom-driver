#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <stdio.h>
#include <string.h>

static const char *VS =
    "attribute vec4 vPos;\n"
    "void main() { gl_Position = vPos; }\n";

static const char *FS =
    "precision mediump float;\n"
    "void main() { gl_FragColor = vec4(1.0, 0.5, 0.0, 1.0); }\n";

static GLuint compile(GLenum type, const char *src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, NULL);
    glCompileShader(s);
    GLint ok;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(s, 512, NULL, log);
        printf("Shader fail: %s\n", log);
        return 0;
    }
    return s;
}

int main() {
    EGLDisplay dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (!eglInitialize(dpy, NULL, NULL)) {
        printf("eglInitialize failed\n"); return 1;
    }

    EGLint cfg_attr[] = {
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8,
        EGL_NONE
    };
    EGLConfig cfg; EGLint n;
    eglChooseConfig(dpy, cfg_attr, &cfg, 1, &n);

    EGLint ctx_attr[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext ctx = eglCreateContext(dpy, cfg, EGL_NO_CONTEXT, ctx_attr);

    EGLint pb_attr[] = { EGL_WIDTH, 256, EGL_HEIGHT, 256, EGL_NONE };
    EGLSurface surf = eglCreatePbufferSurface(dpy, cfg, pb_attr);

    eglMakeCurrent(dpy, surf, surf, ctx);

    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION:  %s\n\n", glGetString(GL_VERSION));

    GLuint vs = compile(GL_VERTEX_SHADER, VS);
    GLuint fs = compile(GL_FRAGMENT_SHADER, FS);
    if (!vs || !fs) return 1;
    printf("[OK] Shader compiled\n");

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    GLint linked;
    glGetProgramiv(prog, GL_LINK_STATUS, &linked);
    if (!linked) { printf("Link fail\n"); return 1; }
    printf("[OK] Program linked\n");

    GLfloat verts[] = {
        0.0f,  0.8f,
       -0.8f, -0.8f,
        0.8f, -0.8f,
    };
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    GLint pos = glGetAttribLocation(prog, "vPos");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glViewport(0, 0, 256, 256);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(prog);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glFinish();
    printf("[OK] Triangle drawn\n");

    unsigned char pixel[4];
    glReadPixels(128, 128, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    printf("[INFO] Pixel(128,128) = R=%d G=%d B=%d A=%d\n",
           pixel[0], pixel[1], pixel[2], pixel[3]);

    int pass = (pixel[0] > 200 && pixel[1] > 100 && pixel[1] < 180 && pixel[2] < 50);
    if (pass) {
        printf("\n[PASS] Triangle rendered correctly (orange)\n");
    } else {
        printf("\n[FAIL] Pixel warna salah — expected orange\n");
    }

    eglTerminate(dpy);
    return pass ? 0 : 1;
}
