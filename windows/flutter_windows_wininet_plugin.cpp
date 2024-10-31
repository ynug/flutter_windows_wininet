#include "flutter_windows_wininet_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

#include <string>

#include <wininet.h>
#pragma comment(lib, "wininet.lib")

namespace flutter_windows_wininet {

// static
void FlutterWindowsWininetPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "flutter_windows_wininet",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<FlutterWindowsWininetPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

FlutterWindowsWininetPlugin::FlutterWindowsWininetPlugin() {}

FlutterWindowsWininetPlugin::~FlutterWindowsWininetPlugin() {}

void FlutterWindowsWininetPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("requestWinnet") == 0) {
    const std::string* host = std::get_if<std::string>(method_call.arguments());
//    std::cout << "call method name : requestWinnet, host: " << *host << std::endl;
    int resultCode = requestWinnet(*host);
    result->Success(flutter::EncodableValue(resultCode));
  } else {
    result->NotImplemented();
  }
}

int FlutterWindowsWininetPlugin::requestWinnet(const std::string& host) {
  std::string url = "https://" + host;
//  std::cout << "Access URL: " << url << std::endl;

  std::wstring lwrl = stringToWstring(url);
  // Initializing the WinINet API
  HINTERNET hInternet = InternetOpenW(L"WinINet", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
  if (!hInternet) {
//    std::cerr << "InternetOpen failed. Error: " << GetLastError() << std::endl;
    return 1;
  }

  HINTERNET hConnect = InternetOpenUrlW(hInternet, lwrl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE, 0);
  if (!hConnect) {
//    std::cerr << "InternetOpenUrl failed. Error: " << GetLastError() << std::endl;
    InternetCloseHandle(hInternet);
    return 2;
  }

  int resultCode = 0;

  DWORD statusCode = 0;
  DWORD statusCodeSize = sizeof(statusCode);
  if (HttpQueryInfoW(hConnect, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &statusCode, &statusCodeSize, NULL)) {
//    if (statusCode == 200) {
//      std::cout << "HTTP response is 200 (OK)." << std::endl;
//    } else {
//      std::cout << "HTTP response code: " << statusCode << std::endl;
//    }
  } else {
    resultCode = 3;
//    DWORD error = GetLastError();
//    std::cerr << "HttpQueryInfo failed. Error: " << error << std::endl;
//
//    LPVOID errorMsg;
//    FormatMessageW(
//            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//            NULL,
//            error,
//            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//            (LPWSTR)&errorMsg,
//            0, NULL);
//    std::cerr << "Error message: " << (LPSTR)errorMsg << std::endl;
//    LocalFree(errorMsg);
  }

  InternetCloseHandle(hConnect);
  InternetCloseHandle(hInternet);

  return resultCode;
}

std::wstring FlutterWindowsWininetPlugin::stringToWstring(const std::string& str) {
  int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
  std::wstring wstr(size_needed, 0);
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
  return wstr;
}

}  // namespace flutter_windows_wininet
