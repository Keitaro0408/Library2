#include "BehaviorTree\BehaviorTree.h"
//#include "BehaviorTree\NodeBase.h"
#include <algorithm>
#include <iterator>
#include <random>

void main()
{
	Lib::BehaviorTree test;
	test.Initialize(Lib::NodeBase::SEQUENCE_TYPE);
	test.SetNode("�U��", Lib::NodeBase::SEQUENCE_TYPE);
	test.SetNode("�U��", "����", Lib::NodeBase::SEQUENCE_TYPE);
	test.SetNode("�U��", "���@", Lib::NodeBase::RANDOM_TYPE);
	test.SetNode("���@", "��", Lib::NodeBase::SEQUENCE_TYPE);
	test.SetNode("���@", "��", Lib::NodeBase::SEQUENCE_TYPE);
	test.SetNode("���@", "�X", Lib::NodeBase::SEQUENCE_TYPE);

	test.SetNode("�h��", Lib::NodeBase::SEQUENCE_TYPE);
	
	test.Run();
	test.Run();
	test.Run();
	test.Run();
	test.Run();
	test.Run();


	getchar();
}