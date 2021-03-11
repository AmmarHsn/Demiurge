/**
  * @file <src/modules/AutoMoDeBehaviourStopChocolate.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */


#ifndef AUTOMODE_BEHAVIOUR_STOP_CHOCOLATE_H
#define AUTOMODE_BEHAVIOUR_STOP_CHOCOLATE_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourStopChocolate: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourStopChocolate();
			AutoMoDeBehaviourStopChocolate(AutoMoDeBehaviourStopChocolate* pc_behaviour);
			virtual ~AutoMoDeBehaviourStopChocolate();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();


			virtual AutoMoDeBehaviourStopChocolate* Clone();

			virtual bool Succeeded();
			virtual bool Failed();
	};
}


#endif
