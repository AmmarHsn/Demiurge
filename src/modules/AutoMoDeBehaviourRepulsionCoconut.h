/**
  * @file <src/modules/AutoMoDeBehaviourRepulsionCoconut.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_REPULSION_COCONUT_H
#define AUTOMODE_BEHAVIOUR_REPULSION_COCONUT_H

#include "AutoMoDeBehaviour.h"

namespace argos
{
	class AutoMoDeBehaviourRepulsionCoconut : public AutoMoDeBehaviour
	{
	public:
		AutoMoDeBehaviourRepulsionCoconut();
		AutoMoDeBehaviourRepulsionCoconut(AutoMoDeBehaviourRepulsionCoconut *pc_behaviour);
		virtual ~AutoMoDeBehaviourRepulsionCoconut();

		virtual void ControlStep();
		virtual void Reset();
		virtual void ResumeStep();
		virtual void Init();

		virtual AutoMoDeBehaviourRepulsionCoconut *Clone();

	private:
		UInt8 m_unRepulsionParameter;
	};
} // namespace argos

#endif
