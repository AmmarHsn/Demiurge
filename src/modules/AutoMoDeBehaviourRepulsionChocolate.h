/**
  * @file <src/modules/AutoMoDeBehaviourRepulsionChocolate.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_REPULSION_CHOCOLATE_H
#define AUTOMODE_BEHAVIOUR_REPULSION_CHOCOLATE_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourRepulsionChocolate: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourRepulsionChocolate();
			AutoMoDeBehaviourRepulsionChocolate(AutoMoDeBehaviourRepulsionChocolate* pc_behaviour);
			virtual ~AutoMoDeBehaviourRepulsionChocolate();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourRepulsionChocolate* Clone();

			virtual bool Succeeded();
			virtual bool Failed();

		private:
			UInt8 m_unRepulsionParameter;
	};
}


#endif
