/**
  * @file <src/modules/AutoMoDeBehaviourExplorationChocolate.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourExplorationChocolate.h"


namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourExplorationChocolate::AutoMoDeBehaviourExplorationChocolate() {
		m_strLabel = "Exploration";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourExplorationChocolate::AutoMoDeBehaviourExplorationChocolate(AutoMoDeBehaviourExplorationChocolate* pc_behaviour) {
		m_strLabel = pc_behaviour->GetLabel();
		m_bLocked = pc_behaviour->IsLocked();
		m_bOperational = pc_behaviour->IsOperational();
		m_unIndex = pc_behaviour->GetIndex();
		m_unIdentifier = pc_behaviour->GetIdentifier();
		m_mapParameters = pc_behaviour->GetParameters();
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourExplorationChocolate::~AutoMoDeBehaviourExplorationChocolate() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourExplorationChocolate* AutoMoDeBehaviourExplorationChocolate::Clone() {
		return new AutoMoDeBehaviourExplorationChocolate(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExplorationChocolate::Init() {
		m_unTurnSteps = 0;
		m_eExplorationState = RANDOM_WALK;
		m_fProximityThreshold = 0.1;
		m_bLocked = false;
		std::map<std::string, Real>::iterator it = m_mapParameters.find("rwm");
		if (it != m_mapParameters.end()) {
			m_cRandomStepsRange.SetMax(it->second);
		} else {
			LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExplorationChocolate::ControlStep() {
		switch (m_eExplorationState) {
			case RANDOM_WALK: {
				m_pcRobotDAO->SetWheelsVelocity(m_pcRobotDAO->GetMaxVelocity(), m_pcRobotDAO->GetMaxVelocity());
				if (IsObstacleInFront(m_pcRobotDAO->GetProximityReading())) {
					m_eExplorationState = OBSTACLE_AVOIDANCE;
					m_unTurnSteps = (m_pcRobotDAO->GetRandomNumberGenerator())->Uniform(m_cRandomStepsRange);
					CRadians cAngle = m_pcRobotDAO->GetProximityReading().Angle.SignedNormalize();
					if (cAngle.GetValue() < 0) {
						m_eTurnDirection = LEFT;
					} else {
						m_eTurnDirection = RIGHT;
					}
				}
				break;
			}
			case OBSTACLE_AVOIDANCE: {
				m_unTurnSteps -= 1;
				switch (m_eTurnDirection) {
					case LEFT: {
						m_pcRobotDAO->SetWheelsVelocity(-m_pcRobotDAO->GetMaxVelocity(), m_pcRobotDAO->GetMaxVelocity());
						break;
					}
					case RIGHT: {
						m_pcRobotDAO->SetWheelsVelocity(m_pcRobotDAO->GetMaxVelocity(), -m_pcRobotDAO->GetMaxVelocity());
						break;
					}
				}
				if (m_unTurnSteps <= 0) {
					m_eExplorationState = RANDOM_WALK;
				}
				break;
			}
		}
		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExplorationChocolate::Reset() {
		m_bOperational = false;
		Init();
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExplorationChocolate::ResumeStep() {
		m_bOperational = true;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourExplorationChocolate::IsObstacleInFront(CCI_EPuckProximitySensor::SReading s_prox_reading) {
		CRadians cAngle = s_prox_reading.Angle;
		if (s_prox_reading.Value >= m_fProximityThreshold && ((cAngle <= CRadians::PI_OVER_TWO) && (cAngle >= -CRadians::PI_OVER_TWO))) {
			return true;
		}
		return false;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourExplorationChocolate::Succeeded() {
		return false;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourExplorationChocolate::Failed() {
		return false; //(ObstacleInFront() || !LightPerceived());
	}
}
