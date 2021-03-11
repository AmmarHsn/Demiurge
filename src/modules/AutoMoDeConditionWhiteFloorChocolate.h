/**
  * @file <src/modules/AutoMoDeConditionInvertedWhiteFloor.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */
	
#ifndef AUTOMODE_CONDITION_WHITE_FLOOR_CHOCOLATE_H
#define AUTOMODE_CONDITION_WHITE_FLOOR_CHOCOLATE_H

#include "AutoMoDeCondition.h"

namespace argos {
	class AutoMoDeConditionWhiteFloorChocolate: public AutoMoDeCondition {
		public:
			AutoMoDeConditionWhiteFloorChocolate();
			virtual ~AutoMoDeConditionWhiteFloorChocolate();

			AutoMoDeConditionWhiteFloorChocolate(AutoMoDeConditionWhiteFloorChocolate* pc_condition);
			virtual AutoMoDeConditionWhiteFloorChocolate* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fGroundThreshold;
			Real m_fProbability;
	};
}

#endif
