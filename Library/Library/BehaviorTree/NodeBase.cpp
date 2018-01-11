 /**
  * @file   NodeBase.cpp
  * @brief  NodeBaseƒNƒ‰ƒX‚ÌŽÀ‘•
  * @author kotani
  */
#include "..\stdafx.h"
#include "NodeBase.h"
#include "BehaviorTree.h"

#include <algorithm>
#include <iterator>
#include <random>

namespace Lib
{
	void NodeBase::Next()
	{
		if (GetIsEnd())
		{
			m_pBehaviorTree->SetRunActionNode(this);
			return;
		}

		switch (m_SelectType)
		{
		case PRIORITY_TYPE:
		{
			m_pChildNodes.sort(NodeCmp());
			auto pChildNode = m_pChildNodes.front();
			pChildNode->Next();
		}
			break;
		case SEQUENCE_TYPE:
		{
			for (auto itr = m_pChildNodes.rbegin(), end = m_pChildNodes.rend(); itr != end; ++itr) 
			{
				if (*itr != m_pChildNodes.front())
					m_pBehaviorTree->SetSequenceNode(*itr);
			}
			auto pChildNode = m_pChildNodes.front();
			pChildNode->Next();
		}
			break;
		case RANDOM_TYPE:
		{
			std::random_device RandomDevice;
			std::mt19937 RandomGenerator(RandomDevice());
			std::uniform_int_distribution<int> RandomDistribution(0, m_pChildNodes.size()-1);
			auto pChildNode = *std::next(m_pChildNodes.begin(), RandomDistribution(RandomGenerator));
			pChildNode->Next();
		}
			break;
		default:
			break;
		}
	}
}
