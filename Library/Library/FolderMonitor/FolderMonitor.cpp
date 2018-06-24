#include "FolderMonitor.h"
#include "..\Utility\Utility.h"


namespace Lib
{
	bool FolderMonitor::AddChangeFunc(
		std::string _filePath, 
		std::function<void(MODIFY_TYPE _modifyType)> _pFunc)
	{
		if (m_FileChangeFunc.count(_filePath) == 0)
		{
			m_FileChangeFunc[_filePath] = _pFunc;
			return true;
		}

		return false;
	}


	bool FolderMonitor::Start(std::string _folderPath, bool _isSubDirectory)
	{
		if (m_IsOpen) return false;

		m_FolderPath = _folderPath;
		m_pThread = new std::thread([&]() 
		{  
			Loop(_isSubDirectory);
		});
		return true;

	}

	void FolderMonitor::Stop()
	{
		m_IsOpen = false;
		// 同期IO終了
		CancelSynchronousIo(m_hDirectory);
	
		CloseHandle(m_hEvent);
		CloseHandle(m_hDirectory);

		m_pThread->join();
		Lib::SafeDelete(m_pThread);
	}

	void FolderMonitor::Loop(bool _isSubDirectory)
	{
		setlocale(LC_ALL, "");

		m_hDirectory = CreateFile(
			m_FolderPath.c_str(),
			FILE_LIST_DIRECTORY,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
			NULL);

		if (m_hDirectory == INVALID_HANDLE_VALUE)
		{
			MyOutputDebugString("CreateFile Failed\n");
		}

		// 監視条件 (FindFirstChangeNotificationと同じ)
		DWORD filter =
			FILE_NOTIFY_CHANGE_FILE_NAME |  // ファイル名の変更
			FILE_NOTIFY_CHANGE_DIR_NAME |  // ディレクトリ名の変更
			FILE_NOTIFY_CHANGE_ATTRIBUTES |  // 属性の変更
			FILE_NOTIFY_CHANGE_SIZE |  // サイズの変更
			FILE_NOTIFY_CHANGE_LAST_WRITE;    // 最終書き込み日時の変更

		size_t bufSize = 1024 * 8;
		std::vector<BYTE> buf(bufSize);

		void* pBuf = &buf[0];

		m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		DWORD oldAction = 0;

		m_IsOpen = true;

		while (m_IsOpen)
		{
			ResetEvent(m_hEvent);

			OVERLAPPED overLapped = { 0 };
			overLapped.hEvent = m_hEvent;

			if (!ReadDirectoryChangesW(
				m_hDirectory,
				pBuf,
				bufSize,
				_isSubDirectory,
				filter,
				NULL,
				&overLapped,
				NULL))
			{
				MyOutputDebugString("ReadDirectoryChangesW Failed\n");
				break;
			}

			DWORD retsize = 0;

			if (!GetOverlappedResult(m_hDirectory, &overLapped, &retsize, TRUE))
			{
				if (GetLastError() != ERROR_IO_INCOMPLETE)
				{
					break;
				}
			}


			if (retsize != 0)
			{
				FILE_NOTIFY_INFORMATION* pData = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(pBuf);

				size_t offset = 0;
				MODIFY_TYPE modifyType = MODIFY_TYPE::OTHER;
				for (;;)
				{
					// アクションタイプを可読文字に変換
					switch (pData->Action) {
					case FILE_ACTION_ADDED:
						modifyType = MODIFY_TYPE::ADD;
						break;
					case FILE_ACTION_REMOVED:
						modifyType = MODIFY_TYPE::REMOVE;
						break;
					case FILE_ACTION_MODIFIED:
						modifyType = MODIFY_TYPE::SAVE;
						break;
					case FILE_ACTION_RENAMED_OLD_NAME:
						modifyType = MODIFY_TYPE::RENAME_OLD;
						break;
					case FILE_ACTION_RENAMED_NEW_NAME:
						modifyType = MODIFY_TYPE::RENAME_NEW;
						break;
					}
					if (oldAction == pData->Action)
					{
						oldAction = 0;
						break;
					}

					DWORD lenBytes = pData->FileNameLength;
					std::vector<WCHAR> fileName(lenBytes / sizeof(WCHAR) + 1); // ヌル終端用に+1
					memcpy(&fileName[0], pData->FileName, lenBytes);

					char file[64] = { "" };

					size_t rettest;
					wcstombs_s(&rettest, file, 64, &fileName[0], lenBytes);

					if (m_FileChangeFunc.count(file) != 0)
					{
						m_FileChangeFunc[file](modifyType);
					}

					oldAction = pData->Action;

					if (pData->NextEntryOffset == 0) break;

					pData = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(
						reinterpret_cast<unsigned char*>(pData) + pData->NextEntryOffset);
				}
			}
		}
	}
}