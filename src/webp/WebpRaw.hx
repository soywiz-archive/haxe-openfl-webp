package webp;

#if neko
import neko.Lib;
#elseif cpp
import cpp.Lib;
#end

class WebpRaw {
	static public var webp_get_decoder_version = Lib.load("openfl-webp", "webp_get_decoder_version", 0);
	static public var webp_get_encoder_version = Lib.load("openfl-webp", "webp_get_encoder_version", 0);
	static public var webp_get_info = Lib.load("openfl-webp", "webp_get_features", 1);
	static public var webp_decode_argb = Lib.load("openfl-webp", "webp_decode_argb", 1);
	static public var webp_encode_argb = Lib.load("openfl-webp", "webp_encode_argb", 5);
}