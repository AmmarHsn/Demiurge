/**
  * @file <src/modules/AutoMoDeBehaviourExplorationCoconut.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourExplorationCoconut.h"

namespace argos
{

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourExplorationCoconut::AutoMoDeBehaviourExplorationCoconut()
	{
		m_strLabel = "Exploration";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourExplorationCoconut::AutoMoDeBehaviourExplorationCoconut(AutoMoDeBehaviourExplorationCoconut *pc_behaviour)
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

	AutoMoDeBehaviourExplorationCoconut::~AutoMoDeBehaviourExplorationCoconut() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourExplorationCoconut *AutoMoDeBehaviourExplorationCoconut::Clone()
	{
		return new AutoMoDeBehaviourExplorationCoconut(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExplorationCoconut::Init()
	{
		bool error = false;
		m_walkSteps = 0;
		m_fProximityThreshold = 0.1;
		m_bLocked = false;
		std::map<std::string, Real>::iterator itExp = m_mapParameters.find("exp");
		std::map<std::string, Real>::iterator itRwm = m_mapParameters.find("rwm");
		std::map<std::string, Real>::iterator itMu = m_mapParameters.find("mu");
		std::map<std::string, Real>::iterator itRho = m_mapParameters.find("rho");
		if (itExp != m_mapParameters.end())
		{
			m_ExplorationType = itExp->second;
			switch (m_ExplorationType)
			{
			case 1:
				if (itRwm != m_mapParameters.end())
				{
					m_cRandomStepsRange.SetMax(itRwm->second);
				}
				else
				{
					error = true;
				}
				break;
			case 2:
				if (itMu != m_mapParameters.end() && itRho != m_mapParameters.end())
				{
					mu = itMu->second;
					rho = itRho->second;
				}
				else
				{
					error = true;
				}
			}
		}
		else
		{
			error = true;
		}
		if (error)
		{
			LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExplorationCoconut::ControlStep()
	{

		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(GetHeadingVector(CVector2(0, CRadians::ZERO), 1)));
		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExplorationCoconut::Reset()
	{
		m_bOperational = false;
		Init();
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExplorationCoconut::ResumeStep()
	{
		m_bOperational = true;
	}

	/****************************************/
	/****************************************/
} // namespace argos
