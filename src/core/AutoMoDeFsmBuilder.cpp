/*
 * @file <src/core/AutoMoDeFsmBuilder.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include "AutoMoDeFsmBuilder.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeFsmBuilder::AutoMoDeFsmBuilder() {}

	/****************************************/
	/****************************************/

	AutoMoDeFsmBuilder::~AutoMoDeFsmBuilder() {
		delete cFiniteStateMachine;
	}

	/****************************************/
	/****************************************/

	AutoMoDeFiniteStateMachine* AutoMoDeFsmBuilder::BuildFiniteStateMachine(const std::string& str_fsm_config) {
		std::istringstream iss(str_fsm_config);
		std::vector<std::string> tokens;
		copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			std::back_inserter(tokens));
		return BuildFiniteStateMachine(tokens);
	}

	/****************************************/
	/****************************************/

	AutoMoDeFiniteStateMachine* AutoMoDeFsmBuilder::BuildFiniteStateMachine(std::vector<std::string>& vec_fsm_config) {
		cFiniteStateMachine = new AutoMoDeFiniteStateMachine();

		std::vector<std::string>::iterator it;
		try {
			it = std::find(vec_fsm_config.begin(), vec_fsm_config.end(), "--nstates");
			m_unNumberStates = atoi((*(it+1)).c_str());
			std::vector<std::string>::iterator first_state;
			std::vector<std::string>::iterator second_state;
			for (UInt32 i = 0; i < m_unNumberStates; i++) {
				std::ostringstream oss;
				oss << "--s" << i;
				first_state = std::find(vec_fsm_config.begin(), vec_fsm_config.end(), oss.str());
				if (i+1 < m_unNumberStates) {
					std::ostringstream oss;
					oss << "--s" << i+1;
					second_state = std::find(vec_fsm_config.begin(), vec_fsm_config.end(), oss.str());
				} else {
					second_state = vec_fsm_config.end();
				}
				std::vector<std::string> vecStateConfig(first_state, second_state);
				HandleState(cFiniteStateMachine, vecStateConfig);
			}
		}
		catch (std::exception e) {
			THROW_ARGOSEXCEPTION("Could not create the Finite State Machine: Error while parsing.");
		}

		return cFiniteStateMachine;

	}

	/****************************************/
	/****************************************/

	void AutoMoDeFsmBuilder::HandleState(AutoMoDeFiniteStateMachine* c_fsm, std::vector<std::string>& vec_fsm_state_config) {
		AutoMoDeBehaviour* cNewBehaviour;
		std::vector<std::string>::iterator it;
		// Extraction of the index of the behaviour in the FSM
		UInt8 unBehaviourIndex =  atoi((*vec_fsm_state_config.begin()).substr(3,4).c_str());
		// Extraction of the identifier of the behaviour
		UInt8 unBehaviourIdentifier =  atoi((*(vec_fsm_state_config.begin()+1)).c_str());

		// Creation of the Behaviour object
		switch(unBehaviourIdentifier) {
			case 10:
				cNewBehaviour = new AutoMoDeBehaviourExplorationChocolate();
				break;
			case 11:
				cNewBehaviour = new AutoMoDeBehaviourStopChocolate();
				break;
			case 12:
				cNewBehaviour = new AutoMoDeBehaviourPhototaxisChocolate();
				break;
			case 13:
				cNewBehaviour = new AutoMoDeBehaviourAntiPhototaxisChocolate();
				break;
			case 14:
				cNewBehaviour = new AutoMoDeBehaviourAttractionChocolate();
				break;
			case 15:
				cNewBehaviour = new AutoMoDeBehaviourRepulsionChocolate();
				break;
			case 20:
				cNewBehaviour = new AutoMoDeBehaviourExplorationTuttifrutti();
				break;
			case 21:
				cNewBehaviour = new AutoMoDeBehaviourStopTuttifrutti();
				break;
			case 22:
				cNewBehaviour = new AutoMoDeBehaviourPhototaxisChocolate();//TO DO: Remove photoaxis and antiphoto
				break;
			case 23:
				cNewBehaviour = new AutoMoDeBehaviourAntiPhototaxisChocolate();
				break;
			case 24:
				cNewBehaviour = new AutoMoDeBehaviourAttractionTuttifrutti();
				break;
			case 25:
				cNewBehaviour = new AutoMoDeBehaviourRepulsionTuttifrutti();
				break;
			case 28:
				cNewBehaviour = new AutoMoDeBehaviourGoToColorTuttifrutti();
				break;
			case 29:
				cNewBehaviour = new AutoMoDeBehaviourGoAwayColorTuttifrutti();
				break;
			case 30:
				cNewBehaviour = new AutoMoDeBehaviourExplorationCoconut();
				break;
			case 31:
				cNewBehaviour = new AutoMoDeBehaviourStopChocolate();
				break;
			case 32:
				cNewBehaviour = new AutoMoDeBehaviourPhototaxisCoconut();
				break;
			case 33:
				cNewBehaviour = new AutoMoDeBehaviourAntiPhototaxisCoconut();
				break;
			case 34:
				cNewBehaviour = new AutoMoDeBehaviourAttractionCoconut();
				break;
			case 35:
				cNewBehaviour = new AutoMoDeBehaviourRepulsionCoconut();
				break;
		}
		
		cNewBehaviour->SetIndex(unBehaviourIndex);
		cNewBehaviour->SetIdentifier(unBehaviourIdentifier);

		// Checking for parameters
		std::string vecPossibleParameters[] = {"rwm", "att", "rep", "cle", "clr", "vel", "exp", "mu", "rho"};
		UInt8 unNumberPossibleParameters = sizeof(vecPossibleParameters) / sizeof(vecPossibleParameters[0]);
		for (UInt8 i = 0; i < unNumberPossibleParameters; i++) {
			std::string strCurrentParameter = vecPossibleParameters[i];
			std::ostringstream oss;
			oss << "--" <<strCurrentParameter << unBehaviourIndex;
			it = std::find(vec_fsm_state_config.begin(), vec_fsm_state_config.end(), oss.str());
			if (it != vec_fsm_state_config.end()) {
				Real fCurrentParameterValue = strtod((*(it+1)).c_str(), NULL);
				cNewBehaviour->AddParameter(strCurrentParameter, fCurrentParameterValue);
			}
		}
		cNewBehaviour->Init();
		// Add the constructed Behaviour to the FSM
		c_fsm->AddBehaviour(cNewBehaviour);

		/*
		 * Extract the transitions starting from the state and
		 * pass them to the transition handler, if they exist.
		 */
		std::ostringstream oss;
		oss << "--n" << unBehaviourIndex;
		it = std::find(vec_fsm_state_config.begin(), vec_fsm_state_config.end(), oss.str());
		if (it != vec_fsm_state_config.end()) {
			UInt8 unNumberTransitions = atoi((*(it+1)).c_str());

			std::vector<std::string>::iterator first_transition;
			std::vector<std::string>::iterator second_transition;

			for (UInt8 i = 0; i < unNumberTransitions; i++) {
				std::ostringstream oss;
				oss << "--n" << unBehaviourIndex << "x" << i;
				first_transition = std::find(vec_fsm_state_config.begin(), vec_fsm_state_config.end(), oss.str());
				if (i+1 < unNumberTransitions) {
					std::ostringstream oss;
					oss << "--n" << unBehaviourIndex << "x" << i+1;
					second_transition = std::find(vec_fsm_state_config.begin(), vec_fsm_state_config.end(), oss.str());
				} else {
					second_transition = vec_fsm_state_config.end();
				}
				std::vector<std::string> vecTransitionConfig(first_transition, second_transition);
				HandleTransition(vecTransitionConfig, unBehaviourIndex, i);
			}
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeFsmBuilder::HandleTransition(std::vector<std::string>& vec_fsm_transition_config, const UInt32& un_initial_state_index, const UInt32& un_condition_index) {
		AutoMoDeCondition* cNewCondition;

		std::stringstream ss;
		ss << "--n" << un_initial_state_index << "x" << un_condition_index;
		std::vector<UInt32> vecPossibleDestinationIndex = GetPossibleDestinationBehaviour(un_initial_state_index);
		std::vector<std::string>::iterator it;
		it = std::find(vec_fsm_transition_config.begin(), vec_fsm_transition_config.end(), ss.str());

		// TODO: Check here whether unToBehaviour is smaller than the total number of states.
		UInt32 unIndexBehaviour = atoi((*(it+1)).c_str());
		UInt32 unToBehaviour = vecPossibleDestinationIndex.at(unIndexBehaviour);
		if (unToBehaviour < m_unNumberStates) {
			ss.str(std::string());
			ss << "--c" << un_initial_state_index << "x" << un_condition_index;
			it = std::find(vec_fsm_transition_config.begin(), vec_fsm_transition_config.end(), ss.str());

			UInt8 unConditionIdentifier = atoi((*(it+1)).c_str());

			switch(unConditionIdentifier) {
				case 10:
					cNewCondition = new AutoMoDeConditionBlackFloor();
					break;
				case 11:
					cNewCondition = new AutoMoDeConditionGrayFloor();
					break;
				case 12:
					cNewCondition = new AutoMoDeConditionWhiteFloor();
					break;
				case 13:
					cNewCondition = new AutoMoDeConditionNeighborsCount();
					break;
				case 14:
					cNewCondition = new AutoMoDeConditionInvertedNeighborsCount();
					break;
				case 15:
					cNewCondition = new AutoMoDeConditionFixedProbability();
					break;
				case 20:
					cNewCondition = new AutoMoDeConditionBlackFloor();
					break;
				case 21:
					cNewCondition = new AutoMoDeConditionGrayFloor();
					break;
				case 22:
					cNewCondition = new AutoMoDeConditionWhiteFloor();
					break;
				case 23:
					cNewCondition = new AutoMoDeConditionNeighborsCount();
					break;
				case 24:
					cNewCondition = new AutoMoDeConditionInvertedNeighborsCount();
					break;
				case 25:
					cNewCondition = new AutoMoDeConditionFixedProbability();
					break;
				case 27:
					cNewCondition = new AutoMoDeConditionProbColorTuttifrutti();
					break;
				case 30:
					cNewCondition = new AutoMoDeConditionBlackFloor();
					break;
				case 31:
					cNewCondition = new AutoMoDeConditionGrayFloor();
					break;
				case 32:
					cNewCondition = new AutoMoDeConditionWhiteFloor();
					break;
				case 33:
					cNewCondition = new AutoMoDeConditionNeighborsCount();
					break;
				case 34:
					cNewCondition = new AutoMoDeConditionInvertedNeighborsCount();
					break;
				case 35:
					cNewCondition = new AutoMoDeConditionFixedProbability();
					break;
			}

			cNewCondition->SetOriginAndExtremity(un_initial_state_index, unToBehaviour);
			cNewCondition->SetIndex(un_condition_index);
			cNewCondition->SetIdentifier(unConditionIdentifier);


			// Checking for parameters
			std::string vecPossibleParameters[] = {"p", "w", "l", "n"};
			UInt8 unNumberPossibleParameters = sizeof(vecPossibleParameters) / sizeof(vecPossibleParameters[0]);
			for (UInt8 i = 0; i < unNumberPossibleParameters; i++) {
				std::string strCurrentParameter = vecPossibleParameters[i];
				ss.str(std::string());
				ss << "--" << strCurrentParameter << un_initial_state_index << "x" << un_condition_index;
				it = std::find(vec_fsm_transition_config.begin(), vec_fsm_transition_config.end(), ss.str());
				if (it != vec_fsm_transition_config.end()) {
					Real fCurrentParameterValue = strtod((*(it+1)).c_str(), NULL);
					cNewCondition->AddParameter(strCurrentParameter, fCurrentParameterValue);
				}
			}
			cNewCondition->Init();
			cFiniteStateMachine->AddCondition(cNewCondition);
		}
	}

	/****************************************/
	/****************************************/

	const std::vector<UInt32> AutoMoDeFsmBuilder::GetPossibleDestinationBehaviour(const UInt32& un_initial_state_index) {
		std::vector<UInt32> vecPossibleDestinationIndex;
		for (UInt32 i = 0; i < m_unNumberStates; i++) {
			if (i != un_initial_state_index) {
				vecPossibleDestinationIndex.push_back(i);
			}
		}
		return vecPossibleDestinationIndex;
	}

}
