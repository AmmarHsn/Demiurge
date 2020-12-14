/**
  * @file <src/modules/AutoMoDeBehaviourAntiPhototaxisCoconut.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_ANTI_PHOTOTAXIS_COCONUT_H
#define AUTOMODE_BEHAVIOUR_ANTI_PHOTOTAXIS_COCONUT_H

#include "AutoMoDeBehaviour.h"

namespace argos
{
	class AutoMoDeBehaviourAntiPhototaxisCoconut : public AutoMoDeBehaviour
	{
	public:
		AutoMoDeBehaviourAntiPhototaxisCoconut();
		AutoMoDeBehaviourAntiPhototaxisCoconut(AutoMoDeBehaviourAntiPhototaxisCoconut *pc_behaviour);
		virtual ~AutoMoDeBehaviourAntiPhototaxisCoconut();

		virtual void ControlStep();
		virtual void Reset();
		virtual void ResumeStep();
		virtual void Init();

		virtual AutoMoDeBehaviourAntiPhototaxisCoconut *Clone();
	};
} // namespace argos

#endif
