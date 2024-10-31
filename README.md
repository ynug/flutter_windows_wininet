# flutter_windows_wininet

Windowsの[WinINet](https://learn.microsoft.com/ja-jp/windows/win32/wininet/about-wininet)を利用してAPI通信を行う  
通信を行うのみで、レスポンスデータを返す仕様では無い。

## 開発目的

Windowsの通信APIは、ローカルに信頼できるルート証明書がなくても、非同期で`Microsoft Trusted Root Certificate Program`を参照してルート証明書を手に入れて通信が可能である。  
しかし、Flutterの`http`パッケージには非同期取得機能がないため、Windowsにルート証明書が無いと、証明書の検証エラーで通信が失敗してしまう。

そこで、Flutterアプリが起動する前に、Windowsの通信APIを使って、アプリがアクセスしているホストすべてに事前に通信して、必要やルート証明書を取得する。

## 開発環境

Flutter 3.22.1 
