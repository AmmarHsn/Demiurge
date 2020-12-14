/**
  * @file <src/modules/AutoMoDeBehaviourAttraction.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_ATTRACTION_TUTTIFRUTTI_H
#define AUTOMODE_BEHAVIOUR_ATTRACTION_TUTTIFRUTTI_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourAttractionTuttifrutti: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourAttractionTuttifrutti();
			AutoMoDeBehaviourAttractionTuttifrutti(AutoMoDeBehaviourAttractionTuttifrutti* pc_behaviour);
			virtual ~AutoMoDeBehaviourAttractionTuttifrutti();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourAttractionTuttifrutti* Clone();

		private:
			UInt8 m_unAttractionParameter;
            CColor m_cColorEmiterParameter;

	};
}

#endif