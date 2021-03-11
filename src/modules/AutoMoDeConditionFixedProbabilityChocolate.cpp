/**
  * @file <src/modules/AutoMoDeConditionFixedProbabilityChocolate.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

 #include "AutoMoDeConditionFixedProbabilityChocolate.h"

 namespace argos {

  /****************************************/
  /****************************************/

	AutoMoDeConditionFixedProbabilityChocolate::AutoMoDeConditionFixedProbabilityChocolate() {
		m_strLabel = "FixedProbability";
	}

  /****************************************/
  /****************************************/

	AutoMoDeConditionFixedProbabilityChocolate::~AutoMoDeConditionFixedProbabilityChocolate() {}

  /****************************************/
  /****************************************/

	AutoMoDeConditionFixedProbabilityChocolate::AutoMoDeConditionFixedProbabilityChocolate(AutoMoDeConditionFixedProbabilityChocolate* pc_condition) {
		m_strLabel = pc_condition->GetLabel();
		m_unIndex = pc_condition->GetIndex();
		m_unIdentifier = pc_condition->GetIndex();
		m_unFromBehaviourIndex = pc_condition->GetOrigin();
		m_unToBehaviourIndex = pc_condition->GetExtremity();
		m_mapParameters = pc_condition->GetParameters();
    Init();
	}

  /****************************************/
  /****************************************/

	AutoMoDeConditionFixedProbabilityChocolate* AutoMoDeConditionFixedProbabilityChocolate::Clone() {
		return new AutoMoDeConditionFixedProbabilityChocolate(this);
	}

  /****************************************/
  /****************************************/

	void AutoMoDeConditionFixedProbabilityChocolate::Init() {
		std::map<std::string, Real>::iterator it = m_mapParameters.find("p");
		if (it != m_mapParameters.end()) {
			m_fProbability = it->second;
		} else {
			LOGERR << "[FATAL] Missing parameter for the following condition:" << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
	}

  /****************************************/
  /****************************************/

	bool AutoMoDeConditionFixedProbabilityChocolate::Verify() {
		return EvaluateBernoulliProbability(m_fProbability);
	}

  /****************************************/
  /****************************************/

	void AutoMoDeConditionFixedProbabilityChocolate::Reset() {
    Init();
  }

 }
