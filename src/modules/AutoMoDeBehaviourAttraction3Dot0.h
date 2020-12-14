/**
  * @file <src/modules/AutoMoDeBehaviourAttraction.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_ATTRACTION_3DOT0_H
#define AUTOMODE_BEHAVIOUR_ATTRACTION_3DOT0_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourAttraction3Dot0: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourAttraction3Dot0();
			AutoMoDeBehaviourAttraction3Dot0(AutoMoDeBehaviourAttraction3Dot0* pc_behaviour);
			virtual ~AutoMoDeBehaviourAttraction3Dot0();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourAttraction3Dot0* Clone();

		private:
			UInt8 m_unAttractionParameter;
            CColor m_cColorEmiterParameter;

	};
}

#endif