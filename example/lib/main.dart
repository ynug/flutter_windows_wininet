import 'dart:io';

import 'package:flutter/material.dart';
import 'dart:async';

import 'package:flutter_windows_wininet/flutter_windows_wininet.dart';
import 'package:http/http.dart' as http;

const List<String> hosts = [
  'valid.rootca1.demo.amazontrust.com',
  'valid.rootca2.demo.amazontrust.com',
  'valid.rootca3.demo.amazontrust.com',
  'valid.rootca4.demo.amazontrust.com',
  'valid.sfg2.demo.amazontrust.com'
];

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  final flutterWindowsWininetPlugin = FlutterWindowsWininet();
  for (var host in hosts) {
    // If you comment out this, the root certificate will not be obtained in advance at startup.
    final resultCode = await flutterWindowsWininetPlugin.requestWinnet(host);
    debugPrint("response: requestWinnet : $host, resultCode : $resultCode");
  }

  debugPrint("After this runApp is called");
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  @override
  void initState() {
    super.initState();
    getData();
  }

  Future<void> getData() async {
    for (var host in hosts) {
      try {
        var uri = Uri.https(host);
        var response = await http.get(uri);
        debugPrint("host : $host, ${response.statusCode}");

      } on HandshakeException catch (handshakeException) {
        var osErrorMessage = handshakeException.osError?.message ?? '';
        if (osErrorMessage.contains('CERTIFICATE_VERIFY_FAILED')) {
          debugPrint("HandshakeException: CERTIFICATE_VERIFY_FAILED, host: $host");
        }
      } on Exception catch (exception) {
        debugPrint("Exception: ${exception.toString()}, host: $host");
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: const Center(
          child: Text('Please check the console log to confirm the operation.\n'),
        ),
      ),
    );
  }
}
