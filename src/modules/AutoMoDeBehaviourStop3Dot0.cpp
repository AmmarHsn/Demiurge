/**
  * @file <src/modules/AutoMoDeBehaviourStop3Dot0.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourStop3Dot0.h"

namespace argos
{

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStop3Dot0::AutoMoDeBehaviourStop3Dot0()
	{
		m_strLabel = "Stop";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStop3Dot0::AutoMoDeBehaviourStop3Dot0(AutoMoDeBehaviourStop3Dot0 *pc_behaviour)
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

	AutoMoDeBehaviourStop3Dot0::~AutoMoDeBehaviourStop3Dot0() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStop3Dot0 *AutoMoDeBehaviourStop3Dot0::Clone()
	{
		return new AutoMoDeBehaviourStop3Dot0(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop3Dot0::ControlStep()
	{
		m_pcRobotDAO->SetWheelsVelocity(0, 0);
		if(is3Dot0)
			m_pcRobotDAO->SetLEDsColor(m_cColorEmiterParameter);
		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop3Dot0::Init()
	{
		std::map<std::string, Real>::iterator it = m_mapParameters.find("cle");
		if (it != m_mapParameters.end())
		{
			m_cColorEmiterParameter = GetColorParameter(it->second, true);
			is3Dot0 = true;
		}
		else
		{
			//LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
			//THROW_ARGOSEXCEPTION("Missing Parameter");
			is3Dot0 = false;
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop3Dot0::Reset()
	{
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop3Dot0::ResumeStep()
	{
		m_bOperational = true;
	}
} // namespace argos
