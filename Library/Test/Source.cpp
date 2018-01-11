#include "BehaviorTree\BehaviorTree.h"
//#include "BehaviorTree\NodeBase.h"
#include <algorithm>
#include <iterator>
#include <random>

void main()
{
	Lib::BehaviorTree test;
	test.Initialize(Lib::NodeBase::SEQUENCE_TYPE);
	test.SetNode("UŒ‚", Lib::NodeBase::SEQUENCE_TYPE);
	test.SetNode("UŒ‚", "•¨—", Lib::NodeBase::SEQUENCE_TYPE);
	test.SetNode("UŒ‚", "–‚–@", Lib::NodeBase::RANDOM_TYPE);
	test.SetNode("–‚–@", "‰Î", Lib::NodeBase::SEQUENCE_TYPE);
	test.SetNode("–‚–@", "…", Lib::NodeBase::SEQUENCE_TYPE);
	test.SetNode("–‚–@", "•X", Lib::NodeBase::SEQUENCE_TYPE);

	test.SetNode("–hŒä", Lib::NodeBase::SEQUENCE_TYPE);
	
	test.Run();
	test.Run();
	test.Run();
	test.Run();
	test.Run();
	test.Run();


	getchar();
}