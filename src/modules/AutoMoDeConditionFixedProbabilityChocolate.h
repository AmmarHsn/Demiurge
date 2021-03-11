/**
  * @file <src/modules/AutoMoDeConditionFixedProbabilityChocolate.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_FIXED_PROBABILITY_CHOCOLATE_H
#define AUTOMODE_CONDITION_FIXED_PROBABILITY_CHOCOLATE_H

#include "AutoMoDeCondition.h"

namespace argos {
	class AutoMoDeConditionFixedProbabilityChocolate: public AutoMoDeCondition {
		public:
			AutoMoDeConditionFixedProbabilityChocolate();
			virtual ~AutoMoDeConditionFixedProbabilityChocolate();

			AutoMoDeConditionFixedProbabilityChocolate(AutoMoDeConditionFixedProbabilityChocolate* pc_condition);
			virtual AutoMoDeConditionFixedProbabilityChocolate* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fProbability;
	};
}

#endif
