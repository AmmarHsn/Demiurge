/**
  * @file <src/modules/AutoMoDeBehaviourExploration.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EXPLORATION_TUTTIFRUTTI_H
#define AUTOMODE_BEHAVIOUR_EXPLORATION_TUTTIFRUTTI_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourExplorationTuttifrutti: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourExplorationTuttifrutti();
			AutoMoDeBehaviourExplorationTuttifrutti(AutoMoDeBehaviourExplorationTuttifrutti* pc_behaviour);
			virtual ~AutoMoDeBehaviourExplorationTuttifrutti();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourExplorationTuttifrutti* Clone();

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
	};
}

#endif