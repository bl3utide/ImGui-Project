# ImGui Project (for Visual Studio)
C++ Project template using SDL2 and ImGui in Visual Studio

## Dependencies (Latest version)
- [SDL 2.0.10](https://github.com/libsdl-org/SDL/tree/release-2.0.10)
- [ImGui 1.87 w/ docking](https://github.com/ocornut/imgui/tree/1ee252772ae9c0a971d06257bb5c89f628fa696a)
- [plog 1.1.10](https://github.com/SergiusTheBest/plog/tree/1.1.10)
- [mINI 0.9.15](https://github.com/metayeti/mINI/tree/0.9.15)

## Changelog

### v0.3.1
- c++20 に対応
- 開発環境を Visual Studio 2022 に移行
- 全体的な動作の安定性を強化
- ログ機能を強化
- 外部ライブラリをサブモジュールとして直接取り込むように変更

### v0.3.0
- パラメータを設定ファイル (.ini) に保存する機能を追加

### v0.2.4
- VERSIONINFO リソースを追加
- デバッグログのファイルが正常に出力されるように修正

### v0.2.3
- string_util.hpp はプリコンパイル済みヘッダーに含まれるようになった
- Font モジュールを GUI モジュールから切り離した
- Gui::initialize がアプリケーションのメタ情報を受け取るように変更し、メインヘッダーは他のモジュールから参照されなくなった
- GUI (デバッグ) モジュールを Gui::Debug 名前空間の中に移動させた

### v0.2.2
- 依存するライブラリをサブモジュールとして追加
- メインプロジェクトのプロジェクト名を `App` に変更
- メインプロジェクトのソースファイルおよびヘッダーファイルを snake_case に統一
  - ソリューションファイル (.sln) 、プロジェクトファイル (.vcxproj) 等のファイル名はこれまで通り UpperCamelCase とする

### v0.2.1
- メインプロジェクトの src をインクルードディレクトリとして追加
- 同じカテゴリのソースファイルをサブディレクトリに移動
- 出力される実行ファイルをソリューション名に変更(デフォルトは ImGuiProject.exe)
- GUI のカラー定義用のソースファイルを追加

### v0.2.0
- 依存するライブラリをソリューションディレクトリに格納
- アプリケーションのベース名前空間の名称をソリューション名(リポジトリ名)と統一
- メインのプロジェクトの名前を Application に変更
- State モジュールと Error モジュールを Main モジュールから独立

### v0.1.1
- SDL ライブラリをソースからコンパイルするように変更
