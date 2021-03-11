/**
  * @file <src/modules/AutoMoDeBehaviourAttractionChocolate.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_ATTRACTION_CHOCOLATE_H
#define AUTOMODE_BEHAVIOUR_ATTRACTION_CHOCOLATE_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourAttractionChocolate: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourAttractionChocolate();
			AutoMoDeBehaviourAttractionChocolate(AutoMoDeBehaviourAttractionChocolate* pc_behaviour);
			virtual ~AutoMoDeBehaviourAttractionChocolate();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourAttractionChocolate* Clone();

			virtual bool Succeeded();
			virtual bool Failed();

		private:
			UInt8 m_unAttractionParameter;
	};
}

#endif
