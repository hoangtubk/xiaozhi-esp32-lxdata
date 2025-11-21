// image_to_jpeg.h - Efficient image to JPEG conversion for ESP32
#pragma once

#include "sdkconfig.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // ---- ESP32-friendly pixel formats ----
    // Values are arbitrary sequential IDs; callers should use these PIX_FMT_* constants.
    typedef enum
    {
        PIX_FMT_UNKNOWN = 0,
        PIX_FMT_GREY,    // grayscale (1 byte per pixel)
        PIX_FMT_YUYV,    // YUYV (Y Cb Y Cr) 4:2:2 packed
        PIX_FMT_UYVY,    // UYVY (Cb Y Cr Y) 4:2:2 packed
        PIX_FMT_YUV422P, // YUV422 planar
        PIX_FMT_RGB24,   // RGB888 (3 bytes per pixel)
        PIX_FMT_RGB565,  // RGB565 little-endian (2 bytes per pixel)
        PIX_FMT_RGB565X, // RGB565 big-endian/other variant
        PIX_FMT_RGB888,  // alias for RGB24
        PIX_FMT_JPEG,    // input already JPEG compressed
    } pixel_format_t;

    // Callback for chunked JPEG output
    typedef size_t (*jpg_out_cb)(void *arg, size_t index, const void *data, size_t len);

    /**
     * @brief Convert image to JPEG (full buffer output)
     */
    bool image_to_jpeg(uint8_t *src, size_t src_len,
                       uint16_t width, uint16_t height,
                       pixel_format_t format, uint8_t quality,
                       uint8_t **out, size_t *out_len);

    /**
     * @brief Convert image to JPEG using streaming callback
     */
    bool image_to_jpeg_cb(uint8_t *src, size_t src_len,
                          uint16_t width, uint16_t height,
                          pixel_format_t format, uint8_t quality,
                          jpg_out_cb cb, void *arg);

#ifdef __cplusplus
}
#endif
