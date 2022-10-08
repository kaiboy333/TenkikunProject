#include "ScriptIcon.h"

ScriptIcon::ScriptIcon(float startX, float startY, float iconWidth, float iconHeight, float blankWidth, float blankHeight, std::string imageFileName, std::filesystem::path path) : FileIcon(startX, startY, iconWidth, iconHeight, blankWidth, blankHeight, imageFileName, path)
{
	//�C�x���g��ǉ�(�_�u���N���b�N��������)
	this->mouseDoubleClickEvents.push_back([this]() {
        // �N���������A�v���P�[�V�����̃t���p�X(���邢�̓J�����g�t�H���_�[����̑��΃p�X)�ƁA
            // �K�v�ɉ����Ĉ������󔒋�؂�ɂĕt������B
        //wchar_t commandLine[] = L"�A�v���P�[�V�����̃p�X�ƈ���";
        STARTUPINFO si{};
        PROCESS_INFORMATION pi{};

        si.cb = sizeof(si);

        // �R�}���h���C���̎��s(���������0�ȊO���߂�)
        std::string path = "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.exe";
        LPSTR commandLine = const_cast<char*>(path.c_str());
        if (CreateProcess(nullptr, commandLine, nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi))
        {
            // �N������
            //

            //// �A�v���P�[�V�����̏I���܂ő҂�
            //// (�҂����ɏ������ɐi�߂�ꍇ�AWaitForSingleObject��GetExitCodeProcess�͕s�v)
            //WaitForSingleObject(pi.hProcess, INFINITE);

            //// �A�v���P�[�V�����̏I���R�[�h�̎擾
            //// (�I���R�[�h���g�p���Ȃ��ꍇ�͕s�v)
            //unsigned long exitCode;
            //GetExitCodeProcess(pi.hProcess, &exitCode);

            //// �I���R�[�h�����̒l�ɂȂ�ꍇ������̂ŁAsigned�ɃL���X�g����
            //long ec = static_cast<long>(exitCode);

            // �n���h�������
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        else
        {
            // �N�����s
            //
        }
        });
}
