/**
  * @file <src/modules/AutoMoDeConditionInvertedNeighborsCountChocolate.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_INVERTED_NEIGHBORS_COUNT_CHOCOLATE_H
#define AUTOMODE_CONDITION_INVERTED_NEIGHBORS_COUNT_CHOCOLATE_H

#include "AutoMoDeCondition.h"

namespace argos {
	class AutoMoDeConditionInvertedNeighborsCountChocolate: public AutoMoDeCondition {
		public:
			AutoMoDeConditionInvertedNeighborsCountChocolate();
			virtual ~AutoMoDeConditionInvertedNeighborsCountChocolate();

			AutoMoDeConditionInvertedNeighborsCountChocolate(AutoMoDeConditionInvertedNeighborsCountChocolate* pc_condition);
			virtual AutoMoDeConditionInvertedNeighborsCountChocolate* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fParameterEta;
			UInt8 m_unParameterXi;
	};
}

#endif
