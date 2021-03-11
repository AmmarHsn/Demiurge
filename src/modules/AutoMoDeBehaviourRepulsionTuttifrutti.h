/**
  * @file <src/modules/AutoMoDeBehaviourRepulsion.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_REPULSION_TUTTIFRUTTI_H
#define AUTOMODE_BEHAVIOUR_REPULSION_TUTTIFRUTTI_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourRepulsionTuttifrutti: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourRepulsionTuttifrutti();
			AutoMoDeBehaviourRepulsionTuttifrutti(AutoMoDeBehaviourRepulsionTuttifrutti* pc_behaviour);
			virtual ~AutoMoDeBehaviourRepulsionTuttifrutti();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourRepulsionTuttifrutti* Clone();

			virtual bool Succeeded();
			virtual bool Failed();

		private:
			UInt8 m_unRepulsionParameter;
            CColor m_cColorEmiterParameter;
	};
}


#endif