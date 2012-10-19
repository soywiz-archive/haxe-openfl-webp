package webp;
import haxe.io.Bytes;
import haxe.io.BytesData;
import neash.utils.ByteArray;
import nme.display.BitmapData;
import nme.errors.Error;
import nme.geom.Point;

class Decoder {
	public static function getDecoderVersion():String {
		return webp_get_decoder_version();
	}

	public static function getInfo(data:Bytes):Array<Int> {
		var arr = webp_get_info(data.getData());
		return arr;
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

	public static function decodeAsBitmapData(data:Bytes):BitmapData {
		return _decode(webp_decode_argb(data.getData()));
	}
	
	static var webp_get_decoder_version = cpp.Lib.load("nme-webp", "webp_get_decoder_version", 0);
	static var webp_get_info = cpp.Lib.load("nme-webp", "webp_get_info", 1);
	static var webp_decode_argb = cpp.Lib.load("nme-webp", "webp_decode_argb", 1);
	
}