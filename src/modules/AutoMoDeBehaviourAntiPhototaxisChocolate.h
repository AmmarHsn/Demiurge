/**
  * @file <src/modules/AutoMoDeBehaviourAntiPhototaxisChocolate.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_ANTI_PHOTOTAXIS_CHOCOLATE_H
#define AUTOMODE_BEHAVIOUR_ANTI_PHOTOTAXIS_CHOCOLATE_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourAntiPhototaxisChocolate: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourAntiPhototaxisChocolate();
			AutoMoDeBehaviourAntiPhototaxisChocolate(AutoMoDeBehaviourAntiPhototaxisChocolate* pc_behaviour);
			virtual ~AutoMoDeBehaviourAntiPhototaxisChocolate();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourAntiPhototaxisChocolate* Clone();

			virtual bool Succeeded();
			virtual bool Failed();
	};
}

#endif
