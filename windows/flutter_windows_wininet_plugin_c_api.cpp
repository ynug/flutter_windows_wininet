#include "include/flutter_windows_wininet/flutter_windows_wininet_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "flutter_windows_wininet_plugin.h"

void FlutterWindowsWininetPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_windows_wininet::FlutterWindowsWininetPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
