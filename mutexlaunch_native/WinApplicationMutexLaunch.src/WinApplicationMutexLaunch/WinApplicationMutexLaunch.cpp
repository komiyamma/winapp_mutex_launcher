/*
* Copyright (c) 2017 Akitsugu Komiyama
* under the MITLicense
*/

#include <windows.h>
#include <shlwapi.h>
#include <tchar.h>
#include <vector>
#include <string>


#pragma comment(lib, "shlwapi.lib")

using namespace std;

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// [�������g] [�^�[�Q�b�g�v���O�����̃t���p�X] [�^�[�Q�b�g�̃E�B���h�E�N���X] [���̃v���O�����ւ̎c��̈���]
	if (__argc < 3) {
		return -1;
	}

	vector<string> args_list;
	string joined_args_list = "";

	// �v���O�����p�X�ȊO�̈�������B
	if (__argc > 3) {
		for (int c = 3; c < __argc; c++) {
			string elem = "\"" + string(__argv[c]) + "\"";
			// �_�u���N�H�[�e�[�V�����ň݂͂Ȃ���W�߂�
			args_list.push_back(elem);
			joined_args_list += " " + elem;
		}
	}

	char *szTargetExeFullPath = __argv[1];
	char *szTargetWndClassName = __argv[2];
	char szTargetDirName[256] = "";
	strcpy(szTargetDirName, szTargetExeFullPath);
	::PathRemoveFileSpecA(szTargetDirName);

	// FindWindow�́A�Ώۂ̃E�B���h�E�N���X����������ꍇ�ɂ́AZ�I�[�_�[����ԏ�̂��̂��E��
	HWND hWndHandle = FindWindowA(szTargetWndClassName, NULL);

	// SHIFT�L�[�������Ă��邩�A�Ώۂ̃A�v���������オ���Ă��Ȃ��Ȃ�Υ��
	if (GetKeyState(VK_SHIFT) < 0 || !hWndHandle) {

		// �J�����g�f�B���N�g���ύX
		SetCurrentDirectoryA(szTargetDirName);

		// �N��
		ShellExecuteA(NULL, "open", szTargetExeFullPath, joined_args_list.data(), NULL, SW_SHOWNORMAL);

	}
	else {

		// �����A�C�R�������Ă����猳�ɖ߂�
		if (IsIconic(hWndHandle)) {

			// ���ɖ߂�
			OpenIcon(hWndHandle);
		}

		// ���ꂪ�A�N�e�B�u��!!
		SetForegroundWindow(hWndHandle);
	}

	return 0;
}