/**
  * @file <src/modules/AutoMoDeBehaviourStopTuttifrutti3Dot0.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_STOP_TUTTIFRUTTI_H
#define AUTOMODE_BEHAVIOUR_STOP_TUTTIFRUTTI_H

#include "AutoMoDeBehaviour.h"

namespace argos
{
	class AutoMoDeBehaviourStopTuttifrutti : public AutoMoDeBehaviour
	{
	public:
		AutoMoDeBehaviourStopTuttifrutti();
		AutoMoDeBehaviourStopTuttifrutti(AutoMoDeBehaviourStopTuttifrutti *pc_behaviour);
		virtual ~AutoMoDeBehaviourStopTuttifrutti();

		virtual void ControlStep();
		virtual void Reset();
		virtual void ResumeStep();
		virtual void Init();

		virtual AutoMoDeBehaviourStopTuttifrutti *Clone();

		virtual bool Succeeded();
		virtual bool Failed();

	private:
		CColor m_cColorEmiterParameter;
	};
} // namespace argos

#endif
