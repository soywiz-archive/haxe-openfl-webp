Setup/Installing:

```
haxelib install nme-webp
```

Usage/API:

```haxe
webp.Webp.getDecoderVersion():String
webp.Webp.getEncoderVersion():String
webp.Webp.getImageInfo(bytes:ByteArray):WebpInfo;
webp.Webp.decodeAsBitmapData(bytes:ByteArray):BitmapData;
webp.Webp.encodeBitmapData(bitmapData:BitmapData, lossless:Bool = false, quality_factor:Float = 86):ByteArray
```

Example:

```haxe
var bytes:ByteArray = nme.Assets.getBytes("image.webp");
var bitmapData:BitmapData = webp.Webp.decodeAsBitmapData(bytes);
var bitmap:Bitmap = new Bitmap(bitmapData);
addChild(bitmap);
```