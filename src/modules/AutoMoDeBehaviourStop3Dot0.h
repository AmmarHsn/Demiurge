/**
  * @file <src/modules/AutoMoDeBehaviourStop3Dot03Dot0.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_STOP_3DOT0_H
#define AUTOMODE_BEHAVIOUR_STOP_3DOT0_H

#include "AutoMoDeBehaviour.h"

namespace argos
{
	class AutoMoDeBehaviourStop3Dot0 : public AutoMoDeBehaviour
	{
	public:
		AutoMoDeBehaviourStop3Dot0();
		AutoMoDeBehaviourStop3Dot0(AutoMoDeBehaviourStop3Dot0 *pc_behaviour);
		virtual ~AutoMoDeBehaviourStop3Dot0();

		virtual void ControlStep();
		virtual void Reset();
		virtual void ResumeStep();
		virtual void Init();

		virtual AutoMoDeBehaviourStop3Dot0 *Clone();

	private:
		CColor m_cColorEmiterParameter;
		bool is3Dot0;
	};
} // namespace argos

#endif
