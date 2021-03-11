/**
  * @file <src/modules/AutoMoDeBehaviourExplorationChocolate.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EXPLORATION_CHOCOLATE_H
#define AUTOMODE_BEHAVIOUR_EXPLORATION_CHOCOLATE_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourExplorationChocolate: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourExplorationChocolate();
			AutoMoDeBehaviourExplorationChocolate(AutoMoDeBehaviourExplorationChocolate* pc_behaviour);
			virtual ~AutoMoDeBehaviourExplorationChocolate();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourExplorationChocolate* Clone();

			virtual bool Succeeded();
			virtual bool Failed();

		private:
			SInt32 m_unTurnSteps;

			enum ExplorationState {
				RANDOM_WALK,
				OBSTACLE_AVOIDANCE
			};

			enum TurnDirection {
				LEFT,
				RIGHT
			};

			ExplorationState m_eExplorationState;
			TurnDirection m_eTurnDirection;

			Real m_fProximityThreshold;
			CRange<UInt32> m_cRandomStepsRange;

			bool IsObstacleInFront(CCI_EPuckProximitySensor::SReading s_prox_reading);
	};
}

#endif
