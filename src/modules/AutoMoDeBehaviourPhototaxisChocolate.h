/**
  * @file <src/modules/AutoMoDeBehaviourPhototaxisChocolate.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_PHOTOTAXIS_CHOCOLATE_H
#define AUTOMODE_BEHAVIOUR_PHOTOTAXIS_CHOCOLATE_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourPhototaxisChocolate: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourPhototaxisChocolate();
			AutoMoDeBehaviourPhototaxisChocolate(AutoMoDeBehaviourPhototaxisChocolate* pc_behaviour);
			virtual ~AutoMoDeBehaviourPhototaxisChocolate();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourPhototaxisChocolate* Clone();

			virtual bool Succeeded();
			virtual bool Failed();
	};
}

#endif
