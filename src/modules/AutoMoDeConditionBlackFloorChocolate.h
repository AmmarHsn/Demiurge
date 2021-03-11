/**
  * @file <src/modules/AutoMoDeConditionBlackFloorChocolate.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_BLACK_FLOOR_CHOCOLATE_H
#define AUTOMODE_CONDITION_BLACK_FLOOR_CHOCOLATE_H

#include "AutoMoDeCondition.h"

namespace argos {
	class AutoMoDeConditionBlackFloorChocolate: public AutoMoDeCondition {
		public:
			AutoMoDeConditionBlackFloorChocolate();
			virtual ~AutoMoDeConditionBlackFloorChocolate();

			AutoMoDeConditionBlackFloorChocolate(AutoMoDeConditionBlackFloorChocolate* pc_condition);
			virtual AutoMoDeConditionBlackFloorChocolate* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fGroundThreshold;
			Real m_fProbability;
	};
}

#endif
