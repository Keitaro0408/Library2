 /**
  * @file   BehaviorTree.cpp
  * @brief  BehaviorTreeƒNƒ‰ƒX‚ÌŽÀ‘•
  * @author kotani
  */
#include "..\stdafx.h"
#include "BehaviorTree.h"

namespace Lib
{
	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	bool BehaviorTree::Initialize(NodeBase::SELECT_TYPE _selectType)
	{
		if (m_pNodes.find("Root") == m_pNodes.end())
		{
			m_pNodes["Root"] = NodeBase("Root", this);
			m_pNodes["Root"].SetSelectType(_selectType);
			return true;
		}

		return false;
	}

	bool BehaviorTree::SetNode(const std::string& _nodeName, NodeBase::SELECT_TYPE _selectType)
	{
		if (m_pNodes.find(_nodeName) == m_pNodes.end())
		{
			m_pNodes[_nodeName] = NodeBase(_nodeName, this);

			m_pNodes["Root"].SetChildNode(&m_pNodes[_nodeName]);
			m_pNodes[_nodeName].SetSelectType(_selectType);
			return true;
		}

		return false;
	}

	bool BehaviorTree::SetNode(const std::string& _parentNodeName, const std::string& _childNodeName, NodeBase::SELECT_TYPE _selectType)
	{
		if (m_pNodes.find(_parentNodeName) != m_pNodes.end() &&
			m_pNodes.find(_childNodeName) == m_pNodes.end())
		{
			m_pNodes[_childNodeName] = NodeBase(_childNodeName, this);
			m_pNodes[_parentNodeName].SetChildNode(&m_pNodes[_childNodeName]);
			m_pNodes[_childNodeName].SetSelectType(_selectType);
			return true;
		}

		return false;
	}

	void BehaviorTree::Run()
	{
		if (m_pRunActionNode == nullptr)
		{
			m_pNodes["Root"].Next();
		}

		if (m_pRunActionNode->Action())
		{
			if (m_pSequenceNodes.size() != 0)
			{
				m_pRunActionNode = m_pSequenceNodes.back();
				m_pSequenceNodes.pop_back();
				m_pRunActionNode->Next();
			}
			else
			{
				m_pRunActionNode = nullptr;
			}
		}
	}

}
