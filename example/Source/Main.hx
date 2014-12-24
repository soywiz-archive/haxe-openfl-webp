package;

import flash.display.Bitmap;
import flash.display.BitmapData;
import flash.display.Sprite;
import flash.media.Sound;
import flash.utils.ByteArray;
import haxe.io.Bytes;
import haxe.Timer;
import webp.Webp;
import openfl.Assets;

class Main extends Sprite {
	
	
	public function new () {
		
		super ();

		trace('started!');
		trace(Webp.getDecoderVersion());
		trace(Webp.getEncoderVersion());
		
		//var bitmap:Bitmap = new Bitmap (Assets.getBitmapData ("assets/openfl.png"));
		var byteArray:ByteArray = Assets.getBytes("assets/texture.webp");
		var bitmap:Bitmap;
		Timer.measure(function():Dynamic {
			bitmap = new Bitmap (Webp.decodeAsBitmapData(byteArray));
			return false;
		});
		addChild(bitmap);
		
		bitmap.x = (stage.stageWidth - bitmap.width) / 2;
		bitmap.y = (stage.stageHeight - bitmap.height) / 2;
	}
}