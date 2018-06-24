#ifndef FOLDER_MONITOR_H
#define FOLDER_MONITOR_H
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <thread>
#include "..\Singleton\Singleton.h"

namespace Lib
{
	/*** フォルダー配下の変更を監視するクラス */
	class FolderMonitor
	{
	public:
		enum struct MODIFY_TYPE
		{
			ADD,		//!< ファイル追加
			REMOVE,
			SAVE,
			RENAME_OLD,
			RENAME_NEW,
			OTHER
		};

		FolderMonitor() : m_IsOpen(false) {};

		~FolderMonitor() { if (m_IsOpen) Stop(); };

		bool AddChangeFunc(std::string _filePath, std::function<void(MODIFY_TYPE _modifyType)> _pFunc);

		/**
		 * @param[in] _folderPath 変更を監視する
		 * @param[in] _isSubDirectory 下層のフォルダも監視するか? 
		 * @param[in] 
 		 */
		bool Start(std::string _folderPath, bool _isSubDirectory);

		void Stop();

	private:
		/*** 別スレッド用関数 */
		void Loop(bool _isSubDirectory);

		using FileChangeFunc = std::unordered_map<std::string, std::function<void(MODIFY_TYPE _modifyType)>>;

		/*** ファイルが変更された時に呼ばれる関数 */
		FileChangeFunc m_FileChangeFunc;
		std::string    m_FolderPath;
		std::thread*   m_pThread;
		bool		   m_IsOpen;
		HANDLE		   m_hDirectory;
		HANDLE		   m_hEvent;

	};
}


#endif
