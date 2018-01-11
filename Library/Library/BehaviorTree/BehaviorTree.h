/**
 * @file   BehaviorTree.h
 * @brief  BehaviorTree�N���X�̃w�b�_�t�@�C��
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
		 * ���[�g�m�[�h�𐶐����z���̑I�����[����ݒ肷��
		 * @param[in] _selectType �I�����[��
		 * @return ���łɐ�������Ă�����true ����Ă��Ȃ�������false
		 */
		bool Initialize(NodeBase::SELECT_TYPE _selectType);
		
		/**
		 * ���[�g�̔z���Ƀm�[�h���Z�b�g���z���̑I�����[����ݒ肷��
		 * @param[in] _nodeName �m�[�h�̖��O
		 * @param[in] _selectType �I�����[��
		 * @return ���łɃZ�b�g����Ă�����true ����Ă��Ȃ�������false
		 */
		bool SetNode(
			const std::string& _childNodeName,
			NodeBase::SELECT_TYPE _selectType);

		/**
		 * �m�[�h���Z�b�g���z���̑I�����[����ݒ肷��
		 * @param[in] _parentNodeName �e�m�[�h�̖��O
		 * @param[in] _childNodeName �q�m�[�h�̖��O
		 * @param[in] _selectType �I�����[��
		 * @return ���łɃZ�b�g����Ă�����true ����Ă��Ȃ�������false
		 */
		bool SetNode(
			const std::string& _parentNodeName, 
			const std::string& _childNodeName, 
			NodeBase::SELECT_TYPE _selectType);

		/*** ���s */
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
		NodeBase*						m_pRunActionNode; //!< ���s����Ă���A�N�V�����̃m�[�h
		std::list<NodeBase*>			m_pSequenceNodes; //!< ���s�����̃V�[�P���X�m�[�h
	};
}


#endif
