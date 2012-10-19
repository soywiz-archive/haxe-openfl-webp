#ifndef IPHONE
#define IMPLEMENT_API
#endif

//#include <hx/CFFI.h>

//#include <Object.h>

#include <hxcpp.h>
//#include <hx/Macros.h>
#include <hx/CFFI.h>
//#include <hx/CFFIAPI.h>
#include <hxcpp.h>
#include "../webp/webp/decode.h"
#include <string.h>
#include <stdio.h>

#define DEFINE_FUNC(COUNT, NAME, ...) value NAME(__VA_ARGS__); DEFINE_PRIM(NAME, COUNT); value NAME(__VA_ARGS__)
#define DEFINE_FUNC_0(NAME) DEFINE_FUNC(0, NAME)
#define DEFINE_FUNC_1(NAME, PARAM1) DEFINE_FUNC(1, NAME, value PARAM1)
#define DEFINE_FUNC_2(NAME, PARAM1, PARAM2) DEFINE_FUNC(2, NAME, value PARAM1, value PARAM2)
#define DEFINE_FUNC_3(NAME, PARAM1, PARAM2, PARAM3) DEFINE_FUNC(3, NAME, value PARAM1, value PARAM2, value PARAM3)

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
// Include neko glue....
#define NEKO_COMPATIBLE
#endif

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

	DEFINE_FUNC_1(webp_get_info, data) {
		if (!val_is_buffer(data)) {
			val_throw(alloc_string("Expected to be a buffer"));
			return alloc_null();
		}
		buffer data_buffer = val_to_buffer(data);
		int    data_len = buffer_size(data_buffer);
		char  *data_ptr = buffer_data(data_buffer);
		int webp_width = -1, webp_height = -1;
		if (!WebPGetInfo((const unsigned char *)data_ptr, data_len, &webp_width, &webp_height)) {
			val_throw(alloc_string("Invalid webp data"));
			return alloc_null();
		}

		value array = alloc_array(2);
		val_array_set_i(array, 0, alloc_int(webp_width));
		val_array_set_i(array, 1, alloc_int(webp_height));
		return array;
	}
	
	DEFINE_FUNC_1(webp_decode_argb, data) {
		if (!val_is_buffer(data)) {
			val_throw(alloc_string("Expected to be a buffer"));
			return alloc_null();
		}
		buffer data_buffer = val_to_buffer(data);
		int    data_len = buffer_size(data_buffer);
		char  *data_ptr = buffer_data(data_buffer);
		int webp_width = -1, webp_height = -1;
		char *webp_data_ptr = (char *)WebPDecodeARGB((const unsigned char *)data_ptr, data_len, &webp_width, &webp_height);
		int webp_data_len = webp_width * webp_height * 4;
		
		if (webp_data_ptr == NULL) {
			val_throw(alloc_string("Invalid webp data"));
			return alloc_null();
		}
		
		buffer webp_buffer = alloc_buffer_len(0);
		buffer_append_sub(webp_buffer, webp_data_ptr, webp_data_len);
		buffer_set_size(webp_buffer, webp_data_len);

		value array = alloc_array(3);
		val_array_set_i(array, 0, alloc_int(webp_width));
		val_array_set_i(array, 1, alloc_int(webp_height));
		val_array_set_i(array, 2, buffer_val(webp_buffer));
		return array;
	}
}