/**
  * @file <src/modules/AutoMoDeBehaviourAttractionColor.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_GOTO_COLOR_H
#define AUTOMODE_BEHAVIOUR_GOTO_COLOR_H

#include "AutoMoDeBehaviour.h"

namespace argos {
    class AutoMoDeBehaviourGoToColorTuttifrutti: public AutoMoDeBehaviour {
		public:
            AutoMoDeBehaviourGoToColorTuttifrutti();
            AutoMoDeBehaviourGoToColorTuttifrutti(AutoMoDeBehaviourGoToColorTuttifrutti* pc_behaviour);
            virtual ~AutoMoDeBehaviourGoToColorTuttifrutti();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

            virtual AutoMoDeBehaviourGoToColorTuttifrutti* Clone();

            virtual bool Succeeded();
			      virtual bool Failed();

        private:
            Real m_fDistanceWeightParameter;
            CColor m_cColorEmiterParameter;
            CColor m_cColorReceiverParameter;
            Real m_unAttractionParameter;
	};
}

#endif
