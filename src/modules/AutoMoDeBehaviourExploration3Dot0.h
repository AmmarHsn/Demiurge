/**
  * @file <src/modules/AutoMoDeBehaviourExploration.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EXPLORATION_3DOT0_H
#define AUTOMODE_BEHAVIOUR_EXPLORATION_3DOT0_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourExploration3Dot0: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourExploration3Dot0();
			AutoMoDeBehaviourExploration3Dot0(AutoMoDeBehaviourExploration3Dot0* pc_behaviour);
			virtual ~AutoMoDeBehaviourExploration3Dot0();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourExploration3Dot0* Clone();

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
            CColor m_cColorEmiterParameter;

			bool IsObstacleInFront(CCI_EPuckProximitySensor::SReading s_prox_reading);

			bool is3Dot0;
	};
}

#endif