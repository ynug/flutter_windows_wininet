import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_windows_wininet/flutter_windows_wininet.dart';
import 'package:flutter_windows_wininet/flutter_windows_wininet_platform_interface.dart';
import 'package:flutter_windows_wininet/flutter_windows_wininet_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockFlutterWindowsWininetPlatform
    with MockPlatformInterfaceMixin
    implements FlutterWindowsWininetPlatform {

  @override
  Future<int?> requestWinnet(String host) => Future.value(0);
}

void main() {
  final FlutterWindowsWininetPlatform initialPlatform = FlutterWindowsWininetPlatform.instance;

  test('$MethodChannelFlutterWindowsWininet is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelFlutterWindowsWininet>());
  });

  test('requestWinnet', () async {
    FlutterWindowsWininet flutterWindowsWininetPlugin = FlutterWindowsWininet();
    MockFlutterWindowsWininetPlatform fakePlatform = MockFlutterWindowsWininetPlatform();
    FlutterWindowsWininetPlatform.instance = fakePlatform;

    expect(await flutterWindowsWininetPlugin.requestWinnet(''), 0);
  });
}
