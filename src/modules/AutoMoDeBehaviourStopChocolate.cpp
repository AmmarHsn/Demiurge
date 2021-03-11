/**
  * @file <src/modules/AutoMoDeBehaviourStopChocolate.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourStopChocolate.h"


namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStopChocolate::AutoMoDeBehaviourStopChocolate() {
		m_strLabel = "Stop";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStopChocolate::AutoMoDeBehaviourStopChocolate(AutoMoDeBehaviourStopChocolate* pc_behaviour) {
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

	AutoMoDeBehaviourStopChocolate::~AutoMoDeBehaviourStopChocolate() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStopChocolate* AutoMoDeBehaviourStopChocolate::Clone() {
		return new AutoMoDeBehaviourStopChocolate(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStopChocolate::ControlStep() {
		m_pcRobotDAO->SetWheelsVelocity(0,0);
		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStopChocolate::Init() {
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStopChocolate::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStopChocolate::ResumeStep() {
		m_bOperational = true;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourStopChocolate::Succeeded() {
		return false;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourStopChocolate::Failed() {
		return false; //(ObstacleInFront() || !LightPerceived());
	}
}
