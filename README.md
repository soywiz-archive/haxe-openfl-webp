## WEBP:

Information about webp:
* https://developers.google.com/speed/webp/
* http://code.google.com/p/webp/

## Setup/Installing:

You need HAXE and NME. http://www.haxenme.org/

```
haxelib install nme-webp
```

## Usage/API:

The Webp API is pretty simple. It uses ByteArray and BitmapData objects for encoding/decoding.

```actionscript
webp.Webp.getDecoderVersion():String
webp.Webp.getEncoderVersion():String
webp.Webp.getImageInfo(bytes:ByteArray):WebpInfo;
webp.Webp.decodeAsBitmapData(bytes:ByteArray):BitmapData;
webp.Webp.encodeBitmapData(bitmapData:BitmapData, lossless:Bool = false, quality_factor:Float = 86):ByteArray
```

## Simple Example:

You can obtain webp data using Assets.getBytes or sys.io.File functions (available on cpp and neko targets).

```actionscript
var bytes:ByteArray = nme.Assets.getBytes("image.webp");
var bitmapData:BitmapData = webp.Webp.decodeAsBitmapData(bytes);
var bitmap:Bitmap = new Bitmap(bitmapData);
addChild(bitmap);
```