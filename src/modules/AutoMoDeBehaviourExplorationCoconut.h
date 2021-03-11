/**
  * @file <src/modules/AutoMoDeBehaviourExplorationCoconut.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EXPLORATION_COCONUT_H
#define AUTOMODE_BEHAVIOUR_EXPLORATION_COCONUT_H

#include "AutoMoDeBehaviour.h"

namespace argos
{
	class AutoMoDeBehaviourExplorationCoconut : public AutoMoDeBehaviour
	{
	public:
		AutoMoDeBehaviourExplorationCoconut();
		AutoMoDeBehaviourExplorationCoconut(AutoMoDeBehaviourExplorationCoconut *pc_behaviour);
		virtual ~AutoMoDeBehaviourExplorationCoconut();

		virtual void ControlStep();
		virtual void Reset();
		virtual void ResumeStep();
		virtual void Init();

		virtual AutoMoDeBehaviourExplorationCoconut *Clone();

		virtual bool Succeeded();
		virtual bool Failed();
	};
} // namespace argos

#endif
