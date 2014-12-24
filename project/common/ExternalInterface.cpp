#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif

#include <hx/CFFI.h>

#include "../webp/webp/decode.h"
#include "../webp/webp/encode.h"
#include <string.h>
#include <stdio.h>

#define DEFINE_FUNC(COUNT, NAME, ...) value NAME(__VA_ARGS__); DEFINE_PRIM(NAME, COUNT); value NAME(__VA_ARGS__)
#define DEFINE_FUNC_0(NAME) DEFINE_FUNC(0, NAME)
#define DEFINE_FUNC_1(NAME, PARAM1) DEFINE_FUNC(1, NAME, value PARAM1)
#define DEFINE_FUNC_2(NAME, PARAM1, PARAM2) DEFINE_FUNC(2, NAME, value PARAM1, value PARAM2)
#define DEFINE_FUNC_3(NAME, PARAM1, PARAM2, PARAM3) DEFINE_FUNC(3, NAME, value PARAM1, value PARAM2, value PARAM3)
#define DEFINE_FUNC_4(NAME, PARAM1, PARAM2, PARAM3, PARAM4) DEFINE_FUNC(4, NAME, value PARAM1, value PARAM2, value PARAM3, value PARAM4)
#define DEFINE_FUNC_5(NAME, PARAM1, PARAM2, PARAM3, PARAM4, PARAM5) DEFINE_FUNC(5, NAME, value PARAM1, value PARAM2, value PARAM3, value PARAM4, value PARAM5)

#ifdef HX_WINDOWS
#define snprintf _snprintf
#endif

extern "C" {
	DEFINE_FUNC_0(webp_get_decoder_version) {
		//alloc_string
		char temp[16];
		int ver = WebPGetDecoderVersion();
		snprintf(temp, sizeof(temp), "%d.%d.%d", (ver >> 16) & 0xFF, (ver >> 8) & 0xFF, (ver >> 0) & 0xFF);
		return alloc_string(temp);
	}
	
	DEFINE_FUNC_0(webp_get_encoder_version) {
		//alloc_string
		char temp[16];
		int ver = WebPGetEncoderVersion();
		snprintf(temp, sizeof(temp), "%d.%d.%d", (ver >> 16) & 0xFF, (ver >> 8) & 0xFF, (ver >> 0) & 0xFF);
		return alloc_string(temp);
	}

	DEFINE_FUNC_1(webp_get_features, data_buffer_value) {
		if (!val_is_buffer(data_buffer_value)) {
			val_throw(alloc_string("webp_get_features: Expected to be a buffer"));
			return alloc_null();
		}
		buffer data_buffer = val_to_buffer(data_buffer_value);
		int    data_len = buffer_size(data_buffer);
		char  *data_ptr = buffer_data(data_buffer);
		
		WebPBitstreamFeatures features = {0};
		VP8StatusCode code = WebPGetFeatures((const unsigned char *)data_ptr, data_len, &features);
		
		if (code != VP8_STATUS_OK) {
			val_throw(alloc_string("webp_get_features: Error: (code != VP8_STATUS_OK)"));
			return alloc_null();
		}

		value array = alloc_array(7);
		val_array_set_i(array, 0, alloc_int(features.width));
		val_array_set_i(array, 1, alloc_int(features.height));
		val_array_set_i(array, 2, alloc_int(features.has_alpha));
		//val_array_set_i(array, 3, alloc_int(features.bitstream_version));
		val_array_set_i(array, 3, alloc_int(0));
		val_array_set_i(array, 4, alloc_int(features.no_incremental_decoding));
		val_array_set_i(array, 5, alloc_int(features.rotate));
		val_array_set_i(array, 6, alloc_int(features.uv_sampling));
		return array;
	}
	
	DEFINE_FUNC_1(webp_decode_argb, data_buffer_value) {
		if (!val_is_buffer(data_buffer_value)) {
			val_throw(alloc_string("webp_decode_argb: Expected to be a buffer"));
			return alloc_null();
		}
		buffer data_buffer = val_to_buffer(data_buffer_value);
		int    data_len = buffer_size(data_buffer);
		char  *data_ptr = buffer_data(data_buffer);
		int webp_width = -1, webp_height = -1;
		char *webp_data_ptr = (char *)WebPDecodeARGB((const unsigned char *)data_ptr, data_len, &webp_width, &webp_height);
		int webp_data_len = webp_width * webp_height * 4;
		
		if (webp_data_ptr == NULL) {
			val_throw(alloc_string("webp_decode_argb: Invalid webp data"));
			return alloc_null();
		}
		
		buffer webp_buffer = alloc_buffer_len(0);
		buffer_append_sub(webp_buffer, webp_data_ptr, webp_data_len);
		buffer_set_size(webp_buffer, webp_data_len);

		value array = alloc_array(3);
		val_array_set_i(array, 0, alloc_int(webp_width));
		val_array_set_i(array, 1, alloc_int(webp_height));
		val_array_set_i(array, 2, buffer_val(webp_buffer));
		
		if (webp_data_ptr != NULL) free(webp_data_ptr);
		
		return array;
	}

	DEFINE_FUNC_5(webp_encode_argb, data_buffer_value, width_value, height_value, lossless_value, quality_factor_value) {
		int width = 0;
		int height = 0;
		float quality_factor = 100;
		int lossless = 1;
		int stride = 0;
		uint8_t* abgr = NULL;
		uint8_t* rgba = NULL;
		uint8_t* output = NULL;
		int output_size = 0;
		int pixels_size;
		int bytes_size;
		buffer data_buffer;
		
		if (val_is_int(width_value)) width = val_int(width_value);
		if (val_is_int(height_value)) height = val_int(height_value);
		if (val_is_bool(lossless_value)) lossless = val_bool(lossless_value);
		if (val_is_float(quality_factor_value)) quality_factor = val_float(quality_factor_value);

		stride = width * 4;
		pixels_size = width * height;
		bytes_size = pixels_size * 4;
		
		if (!val_is_buffer(data_buffer_value)) {
			val_throw(alloc_string("webp_encode_argb: Expected to be a buffer"));
			return alloc_null();
		}
		
		data_buffer = val_to_buffer(data_buffer_value);
		
		if (bytes_size != buffer_size(data_buffer)) {
			val_throw(alloc_string("webp_encode_argb: Invalid buffer size"));
			return alloc_null();
		}
		
		//if ()
		
		abgr = (uint8_t *)buffer_data(data_buffer);
		rgba = (uint8_t *)malloc(bytes_size);
		
		uint8_t* _abgr = abgr;
		uint8_t* _rgba = rgba;
		int _pixels_size = pixels_size;
		
		while (_pixels_size-- > 0) {
			//_rgba[0] = _abgr[3];
			_rgba[0] = _abgr[1];
			_rgba[1] = _abgr[2];
			_rgba[2] = _abgr[3];
			_rgba[3] = _abgr[0];
			_abgr += 4;
			_rgba += 4;
		}

		if (lossless) {
			output_size = WebPEncodeLosslessRGBA(
				rgba,
				//abgr,
				width, height, stride,
				&output
			);
		} else {
			output_size = WebPEncodeRGBA(
				rgba,
				//abgr,
				width, height, stride,
				quality_factor,
				&output
			);
		}
		
		printf("output_size: (%d, %d, %d) : %d\n", width, height, stride, output_size);

		buffer output_buffer = alloc_buffer_len(0);
		buffer_append_sub(output_buffer, (char *)output, output_size);
		buffer_set_size(output_buffer, output_size);

		if (output != NULL) free(output);
		if (rgba != NULL) free(rgba);
		
		return buffer_val(output_buffer);
	}	
}
