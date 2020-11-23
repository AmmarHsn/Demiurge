/**
  * @file <src/modules/AutoMoDeBehaviourRepulsion.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_REPULSION_3DOT0_H
#define AUTOMODE_BEHAVIOUR_REPULSION_3DOT0_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourRepulsion3Dot0: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourRepulsion3Dot0();
			AutoMoDeBehaviourRepulsion3Dot0(AutoMoDeBehaviourRepulsion3Dot0* pc_behaviour);
			virtual ~AutoMoDeBehaviourRepulsion3Dot0();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourRepulsion3Dot0* Clone();

		private:
			UInt8 m_unRepulsionParameter;
            CColor m_cColorEmiterParameter;
	};
}


#endif