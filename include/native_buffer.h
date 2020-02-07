#ifndef NATIVE_BUFFER_H
#define NATIVE_BUFFER_H

#include <stdint.h>
#include <utils/Singleton.h>
#include <EGL/egl.h>
#include <gralloc_priv.h>
#include <EGL/eglext.h>

/*
   Added by @Lunarixus
   Since Oreo removed android_native_buffer_t
   the struct needs to be added here for backwards compatibility
*/
#define ANDROID_NATIVE_MAKE_CONSTANT(a,b,c,d) \
    (((unsigned)(a)<<24)|((unsigned)(b)<<16)|((unsigned)(c)<<8)|(unsigned)(d))

#define ANDROID_NATIVE_BUFFER_MAGIC \
    ANDROID_NATIVE_MAKE_CONSTANT('_','b','f','r')

typedef struct android_native_base_t
{
    /* a magic value defined by the actual EGL native type */
    int magic;

    /* the sizeof() of the actual EGL native type */
    int version;
    void* reserved[4];
    /* reference-counting interface */
    void (*incRef)(struct android_native_base_t* base);
    void (*decRef)(struct android_native_base_t* base);
} android_native_base_t;

typedef struct android_native_buffer_t
{
#ifdef __cplusplus
    android_native_buffer_t() { 
        common.magic = ANDROID_NATIVE_BUFFER_MAGIC;
        common.version = sizeof(android_native_buffer_t);
        memset(common.reserved, 0, sizeof(common.reserved));
    }
    // Implement the methods that sp<android_native_buffer_t> expects so that it
    // can be used to automatically refcount android_native_buffer_t's.
    void incStrong(const void* id) const {
        common.incRef(const_cast<android_native_base_t*>(&common));
    }
    void decStrong(const void* id) const {
        common.decRef(const_cast<android_native_base_t*>(&common));
    }
#endif
    struct android_native_base_t common;
    int width;
    int height;
    int stride;
    int format;
    int usage;
    /* transformation as defined in hardware.h */
    uint8_t transform;
    uint8_t reserved_bytes[3];
    void* reserved[1];
    buffer_handle_t handle;
    void* reserved_proc[8];
} android_native_buffer_t;
#define ANativeWindowBuffer android_native_buffer_t

#endif // end of NATIVE_BUFFER_H
