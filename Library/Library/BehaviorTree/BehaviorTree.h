/**
 * @file   BehaviorTree.h
 * @brief  BehaviorTreeクラスのヘッダファイル
 * @author kotani
 */
#ifndef BEHAVIORTREE_H
#define BEHAVIORTREE_H
#include "NodeBase.h"
#include <string>
#include <map>

namespace Lib
{
	class BehaviorTree
	{
	public:
		BehaviorTree() {};
		~BehaviorTree() {};

		/**
		 * ルートノードを生成し配下の選択ルールを設定する
		 * @param[in] _selectType 選択ルール
		 * @return すでに生成されていたらtrue されていなかったらfalse
		 */
		bool Initialize(NodeBase::SELECT_TYPE _selectType);
		
		/**
		 * ルートの配下にノードをセットし配下の選択ルールを設定する
		 * @param[in] _nodeName ノードの名前
		 * @param[in] _selectType 選択ルール
		 * @return すでにセットされていたらtrue されていなかったらfalse
		 */
		bool SetNode(
			const std::string& _childNodeName,
			NodeBase::SELECT_TYPE _selectType);

		/**
		 * ノードをセットし配下の選択ルールを設定する
		 * @param[in] _parentNodeName 親ノードの名前
		 * @param[in] _childNodeName 子ノードの名前
		 * @param[in] _selectType 選択ルール
		 * @return すでにセットされていたらtrue されていなかったらfalse
		 */
		bool SetNode(
			const std::string& _parentNodeName, 
			const std::string& _childNodeName, 
			NodeBase::SELECT_TYPE _selectType);

		/*** 実行 */
		void Run();

		void SetSequenceNode(NodeBase* _pNode)
		{
			m_pSequenceNodes.push_back(_pNode);
		}

		void SetRunActionNode(NodeBase* _pNode)
		{
			m_pRunActionNode = _pNode;
		}

		NodeBase* GetNode(std::string _nodeName)
		{
			if(m_pNodes.find(_nodeName) == m_pNodes.end())
				return nullptr;
			else
				return &m_pNodes[_nodeName];
		}

	private:
		std::map<std::string,NodeBase>  m_pNodes;
		NodeBase*						m_pRunActionNode; //!< 実行されているアクションのノード
		std::list<NodeBase*>			m_pSequenceNodes; //!< 実行されるのシーケンスノード
	};
}


#endif
