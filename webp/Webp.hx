package webp;
import haxe.io.Bytes;
import haxe.io.BytesData;
import flash.utils.ByteArray;
import flash.display.BitmapData;
import flash.errors.Error;
import flash.geom.Rectangle;

class Webp {
	/**
	 * Obtains the string version of the decoder
	 * 
	 * @example Webp.getDecoderVersion() == "0.2.0"
	 * 
	 * @return string
	 */
	static public function getDecoderVersion():String {
		return webp_get_decoder_version();
	}

	/**
	 * Obtains the string version of the encoder
	 * 
	 * @example Webp.getEncoderVersion() == "0.2.0"
	 * 
	 * @return string
	 */
	static public function getEncoderVersion():String {
		return webp_get_encoder_version();
	}

	/**
	 * Obtains information about a webp image.
	 * 
	 * @param  bytes     Webp bytes
	 * 
	 * @return Information about the image
	 */
	static public function getImageInfo(bytes:ByteArray):WebpInfo {
		var infoArray = webp_get_info(_byteArrayToBytes(bytes).getData());
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

	/**
	 * Decodes a webp image and returns a BitmapData with the image.
	 * 
	 * @param  bytes    Webp bytes
	 * 
	 * @return BitmapData with the image
	 */
	static public function decodeAsBitmapData(bytes:ByteArray):BitmapData {
		return _decode(webp_decode_argb(_byteArrayToBytes(bytes).getData()));
	}

	/**
	 * Encodes a BitmapData image into a webp image and returns it as a ByteArray.
	 * 
	 * @param   bitmapData       Image to encode
	 * @param   lossless         Wether to perform a lossless compression or not
	 * @param   quality_factor   Quality of the encoded image 0-100
	 * 
	 * @return  ByteArray with the image encoded as Webp
	 */
	static public function encodeBitmapData(bitmapData:BitmapData, lossless:Bool = false, quality_factor:Float = 86):ByteArray {
		var input_bytes:Bytes = bitmapData.getPixels(bitmapData.rect);
		return _bytesToByteArray(Bytes.ofData(webp_encode_argb(input_bytes.getData(), bitmapData.width, bitmapData.height, lossless, quality_factor)));
	}

	static private function _byteArrayToBytes(byteArray:ByteArray):Bytes {
		return byteArray;
	}
	
	static private function _bytesToByteArray(bytes:Bytes):ByteArray {
		return ByteArray.fromBytes(bytes);
	}

	static private function _decode(arr:Array<Dynamic>):BitmapData {
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