#ifndef FLUTTER_PLUGIN_FLUTTER_WINDOWS_WININET_PLUGIN_H_
#define FLUTTER_PLUGIN_FLUTTER_WINDOWS_WININET_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace flutter_windows_wininet {

class FlutterWindowsWininetPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  FlutterWindowsWininetPlugin();

  virtual ~FlutterWindowsWininetPlugin();

  // Disallow copy and assign.
  FlutterWindowsWininetPlugin(const FlutterWindowsWininetPlugin&) = delete;
  FlutterWindowsWininetPlugin& operator=(const FlutterWindowsWininetPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

private:
    int FlutterWindowsWininetPlugin::requestWinnet(const std::string& host);
    std::wstring FlutterWindowsWininetPlugin::stringToWstring(const std::string& str);
};

}  // namespace flutter_windows_wininet

#endif  // FLUTTER_PLUGIN_FLUTTER_WINDOWS_WININET_PLUGIN_H_
