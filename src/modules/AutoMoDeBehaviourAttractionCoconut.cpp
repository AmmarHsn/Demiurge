/**
  * @file <src/modules/AutoMoDeBehaviourAttractionCoconut.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourAttractionCoconut.h"

namespace argos
{

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAttractionCoconut::AutoMoDeBehaviourAttractionCoconut()
	{
		m_strLabel = "Attraction";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAttractionCoconut::AutoMoDeBehaviourAttractionCoconut(AutoMoDeBehaviourAttractionCoconut *pc_behaviour)
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

	AutoMoDeBehaviourAttractionCoconut::~AutoMoDeBehaviourAttractionCoconut() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAttractionCoconut *AutoMoDeBehaviourAttractionCoconut::Clone()
	{
		return new AutoMoDeBehaviourAttractionCoconut(this); // todo: check without *
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAttractionCoconut::ControlStep()
	{
		CVector2 sRabVector(0, CRadians::ZERO);
		CCI_EPuckRangeAndBearingSensor::SReceivedPacket cRabReading = m_pcRobotDAO->GetAttractionVectorToNeighbors(m_unAttractionParameter);

		if (cRabReading.Range > 0.0f)
		{
			sRabVector = CVector2(cRabReading.Range, cRabReading.Bearing) * m_unAttractionParameter;
		}

		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(GetHeadingVector(sRabVector, 6)));

		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAttractionCoconut::Init()
	{
		bool error = false;
		m_walkSteps = 0;
		m_fProximityThreshold = 0.1;
		m_bLocked = false;

		std::map<std::string, Real>::iterator itAtt = m_mapParameters.find("att");
		std::map<std::string, Real>::iterator itExp = m_mapParameters.find("exp");
		std::map<std::string, Real>::iterator itRwm = m_mapParameters.find("rwm");
		std::map<std::string, Real>::iterator itMu = m_mapParameters.find("mu");
		std::map<std::string, Real>::iterator itRho = m_mapParameters.find("rho");
		if (itExp != m_mapParameters.end() && itAtt != m_mapParameters.end())
		{
			m_ExplorationType = itExp->second;
			m_unAttractionParameter = itAtt->second;
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

	void AutoMoDeBehaviourAttractionCoconut::Reset()
	{
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAttractionCoconut::ResumeStep()
	{
		m_bOperational = true;
	}
} // namespace argos
