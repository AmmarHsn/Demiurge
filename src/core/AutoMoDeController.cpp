/*
 * @file <src/core/AutoMoDeController.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include "AutoMoDeController.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeController::AutoMoDeController() {
		m_pcRobotState = new ReferenceModel3Dot0();
		m_unTimeStep = 0;
		m_strConfiguration = "";
		m_bMaintainHistory = false;
		m_bPrintReadableFsm = false;
		m_strHistoryFolder = "./";
		m_bFiniteStateMachineGiven = false;
		m_bBehaviorTreeGiven = false;
		isFSM = false;
		isBT = false;
	}

	/****************************************/
	/****************************************/

	AutoMoDeController::~AutoMoDeController() {
		delete m_pcRobotState;
		if (isFSM) {
			delete m_pcFsmBuilder;
		}
		else if(isBT){
			delete m_pcBehaviorTree;
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::Init(TConfigurationNode& t_node) {
		// Parsing parameters
		try {
			GetNodeAttributeOrDefault(t_node, "config", m_strConfiguration, m_strConfiguration);
			GetNodeAttributeOrDefault(t_node, "history", m_bMaintainHistory, m_bMaintainHistory);
			GetNodeAttributeOrDefault(t_node, "hist-folder", m_strHistoryFolder, m_strHistoryFolder);
			GetNodeAttributeOrDefault(t_node, "readable", m_bPrintReadableFsm, m_bPrintReadableFsm);
		} catch (CARGoSException& ex) {
			THROW_ARGOSEXCEPTION_NESTED("Error parsing <params>", ex);
		}

		m_unRobotID = atoi(GetId().substr(5, 6).c_str());
		m_pcRobotState->SetRobotIdentifier(m_unRobotID);
		
		if(m_strConfiguration.find("--fsm-config") != std::string::npos){
			isFSM = true;
		}else if(m_strConfiguration.find("--bt-config") != std::string::npos){
			isBT = true;
		}

		/*
		 * If a FSM configuration is given as parameter of the experiment file, create a FSM from it
		 */
		if (isFSM && m_strConfiguration.compare("") != 0 && !m_bFiniteStateMachineGiven) {
			m_pcFsmBuilder = new AutoMoDeFsmBuilder();
			SetFiniteStateMachine(m_pcFsmBuilder->BuildFiniteStateMachine(m_strConfiguration));
			if (m_bMaintainHistory) {
				m_pcFiniteStateMachine->SetHistoryFolder(m_strHistoryFolder);
				m_pcFiniteStateMachine->MaintainHistory();
			}
			if (m_bPrintReadableFsm) {
				std::cout << "Finite State Machine description: " << std::endl;
				std::cout << m_pcFiniteStateMachine->GetReadableFormat() << std::endl;
			}
		}else if (isBT && m_strConfiguration.compare("") != 0 && !m_bBehaviorTreeGiven) {
			m_pcBtBuilder = new AutoMoDeBehaviorTreeBuilder();
			SetBehaviorTree(m_pcBtBuilder->BuildBehaviorTree(m_strConfiguration));
			if (m_bMaintainHistory) {
				//m_pcFiniteStateMachine->SetHistoryFolder(m_strHistoryFolder);
				//m_pcFiniteStateMachine->MaintainHistory();
			}
			if (m_bPrintReadableFsm) {
				std::cout << "Behavior tree description: " << std::endl;
				std::cout << m_pcBehaviorTree->GetReadableFormat() << std::endl;
			}
		} else {
			LOGERR << "Warning: No finite state machine configuration found in .argos" << std::endl;
		}



		/*
		 *  Initializing sensors and actuators
		 */
		try{
			m_pcProximitySensor = GetSensor<CCI_EPuckProximitySensor>("epuck_proximity");
			m_pcLightSensor = GetSensor<CCI_EPuckLightSensor>("epuck_light");
			m_pcGroundSensor = GetSensor<CCI_EPuckGroundSensor>("epuck_ground");
			 m_pcRabSensor = GetSensor<CCI_EPuckRangeAndBearingSensor>("epuck_range_and_bearing");
			 m_pcCameraSensor = GetSensor<CCI_EPuckOmnidirectionalCameraSensor>("epuck_omnidirectional_camera");
		} catch (CARGoSException ex) {
			LOGERR<<"Error while initializing a Sensor!\n";
		}

		if(m_pcCameraSensor != NULL){
            m_pcCameraSensor->Enable();
        }

		try{
			m_pcWheelsActuator = GetActuator<CCI_EPuckWheelsActuator>("epuck_wheels");
			m_pcRabActuator = GetActuator<CCI_EPuckRangeAndBearingActuator>("epuck_range_and_bearing");
			m_pcLEDsActuator = GetActuator<CCI_EPuckRGBLEDsActuator>("epuck_rgb_leds");
		} catch (CARGoSException ex) {
			LOGERR<<"Error while initializing an Actuator!\n";
		}

		/*
		 * Starts actuation.
		 */
		 InitializeActuation();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::ControlStep() {
		/*
		 * 1. Update RobotDAO
		 */
		if(m_pcRabSensor != NULL){
			const CCI_EPuckRangeAndBearingSensor::TPackets& packets = m_pcRabSensor->GetPackets();
			//m_pcRobotState->SetNumberNeighbors(packets.size());
			m_pcRobotState->SetRangeAndBearingMessages(packets);
		}
		if (m_pcGroundSensor != NULL) {
			const CCI_EPuckGroundSensor::SReadings& readings = m_pcGroundSensor->GetReadings();
			m_pcRobotState->SetGroundInput(readings);
		}
		if (m_pcLightSensor != NULL) {
			const CCI_EPuckLightSensor::TReadings& readings = m_pcLightSensor->GetReadings();
			m_pcRobotState->SetLightInput(readings);
		}
		if (m_pcProximitySensor != NULL) {
			const CCI_EPuckProximitySensor::TReadings& readings = m_pcProximitySensor->GetReadings();
			m_pcRobotState->SetProximityInput(readings);
		}
		if(m_pcCameraSensor != NULL){
            const CCI_EPuckOmnidirectionalCameraSensor::SReadings& readings = m_pcCameraSensor->GetReadings();
            m_pcRobotState->SetCameraInput(readings);
        }

		/*
		 * 2. Execute step of FSM
		 */
		if(m_bFiniteStateMachineGiven)
			m_pcFiniteStateMachine->ControlStep();
		else if(m_bBehaviorTreeGiven)
			m_pcBehaviorTree->ControlStep();
		/*
		 * 3. Update Actuators
		 */
		if (m_pcWheelsActuator != NULL) {
			m_pcWheelsActuator->SetLinearVelocity(m_pcRobotState->GetLeftWheelVelocity(),m_pcRobotState->GetRightWheelVelocity());
		}
		if (m_pcLEDsActuator != NULL) {
            //m_pcLEDsActuator->SetColors(m_pcRobotState->GetLEDsColor());
            m_pcLEDsActuator->SetColor(2,m_pcRobotState->GetLEDsColor());
        }

		/*
		 * 4. Update variables and sensors
		 */
		if (m_pcRabSensor != NULL) {
			m_pcRabSensor->ClearPackets();
		}
		m_unTimeStep++;

	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::Destroy() {}

	/****************************************/
	/****************************************/

	void AutoMoDeController::Reset() {
		if(m_bFiniteStateMachineGiven)
			m_pcFiniteStateMachine->Reset();
		else if(m_bBehaviorTreeGiven)
			m_pcBehaviorTree->Reset();
		
		m_pcRobotState->Reset();
		// Restart actuation.
		InitializeActuation();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::SetFiniteStateMachine(AutoMoDeFiniteStateMachine* pc_finite_state_machine) {
		m_pcFiniteStateMachine = pc_finite_state_machine;
		m_pcFiniteStateMachine->SetRobotDAO(m_pcRobotState);
		m_pcFiniteStateMachine->Init();
		m_bFiniteStateMachineGiven = true;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::SetBehaviorTree(AutoMoDeBehaviorTree* pc_behavior_tree) {
		m_pcBehaviorTree = pc_behavior_tree;
		m_pcBehaviorTree->SetRobotDAO(m_pcRobotState);
		m_pcBehaviorTree->Init();
		m_bBehaviorTreeGiven = true;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::SetHistoryFlag(bool b_history_flag) {
		if (b_history_flag) {
			m_pcFiniteStateMachine->MaintainHistory();
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::InitializeActuation() {
		/*
		 * Constantly send range-and-bearing messages containing the robot integer identifier.
		 */
		if (m_pcRabActuator != NULL) {
			UInt8 data[4];
			data[0] = m_unRobotID;
			data[1] = 0;
			data[2] = 0;
			data[3] = 0;
			m_pcRabActuator->SetData(data);
		}
	}

	REGISTER_CONTROLLER(AutoMoDeController, "automode_controller");
}
