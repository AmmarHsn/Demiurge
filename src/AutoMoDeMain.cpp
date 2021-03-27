/*
 * @file <src/AutoMoDeMain.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/entity/entity.h>
#include <argos3/core/simulator/entity/controllable_entity.h>
#include <argos3/core/utility/plugins/dynamic_loading.h>
#include <argos3/core/simulator/argos_command_line_arg_parser.h>

#include "./core/AutoMoDeFiniteStateMachine.h"
#include "./core/AutoMoDeFsmBuilder.h"
#include "./core/AutoMoDeController.h"

#include "./core/AutoMoDeBehaviorTree.h"
#include "./core/AutoMoDeBehaviorTreeBuilder.h"

#include <argos3/demiurge/loop-functions/CoreLoopFunctions.h>

using namespace argos;

const std::string ExplainParameters() {
	std::string strExplanation = "Missing finite state machine configuration. The possible parameters are: \n\n"
		" -r | --readable-fsm \t Prints an URL containing a DOT representation of the finite state machine [OPTIONAL]. \n"
		" -s | --seed \t The seed for the ARGoS simulator [OPTIONAL] \n"
		" --fsm-config CONF \t The finite state machine description [MANDATORY]\n"
		"\n The description of the finite state machine should be placed at the end of the command line, after the other parameters.";
	return strExplanation;
}

/**
 * @brief
 *
 */
