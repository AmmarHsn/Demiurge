/**
  * @file <src/modules/AutoMoDeBehaviourRepulsionColor.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_GOAWAY_COLOR_H
#define AUTOMODE_BEHAVIOUR_GOAWAY_COLOR_H

#include "AutoMoDeBehaviour.h"

namespace argos {
    class AutoMoDeBehaviourGoAwayColor3Dot0: public AutoMoDeBehaviour {
		public:
            AutoMoDeBehaviourGoAwayColor3Dot0();
            AutoMoDeBehaviourGoAwayColor3Dot0(AutoMoDeBehaviourGoAwayColor3Dot0* pc_behaviour);
            virtual ~AutoMoDeBehaviourGoAwayColor3Dot0();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

            virtual AutoMoDeBehaviourGoAwayColor3Dot0* Clone();

		private:
            CColor m_cColorEmiterParameter;
            CColor m_cColorReceiverParameter;
            Real m_unRepulsionParameter;
	};
}


#endif
