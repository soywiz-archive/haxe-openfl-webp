package webp;
import haxe.io.Bytes;
import haxe.io.BytesData;
import nme.utils.ByteArray;
import nme.display.BitmapData;
import nme.errors.Error;
import nme.geom.Rectangle;

class Webp {
	public static function getDecoderVersion():String {
		return webp_get_decoder_version();
	}

	public static function getEncoderVersion():String {
		return webp_get_encoder_version();
	}

	public static function getImageInfo(bytes:Bytes):WebpInfo {
		var infoArray = webp_get_info(bytes.getData());
		var info:WebpInfo = new WebpInfo();
		
		info.width = infoArray[0];
		info.height = infoArray[1];
		info.hasAlpha = (infoArray[2] != 0);
		info.bitstreamVersion = infoArray[3];
		info.noIncrementalDecoding = infoArray[4];
		info.rotate = infoArray[5];
		info.uvSampling = infoArray[6];

		return info;
	}

	public static function decodeAsBitmapData(bytes:Bytes):BitmapData {
		return _decode(webp_decode_argb(bytes.getData()));
	}
	
	public static function encodeBitmapData(bitmapData:BitmapData, lossless:Bool = false, quality_factor:Float = 86):Bytes {
		var input_bytes:Bytes = bitmapData.getPixels(bitmapData.rect);
		return Bytes.ofData(webp_encode_argb(input_bytes.getData(), bitmapData.width, bitmapData.height, lossless, quality_factor));
	}
	
	private static function _decode(arr:Array<Dynamic>):BitmapData {
		var width:Int = cast(arr[0]);
		var height:Int = cast(arr[1]);
		var bytes:Bytes = Bytes.ofData(cast(arr[2]));
		if (width <= 0 || height <= 0) throw(new Error("Invalid webp size"));
		if (bytes.length != width * height * 4) throw(new Error("Invalid webp size"));
		var bitmapData:BitmapData = new BitmapData(width, height);
		bitmapData.setPixels(bitmapData.rect, ByteArray.fromBytes(bytes));
		return bitmapData;
	}
	
	static var webp_get_decoder_version = cpp.Lib.load("nme-webp", "webp_get_decoder_version", 0);
	static var webp_get_encoder_version = cpp.Lib.load("nme-webp", "webp_get_encoder_version", 0);
	static var webp_get_info = cpp.Lib.load("nme-webp", "webp_get_features", 1);
	static var webp_decode_argb = cpp.Lib.load("nme-webp", "webp_decode_argb", 1);
	static var webp_encode_argb = cpp.Lib.load("nme-webp", "webp_encode_argb", 5);
	
}