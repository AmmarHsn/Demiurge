/**
  * @file <src/modules/AutoMoDeConditionNeighborsCountChocolate.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_NEIGHBORS_COUNT_CHOCOLATE_H
#define AUTOMODE_CONDITION_NEIGHBORS_COUNT_CHOCOLATE_H

#include "AutoMoDeCondition.h"

namespace argos {
	class AutoMoDeConditionNeighborsCountChocolate: public AutoMoDeCondition {
		public:
			AutoMoDeConditionNeighborsCountChocolate();
			virtual ~AutoMoDeConditionNeighborsCountChocolate();

			AutoMoDeConditionNeighborsCountChocolate(AutoMoDeConditionNeighborsCountChocolate* pc_condition);
			virtual AutoMoDeConditionNeighborsCountChocolate* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fParameterEta;
			UInt8 m_unParameterXi;
	};
}

#endif
