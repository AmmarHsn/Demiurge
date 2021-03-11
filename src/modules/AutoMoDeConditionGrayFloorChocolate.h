/**
  * @file <src/modules/AutoMoDeConditionGrayFloorChocolate.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_GRAY_FLOOR_CHOCOLATE_H
#define AUTOMODE_CONDITION_GRAY_FLOOR_CHOCOLATE_H

#include "AutoMoDeCondition.h"

namespace argos {
	class AutoMoDeConditionGrayFloorChocolate: public AutoMoDeCondition {
		public:
			AutoMoDeConditionGrayFloorChocolate();
			virtual ~AutoMoDeConditionGrayFloorChocolate();

			AutoMoDeConditionGrayFloorChocolate(AutoMoDeConditionGrayFloorChocolate* pc_condition);
			virtual AutoMoDeConditionGrayFloorChocolate* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			CRange<Real> m_fGroundThresholdRange;
			Real m_fProbability;
	};
}

#endif
