/**
 * @file   NodeBase.h
 * @brief  NodeBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef NODEBASE_H
#define NODEBASE_H
#include <list>
#include <string>
#include <stdio.h>

namespace Lib
{
	class BehaviorTree;

	class NodeBase
	{
	public:
		enum SELECT_TYPE
		{
			PRIORITY_TYPE,
			SEQUENCE_TYPE,
			RANDOM_TYPE,
			NON_TYPE
		};

		NodeBase() {}

		NodeBase(const std::string& _nodeName, BehaviorTree* _pBehaviorTree, int _priority = 0) :
			m_NodeName(_nodeName),
			m_pBehaviorTree(_pBehaviorTree),
			m_Priority(_priority){}

		~NodeBase() {}

		void SetChildNode(NodeBase* _childNode)
		{
			m_pChildNodes.push_back(_childNode);
		}

		void SetSelectType(SELECT_TYPE _selectType)
		{
			m_SelectType = _selectType;
		}

		SELECT_TYPE GetSelectType()
		{
			return m_SelectType;
		}

		std::string GetNodeName()
		{
			return m_NodeName;
		}

		void SetPriority(int _priority)
		{
			m_Priority = _priority;
		}

		void Next();

		bool Action() 
		{
			printf("%s\n",m_NodeName.c_str());
			return true;
		}

		bool GetIsEnd()
		{
			return (m_pChildNodes.size() == 0);
		}

	private:
		struct NodeCmp
		{
			bool operator()(const NodeBase& _task1, NodeBase& _task2) const
			{
				return (_task1.m_Priority < _task2.m_Priority);
			}
			bool operator()(NodeBase* _task1, NodeBase* _task2) const
			{
				return (_task1->m_Priority < _task2->m_Priority);
			}
		};

		BehaviorTree*		 m_pBehaviorTree;
		std::list<NodeBase*> m_pChildNodes;
		SELECT_TYPE			 m_SelectType;
		std::string          m_NodeName;
		bool				 m_IsEnable;
		int					 m_Priority;
	};
}


#endif