int main(int n_argc, char** ppch_argv) {

	bool bHistory = false;

	bool bReadableFSM = false;
	bool bReadableBT = false;
	std::vector<std::string> vecConfig;
	bool bControllerFound = false;
	UInt32 unSeed = 0;

	std::vector<AutoMoDeFiniteStateMachine*> vecFsm;
	std::vector<AutoMoDeBehaviorTree*> vecBt;

	bool isFSM = false;
	bool isBT = false;

	try {
		// Cutting off the FSM configuration from the command line

		int nCurrentArgument = 1;
		while(!bControllerFound && nCurrentArgument < n_argc) {
			if(strcmp(ppch_argv[nCurrentArgument], "--fsm-config") == 0) {
				bControllerFound = true;
				nCurrentArgument++;
				while (nCurrentArgument < n_argc) {
					vecConfig.push_back(std::string(ppch_argv[nCurrentArgument]));
					nCurrentArgument++;
				}
				// Do not take the FSM configuration into account in the standard command line parsing.
				n_argc = n_argc - vecConfig.size() - 1;
				isFSM = true;
				isBT = false;
			}else if(strcmp(ppch_argv[nCurrentArgument], "--bt-config")==0){
				bControllerFound = true;
				nCurrentArgument++;
				while (nCurrentArgument < n_argc) {
					vecConfig.push_back(std::string(ppch_argv[nCurrentArgument]));
					nCurrentArgument++;
				}
				// Do not take the FSM configuration into account in the standard command line parsing.
				n_argc = n_argc - vecConfig.size() - 1;
				isBT = true;
				isFSM = false;
			}
			nCurrentArgument++;
		}
		if (!bControllerFound) {
			THROW_ARGOSEXCEPTION(ExplainParameters());
		}

		/*std::vector<std::string>::iterator it;

		it = std::find(vecConfig.begin(), vecConfig.end(), "--fsm-config");
		//s.find(bar) != std::string::npos
		if(it != vecConfig.end()){
			isFSM = true;
		}
		else{
			it = std::find(vecConfig.begin(), vecConfig.end(), "--bt-config");
			if(it != vecConfig.end()){
				isBT = true;
			}
		}*/
		/*
		if(strcmp((*(it+1)).c_str(), "fsm") == 0){
			isFSM = true;
		}else if(strcmp((*(it+1)).c_str(), "bt") == 0){
			isBT = true;
		}*/

		// Configure the command line options
		CARGoSCommandLineArgParser cACLAP;
		cACLAP.AddFlag('r', "readable-fsm", "", bReadableFSM);

		cACLAP.AddFlag('r', "readable-bt", "", bReadableBT);

		cACLAP.AddFlag('t', "history", "", bHistory);

		cACLAP.AddArgument<UInt32>('s', "seed", "", unSeed);

		// Parse command line without taking the configuration of the FSM into account
		cACLAP.Parse(n_argc, ppch_argv);

		CSimulator& cSimulator = CSimulator::GetInstance();

		switch(cACLAP.GetAction()) {
    	case CARGoSCommandLineArgParser::ACTION_RUN_EXPERIMENT: {
				CDynamicLoading::LoadAllLibraries();
				cSimulator.SetExperimentFileName(cACLAP.GetExperimentConfigFile());
				AutoMoDeFiniteStateMachine* pcFiniteStateMachine;
				AutoMoDeBehaviorTree* pcBehaviorTree;
				// Creation of the finite state machine.
				if(isFSM){
					AutoMoDeFsmBuilder cBuilder = AutoMoDeFsmBuilder();
					pcFiniteStateMachine = cBuilder.BuildFiniteStateMachine(vecConfig);
				}
				else if(isBT){
					AutoMoDeBehaviorTreeBuilder cBuilder = AutoMoDeBehaviorTreeBuilder();
					pcBehaviorTree = cBuilder.BuildBehaviorTree(vecConfig);
				}
				

				// If the URL of the finite state machine is requested, display it.
				if (bReadableFSM) {
					std::cout << "Finite State Machine description: " << std::endl;
					std::cout << pcFiniteStateMachine->GetReadableFormat() << std::endl;
				}else if(bReadableBT){
					std::cout << "Behavior Tree description: " << std::endl;
					std::cout << pcBehaviorTree->GetReadableFormat() << std::endl;
				}

				// Setting random seed. Only works with modified version of ARGoS3.
				cSimulator.SetRandomSeed(unSeed);

				cSimulator.LoadExperiment();

				// Duplicate the finite state machine and pass it to all robots.
				CSpace::TMapPerType cEntities = cSimulator.GetSpace().GetEntitiesByType("controller");
				AutoMoDeFiniteStateMachine* pcPersonalFsm;
				AutoMoDeBehaviorTree* pcPersonalBt;
				for (CSpace::TMapPerType::iterator it = cEntities.begin(); it != cEntities.end(); ++it) {
					CControllableEntity* pcEntity = any_cast<CControllableEntity*>(it->second);
					if(isFSM){
						pcPersonalFsm = new AutoMoDeFiniteStateMachine(pcFiniteStateMachine);
						vecFsm.push_back(pcPersonalFsm);
					}else if(isBT){
						pcPersonalBt = new AutoMoDeBehaviorTree(pcBehaviorTree);
						vecBt.push_back(pcPersonalBt);
					}
					
					try {
						if(isFSM){
							AutoMoDeController& cController = dynamic_cast<AutoMoDeController&> (pcEntity->GetController());
							cController.SetFiniteStateMachine(pcPersonalFsm);
							cController.SetHistoryFlag(bHistory);
						}else if(isBT){
							AutoMoDeController& cController = dynamic_cast<AutoMoDeController&> (pcEntity->GetController());
							cController.SetBehaviorTree(pcPersonalBt);
						}
						
					} catch (std::exception& ex) {
						LOGERR << "Error while casting: " << ex.what() << std::endl;
					}
				}

				cSimulator.Execute();

				// Retrieval of the score of the swarm driven by the Finite State Machine
				CoreLoopFunctions& cLoopFunctions = dynamic_cast<CoreLoopFunctions&> (cSimulator.GetLoopFunctions());
				Real fObjectiveFunction = cLoopFunctions.GetObjectiveFunction();
				std::cout << "Score " << fObjectiveFunction << std::endl;

				break;
			}

    	case CARGoSCommandLineArgParser::ACTION_QUERY:
        CDynamicLoading::LoadAllLibraries();
        //QueryPlugins(cACLAP.GetQuery());
        break;
    	case CARGoSCommandLineArgParser::ACTION_SHOW_HELP:
        cACLAP.PrintUsage(LOG);
        break;
		 	case CARGoSCommandLineArgParser::ACTION_SHOW_VERSION:
        cACLAP.PrintVersion();
        break;
      case CARGoSCommandLineArgParser::ACTION_UNKNOWN:
        // Should never get here
        break;
		}

		cSimulator.Destroy();

	} catch(std::exception& ex) {
    // A fatal error occurred: dispose of data, print error and exit
    LOGERR << ex.what() << std::endl;
#ifdef ARGOS_THREADSAFE_LOG
    LOG.Flush();
    LOGERR.Flush();
#endif
    return 1;
  }

	if(isFSM){
		for (unsigned int i = 0; i < vecFsm.size(); ++i) {
			delete vecFsm.at(i);
		}
	}else if(isBT){
		for (unsigned int i = 0; i < vecBt.size(); ++i) {
			delete vecBt.at(i);
		}
	}
	


	/* Everything's ok, exit */
  return 0;
}
