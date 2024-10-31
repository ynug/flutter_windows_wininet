import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'flutter_windows_wininet_platform_interface.dart';

/// An implementation of [FlutterWindowsWininetPlatform] that uses method channels.
class MethodChannelFlutterWindowsWininet extends FlutterWindowsWininetPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_windows_wininet');

  @override
  Future<int?> requestWinnet(String host) async {
    final returnCode = await methodChannel.invokeMethod<int>('requestWinnet', host);
    return returnCode;
  }
}
