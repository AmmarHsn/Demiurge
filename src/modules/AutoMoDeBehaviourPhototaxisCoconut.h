/**
  * @file <src/modules/AutoMoDeBehaviourPhototaxisCoconut.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_PHOTOTAXIS_COCONUT_H
#define AUTOMODE_BEHAVIOUR_PHOTOTAXIS_COCONUT_H

#include "AutoMoDeBehaviour.h"

namespace argos
{
	class AutoMoDeBehaviourPhototaxisCoconut : public AutoMoDeBehaviour
	{
	public:
		AutoMoDeBehaviourPhototaxisCoconut();
		AutoMoDeBehaviourPhototaxisCoconut(AutoMoDeBehaviourPhototaxisCoconut *pc_behaviour);
		virtual ~AutoMoDeBehaviourPhototaxisCoconut();

		virtual void ControlStep();
		virtual void Reset();
		virtual void ResumeStep();
		virtual void Init();

		virtual AutoMoDeBehaviourPhototaxisCoconut *Clone();
	};
} // namespace argos

#endif
