package webp;

class WebpInfo {
	public var width:Int;
	public var height:Int;
	public var hasAlpha:Bool;
	public var bitstreamVersion:Int;
	public var noIncrementalDecoding:Int;
	public var rotate:Int;
	public var uvSampling:Int;
	
	public function new() {
	}
	
	public function toString():String {
		return Std.format(
			"WebpInfo(size(${width}x${height}),alpha:${hasAlpha},bitstreamVersion:${bitstreamVersion},noIncrementalDecoding:${noIncrementalDecoding},rotate:${rotate},uvSampling:${uvSampling})"
		);
	}
}