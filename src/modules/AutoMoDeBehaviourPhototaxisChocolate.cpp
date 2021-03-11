/**
  * @file <src/modules/AutoMoDeBehaviourPhototaxisChocolate.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourPhototaxisChocolate.h"


namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourPhototaxisChocolate::AutoMoDeBehaviourPhototaxisChocolate() {
		m_strLabel = "Phototaxis";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourPhototaxisChocolate::AutoMoDeBehaviourPhototaxisChocolate(AutoMoDeBehaviourPhototaxisChocolate* pc_behaviour) {
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

	AutoMoDeBehaviourPhototaxisChocolate::~AutoMoDeBehaviourPhototaxisChocolate() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourPhototaxisChocolate* AutoMoDeBehaviourPhototaxisChocolate::Clone() {
		return new AutoMoDeBehaviourPhototaxisChocolate(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourPhototaxisChocolate::ControlStep() {
		CVector2 sResultVector(0,CRadians::ZERO);
		CVector2 sLightVector(0,CRadians::ZERO);
		CVector2 sProxVector(0,CRadians::ZERO);

		CCI_EPuckLightSensor::SReading cLightReading = m_pcRobotDAO->GetLightReading();
		sLightVector = CVector2(cLightReading.Value, cLightReading.Angle);

		sProxVector = CVector2(m_pcRobotDAO->GetProximityReading().Value, m_pcRobotDAO->GetProximityReading().Angle);
		sResultVector = sLightVector - 5*sProxVector;

		if (sResultVector.Length() < 0.1) {
			sResultVector = CVector2(1, CRadians::ZERO);
		}
		
		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(sResultVector));

		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourPhototaxisChocolate::Init() {}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourPhototaxisChocolate::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourPhototaxisChocolate::ResumeStep() {
		m_bOperational = true;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourPhototaxisChocolate::Succeeded() {
		return false;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourPhototaxisChocolate::Failed() {
		return false; //(ObstacleInFront() || !LightPerceived());
	}
}
