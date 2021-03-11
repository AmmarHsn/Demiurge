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
    class AutoMoDeBehaviourGoAwayColorTuttifrutti: public AutoMoDeBehaviour {
		public:
            AutoMoDeBehaviourGoAwayColorTuttifrutti();
            AutoMoDeBehaviourGoAwayColorTuttifrutti(AutoMoDeBehaviourGoAwayColorTuttifrutti* pc_behaviour);
            virtual ~AutoMoDeBehaviourGoAwayColorTuttifrutti();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

            virtual AutoMoDeBehaviourGoAwayColorTuttifrutti* Clone();

            virtual bool Succeeded();
			      virtual bool Failed();

		private:
            CColor m_cColorEmiterParameter;
            CColor m_cColorReceiverParameter;
            Real m_unRepulsionParameter;
	};
}


#endif
