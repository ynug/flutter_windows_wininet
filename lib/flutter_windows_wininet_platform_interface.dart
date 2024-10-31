import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'flutter_windows_wininet_method_channel.dart';

abstract class FlutterWindowsWininetPlatform extends PlatformInterface {
  /// Constructs a FlutterWindowsWininetPlatform.
  FlutterWindowsWininetPlatform() : super(token: _token);

  static final Object _token = Object();

  static FlutterWindowsWininetPlatform _instance = MethodChannelFlutterWindowsWininet();

  /// The default instance of [FlutterWindowsWininetPlatform] to use.
  ///
  /// Defaults to [MethodChannelFlutterWindowsWininet].
  static FlutterWindowsWininetPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [FlutterWindowsWininetPlatform] when
  /// they register themselves.
  static set instance(FlutterWindowsWininetPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<int?> requestWinnet(String host) {
    throw UnimplementedError('requestWinnet(String host) has not been implemented.');
  }
}
