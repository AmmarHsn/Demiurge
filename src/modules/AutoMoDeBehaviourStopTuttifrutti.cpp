/**
  * @file <src/modules/AutoMoDeBehaviourStopTuttifrutti.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourStopTuttifrutti.h"

namespace argos
{

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStopTuttifrutti::AutoMoDeBehaviourStopTuttifrutti()
	{
		m_strLabel = "Stop";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStopTuttifrutti::AutoMoDeBehaviourStopTuttifrutti(AutoMoDeBehaviourStopTuttifrutti *pc_behaviour)
	{
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

	AutoMoDeBehaviourStopTuttifrutti::~AutoMoDeBehaviourStopTuttifrutti() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStopTuttifrutti *AutoMoDeBehaviourStopTuttifrutti::Clone()
	{
		return new AutoMoDeBehaviourStopTuttifrutti(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStopTuttifrutti::ControlStep()
	{
		m_pcRobotDAO->SetWheelsVelocity(0, 0);
		m_pcRobotDAO->SetLEDsColor(m_cColorEmiterParameter);
		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStopTuttifrutti::Init()
	{
		std::map<std::string, Real>::iterator it = m_mapParameters.find("cle");
		if (it != m_mapParameters.end())
		{
			m_cColorEmiterParameter = GetColorParameter(it->second, true);
		}
		else
		{
			LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStopTuttifrutti::Reset()
	{
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStopTuttifrutti::ResumeStep()
	{
		m_bOperational = true;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourStopTuttifrutti::Succeeded() {
		return false;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourStopTuttifrutti::Failed() {
		return false; //(ObstacleInFront() || !LightPerceived());
	}
} // namespace argos
