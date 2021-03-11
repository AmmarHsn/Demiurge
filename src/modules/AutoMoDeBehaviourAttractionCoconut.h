/**
  * @file <src/modules/AutoMoDeBehaviourAttractionCoconut.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_ATTRACTION_COCONUT_H
#define AUTOMODE_BEHAVIOUR_ATTRACTION_COCONUT_H

#include "AutoMoDeBehaviour.h"

namespace argos
{
	class AutoMoDeBehaviourAttractionCoconut : public AutoMoDeBehaviour
	{
	public:
		AutoMoDeBehaviourAttractionCoconut();
		AutoMoDeBehaviourAttractionCoconut(AutoMoDeBehaviourAttractionCoconut *pc_behaviour);
		virtual ~AutoMoDeBehaviourAttractionCoconut();

		virtual void ControlStep();
		virtual void Reset();
		virtual void ResumeStep();
		virtual void Init();

		virtual AutoMoDeBehaviourAttractionCoconut *Clone();

		virtual bool Succeeded();
		virtual bool Failed();

	private:
		UInt8 m_unAttractionParameter;
	};
} // namespace argos

#endif
