#include "ScriptIcon.h"

ScriptIcon::ScriptIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::string imageFileName, std::filesystem::path path) : FileIcon(startX, startY, iconWidth, iconHeight, blankWidth, blankHeight, imageFileName, path)
{
	//イベントを追加(ダブルクリックをしたら)
	this->mouseDoubleClickEvents.push_back([this]() {
        // 起動したいアプリケーションのフルパス(あるいはカレントフォルダーからの相対パス)と、
            // 必要に応じて引数も空白区切りにて付加する。
        //wchar_t commandLine[] = L"アプリケーションのパスと引数";
        STARTUPINFO si{};
        PROCESS_INFORMATION pi{};

        si.cb = sizeof(si);

        // コマンドラインの実行(成功すると0以外が戻る)
        std::string path = "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.exe";
        LPSTR commandLine = const_cast<char*>(path.c_str());
        if (CreateProcess(nullptr, commandLine, nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi))
        {
            // 起動成功
            //

            //// アプリケーションの終了まで待つ
            //// (待たずに処理を先に進める場合、WaitForSingleObjectとGetExitCodeProcessは不要)
            //WaitForSingleObject(pi.hProcess, INFINITE);

            //// アプリケーションの終了コードの取得
            //// (終了コードを使用しない場合は不要)
            //unsigned long exitCode;
            //GetExitCodeProcess(pi.hProcess, &exitCode);

            //// 終了コードが負の値になる場合もあるので、signedにキャストする
            //long ec = static_cast<long>(exitCode);

            // ハンドルを閉じる
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        else
        {
            // 起動失敗
            //
        }
        });
}
