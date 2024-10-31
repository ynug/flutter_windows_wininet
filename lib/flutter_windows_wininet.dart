
import 'flutter_windows_wininet_platform_interface.dart';

class FlutterWindowsWininet {
  Future<int?> requestWinnet(String host) {
    return FlutterWindowsWininetPlatform.instance.requestWinnet(host);
  }
}
