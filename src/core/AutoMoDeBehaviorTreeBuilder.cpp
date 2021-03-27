/*
 * @file <src/core/AutoMoDeBehaviorTreeBuilder.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include "AutoMoDeBehaviorTreeBuilder.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviorTreeBuilder::AutoMoDeBehaviorTreeBuilder() {
		m_unMaxTreeLevel = 5;
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviorTreeBuilder::~AutoMoDeBehaviorTreeBuilder() {
		delete cBehaviorTree;
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviorTree* AutoMoDeBehaviorTreeBuilder::BuildBehaviorTree(const std::string& str_bt_config) {
		std::istringstream iss(str_bt_config);
		std::vector<std::string> tokens;
		copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			std::back_inserter(tokens));
		return BuildBehaviorTree(tokens);
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviorTree* AutoMoDeBehaviorTreeBuilder::BuildBehaviorTree(std::vector<std::string>& vec_bt_config) {
		cBehaviorTree = new AutoMoDeBehaviorTree();
		Node* pcRootNode;

		// Get root node type and create root node.
		std::vector<std::string>::iterator it;
		try {
			it = std::find(vec_bt_config.begin(), vec_bt_config.end(), "--nroot");
			UInt8 unRootNodeType = atoi((*(it+1)).c_str());
			pcRootNode = GetNodeFromType(unRootNodeType);
		}
		catch (std::exception e) {
			THROW_ARGOSEXCEPTION("[Error while parsing]: Could not instanciate Root Node");
		}

		try {
			std::vector<std::string> vecRemainingTree(it+2, vec_bt_config.end());
			std::vector<std::vector<std::string> > vecBranches = ExtractBranches(vecRemainingTree);
			for (UInt8 i = 0; i < vecBranches.size(); i++) {
				pcRootNode->AddChildNode(ParseSubTree(vecBranches.at(i)));
			}
		}
		catch (std::exception e) {
			THROW_ARGOSEXCEPTION("[Error while parsing]: Error while parsing Root's childs");
		}

		cBehaviorTree->SetRootNode(pcRootNode);
		std::cout << "Parsing done succesfully!" << std::endl;
		return cBehaviorTree;
	}

	/****************************************/
	/****************************************/

	Node* AutoMoDeBehaviorTreeBuilder::ParseSubTree(std::vector<std::string>& vec_sub_tree) {
		Node* pcNode;
		std::ostringstream oss;
		std::vector<std::string>::iterator it;

		// std::cout << "Parsing subtree of size " << vec_sub_tree.size() << std::endl;
		// for (it=vec_sub_tree.begin(); it!=vec_sub_tree.end(); it++) {
		// 	std::cout << *(it) << " ";
		// }
		// std::cout << std::endl;

		std::string strNodeIdentifier = (*vec_sub_tree.begin()).substr(3, m_unMaxTreeLevel).c_str();
		UInt8 unNodeType = atoi((*(vec_sub_tree.begin()+1)).c_str());

		if (unNodeType < 5) {   // If not an action or condition
			pcNode = GetNodeFromType(unNodeType);
			oss << "--nchild" << strNodeIdentifier;
			it = std::find(vec_sub_tree.begin(), vec_sub_tree.end(), oss.str());
			if (it != vec_sub_tree.end()) {
				std::vector<std::string> vecRemainingTree(it, vec_sub_tree.end());
				std::vector<std::vector<std::string> > vecBranches = ExtractBranches(vecRemainingTree);
				for (UInt8 i = 0; i < vecBranches.size(); i++) {
					pcNode->AddChildNode(ParseSubTree(vecBranches.at(i)));
				}
			} else {
				THROW_ARGOSEXCEPTION("Error while parsing scheduling node");
			}
		} else if (unNodeType == 5) { // If an Action node
			// std::cout << "Action leaf reached" << std::endl;
			oss << "--a" << strNodeIdentifier;
			it = std::find(vec_sub_tree.begin(), vec_sub_tree.end(), oss.str());
			if (it != vec_sub_tree.end()) {
				std::vector<std::string> vecRemainingTree(it, vec_sub_tree.end());
				pcNode = HandleAction(vecRemainingTree);
			} else {
					THROW_ARGOSEXCEPTION("Error while parsing action");
			}
		} else if (unNodeType == 6) { // If a Condition node
			// std::cout << "Condition leaf reached" << std::endl;
			oss << "--c" << strNodeIdentifier;
			it = std::find(vec_sub_tree.begin(), vec_sub_tree.end(), oss.str());
			if (it != vec_sub_tree.end()) {
				std::vector<std::string> vecRemainingTree(it, vec_sub_tree.end());
				pcNode = HandleCondition(vecRemainingTree);
			} else {
				THROW_ARGOSEXCEPTION("Error while parsing action");
			}
		}
		pcNode->SetBranchId(strNodeIdentifier);
		return pcNode;
	}

	/****************************************/
	/****************************************/

	std::vector<std::vector<std::string> > AutoMoDeBehaviorTreeBuilder::ExtractBranches(std::vector<std::string>& vec_sub_tree) {
		std::vector<std::string>::iterator it;
		std::vector<std::vector<std::string> > vecBranches;
		UInt8 unNumberChilds = atoi((*(vec_sub_tree.begin()+1)).c_str());
		std::vector<std::string>::iterator first_child;
		std::vector<std::string>::iterator second_child;
		std::string strBranchIdentifier;
		if ( (*vec_sub_tree.begin()).compare("--nchildroot") == 0 ) {  // First node (aka root) case
			strBranchIdentifier = "";
		} else {
			strBranchIdentifier = (*vec_sub_tree.begin()).substr(8, m_unMaxTreeLevel+1).c_str(); // All other cases
		}

		for (UInt32 i = 0; i < unNumberChilds; i++) {
			std::ostringstream oss;
			oss << "--n" << strBranchIdentifier << i;
			first_child = std::find(vec_sub_tree.begin(), vec_sub_tree.end(), oss.str());
			if (i+1 < unNumberChilds) {
				std::ostringstream oss;
				oss << "--n" << strBranchIdentifier << i+1;
				second_child = std::find(vec_sub_tree.begin(), vec_sub_tree.end(), oss.str());
			} else {
				second_child = vec_sub_tree.end();
			}
			std::vector<std::string> vecChildConfig(first_child, second_child);
			vecBranches.push_back(vecChildConfig);
		}
		return vecBranches;
	}

	/****************************************/
	/****************************************/

	std::vector<std::string> AutoMoDeBehaviorTreeBuilder::TransformIntoSelectorSubtree(std::vector<std::string>& vec_action_config, std::string str_node_identifier) {
		std::vector<std::string> vecSelectorSubtree;
		std::ostringstream oss;
		oss << "--nchild" << str_node_identifier << " 2 --n" << str_node_identifier << "0 5 --af" << str_node_identifier << "0 ";
		oss << *(vec_action_config.begin() + 1) << " ";

		// Checking for parameters
		std::string vecPossibleParameters[] = {"rwm", "att", "rep", "cle", "clr", "vel", "exp", "mu", "rho"};//{"rwm", "att", "rep", "p", "r"};
		UInt8 unNumberPossibleParameters = sizeof(vecPossibleParameters) / sizeof(vecPossibleParameters[0]);
		std::vector<std::string>::iterator it;
		for (UInt8 i = 0; i < unNumberPossibleParameters; i++) {
			std::string strCurrentParameter = vecPossibleParameters[i];
			std::ostringstream oss_param;
			oss_param << "--" << strCurrentParameter << str_node_identifier;
			it = std::find(vec_action_config.begin(), vec_action_config.end(), oss_param.str());
			if (it != vec_action_config.end()) {
				Real fCurrentParameterValue = strtod((*(it+1)).c_str(), NULL);
				oss << oss_param.str().c_str() << "0 " << fCurrentParameterValue << " ";
			}
		}

		// Addition of Rotation action
		oss << "--n" << str_node_identifier << "1 5 --af" << str_node_identifier << "1 7 --p" << str_node_identifier << "1 0.0";
		//std::cout << oss.str().c_str() << std::endl;

		// Transforming stringstream to vector of strings
		std::istringstream iss(oss.str().c_str());
		copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(vecSelectorSubtree));
		return vecSelectorSubtree;
	}

	/****************************************/
	/****************************************/

	Action* AutoMoDeBehaviorTreeBuilder::HandleAction(std::vector<std::string>& vec_bt_action_config) {
		Action* pcActionNode = new Action();
		AutoMoDeBehaviour* pcNewBehaviour;
		std::string sPathToGenomeFile;
		std::string sPathToConfigurationFile = std::string(std::getenv("HOME")) + std::string("/.config/AutoMoDe_Harlequin.conf");
		std::ifstream cConfigurationFile(sPathToConfigurationFile.c_str());
		if (cConfigurationFile.is_open())
		{
			std::getline(cConfigurationFile, sPathToGenomeFile);
		}
		else
		{
			THROW_ARGOSEXCEPTION("Config file not found : Impossible to locate genes directory");
		}
		std::vector<std::string>::iterator it;
		// Extraction of the index of the node
		std::string strNodeIndex =  (*vec_bt_action_config.begin()).substr(3, m_unMaxTreeLevel+1).c_str();
		// Extraction of the identifier of the behaviour
		UInt8 unBehaviourIdentifier =  atoi((*(vec_bt_action_config.begin()+1)).c_str());

		// Creation of the Behaviour object
		switch(unBehaviourIdentifier) {
			case 10:
				pcNewBehaviour = new AutoMoDeBehaviourExplorationChocolate();
				break;
			case 11:
				pcNewBehaviour = new AutoMoDeBehaviourStopChocolate();
				break;
			case 12:
				pcNewBehaviour = new AutoMoDeBehaviourPhototaxisChocolate();
				break;
			case 13:
				pcNewBehaviour = new AutoMoDeBehaviourAntiPhototaxisChocolate();
				break;
			case 14:
				pcNewBehaviour = new AutoMoDeBehaviourAttractionChocolate();
				break;
			case 15:
				pcNewBehaviour = new AutoMoDeBehaviourRepulsionChocolate();
				break;
			case 20:
				pcNewBehaviour = new AutoMoDeBehaviourExplorationTuttifrutti();
				break;
			case 21:
				pcNewBehaviour = new AutoMoDeBehaviourStopTuttifrutti();
				break;
			case 24:
				pcNewBehaviour = new AutoMoDeBehaviourAttractionTuttifrutti();
				break;
			case 25:
				pcNewBehaviour = new AutoMoDeBehaviourRepulsionTuttifrutti();
				break;
			case 28:
				pcNewBehaviour = new AutoMoDeBehaviourGoToColorTuttifrutti();
				break;
			case 29:
				pcNewBehaviour = new AutoMoDeBehaviourGoAwayColorTuttifrutti();
				break;
			case 30:
				pcNewBehaviour = new AutoMoDeBehaviourExplorationCoconut();
				break;
			case 31:
				pcNewBehaviour = new AutoMoDeBehaviourStopChocolate();
				break;
			case 32:
				pcNewBehaviour = new AutoMoDeBehaviourPhototaxisCoconut();
				break;
			case 33:
				pcNewBehaviour = new AutoMoDeBehaviourAntiPhototaxisCoconut();
				break;
			case 34:
				pcNewBehaviour = new AutoMoDeBehaviourAttractionCoconut();
				break;
			case 35:
				pcNewBehaviour = new AutoMoDeBehaviourRepulsionCoconut();
				break;
			case 40:
				pcNewBehaviour = new AutoMoDeBehaviourExplorationChocolate();
				break;
			case 41:
				pcNewBehaviour = new AutoMoDeBehaviourStopChocolate();
				break;
			case 42:
				pcNewBehaviour = new AutoMoDeBehaviourPhototaxisChocolate();
				break;
			case 43:
				pcNewBehaviour = new AutoMoDeBehaviourAntiPhototaxisChocolate();
				break;
			case 44:
				pcNewBehaviour = new AutoMoDeBehaviourAttractionChocolate();
				break;
			case 45:
				pcNewBehaviour = new AutoMoDeBehaviourRepulsionChocolate();
				break;
			case 50:
				sPathToGenomeFile += "/gen/exploration";
				pcNewBehaviour = new AutoMoDeBehaviourGenomeHarlequin("Exploration", sPathToGenomeFile);
				break;
			case 51:
				sPathToGenomeFile += "/gen/stop";
				pcNewBehaviour = new AutoMoDeBehaviourGenomeHarlequin("Stop", sPathToGenomeFile);
				break;
			case 52:
				sPathToGenomeFile += "/gen/phototaxis";
				pcNewBehaviour = new AutoMoDeBehaviourGenomeHarlequin("Phototaxis", sPathToGenomeFile);
				break;
			case 53:
				sPathToGenomeFile += "/gen/antiphototaxis";
				pcNewBehaviour = new AutoMoDeBehaviourGenomeHarlequin("Antiphototaxis", sPathToGenomeFile);
				break;
			case 54:
				sPathToGenomeFile += "/gen/attraction";
				pcNewBehaviour = new AutoMoDeBehaviourGenomeHarlequin("Attraction", sPathToGenomeFile);
				break;
			case 55:
				sPathToGenomeFile += "/gen/repulsion";
				pcNewBehaviour = new AutoMoDeBehaviourGenomeHarlequin("Repulsion", sPathToGenomeFile);
				break;
		}
		pcNewBehaviour->SetIndex(0);
		pcNewBehaviour->SetIdentifier(unBehaviourIdentifier);

		// Checking for parameters
		std::string vecPossibleParameters[] = {"rwm", "att", "rep", "cle", "clr", "vel", "exp", "mu", "rho"};//{"rwm", "att", "rep", "p", "r"};
		UInt8 unNumberPossibleParameters = sizeof(vecPossibleParameters) / sizeof(vecPossibleParameters[0]);
		for (UInt8 i = 0; i < unNumberPossibleParameters; i++) {
			std::string strCurrentParameter = vecPossibleParameters[i];
			std::ostringstream oss;
			oss << "--" << strCurrentParameter << strNodeIndex;
			it = std::find(vec_bt_action_config.begin(), vec_bt_action_config.end(), oss.str());
			if (it != vec_bt_action_config.end()) {
				Real fCurrentParameterValue = strtod((*(it+1)).c_str(), NULL);
				pcNewBehaviour->AddParameter(strCurrentParameter, fCurrentParameterValue);
			}
		}
		pcNewBehaviour->Init();
		pcActionNode->SetBehaviour(pcNewBehaviour);
		return pcActionNode;
	}

	/****************************************/
	/****************************************/

	Condition* AutoMoDeBehaviorTreeBuilder::HandleCondition(std::vector<std::string>& vec_bt_condition_config){
		Condition* pcConditionNode = new Condition();
		AutoMoDeCondition* pcNewCondition;

		// Extraction of the index of the node
		std::string strNodeIndex =  (*vec_bt_condition_config.begin()).substr(3, m_unMaxTreeLevel).c_str();
		// Extract Condition identifier
		UInt32 unConditionIdentifier = atoi((*(vec_bt_condition_config.begin()+1)).c_str());

		switch(unConditionIdentifier) {
			case 10:
				pcNewCondition = new AutoMoDeConditionBlackFloorChocolate();
				break;
			case 11:
				pcNewCondition = new AutoMoDeConditionGrayFloorChocolate();
				break;
			case 12:
				pcNewCondition = new AutoMoDeConditionWhiteFloorChocolate();
				break;
			case 13:
				pcNewCondition = new AutoMoDeConditionNeighborsCountChocolate();
				break;
			case 14:
				pcNewCondition = new AutoMoDeConditionInvertedNeighborsCountChocolate();
				break;
			case 15:
				pcNewCondition = new AutoMoDeConditionFixedProbabilityChocolate();
				break;
			case 20:
				pcNewCondition = new AutoMoDeConditionBlackFloorChocolate();
				break;
			case 21:
				pcNewCondition = new AutoMoDeConditionGrayFloorChocolate();
				break;
			case 22:
				pcNewCondition = new AutoMoDeConditionWhiteFloorChocolate();
				break;
			case 23:
				pcNewCondition = new AutoMoDeConditionNeighborsCountChocolate();
				break;
			case 24:
				pcNewCondition = new AutoMoDeConditionInvertedNeighborsCountChocolate();
				break;
			case 25:
				pcNewCondition = new AutoMoDeConditionFixedProbabilityChocolate();
				break;
			case 27:
				pcNewCondition = new AutoMoDeConditionProbColorTuttifrutti();
				break;
			case 30:
				pcNewCondition = new AutoMoDeConditionBlackFloorChocolate();
				break;
			case 31:
				pcNewCondition = new AutoMoDeConditionGrayFloorChocolate();
				break;
			case 32:
				pcNewCondition = new AutoMoDeConditionWhiteFloorChocolate();
				break;
			case 33:
				pcNewCondition = new AutoMoDeConditionNeighborsCountChocolate();
				break;
			case 34:
				pcNewCondition = new AutoMoDeConditionInvertedNeighborsCountChocolate();
				break;
			case 35:
				pcNewCondition = new AutoMoDeConditionFixedProbabilityChocolate();
				break;
			case 40:
				pcNewCondition = new AutoMoDeConditionBlackFloorChocolate();
				break;
			case 41:
				pcNewCondition = new AutoMoDeConditionGrayFloorChocolate();
				break;
			case 42:
				pcNewCondition = new AutoMoDeConditionWhiteFloorChocolate();
				break;
			case 43:
				pcNewCondition = new AutoMoDeConditionNeighborsCountChocolate();
				break;
			case 44:
				pcNewCondition = new AutoMoDeConditionInvertedNeighborsCountChocolate();
				break;
			case 45:
				pcNewCondition = new AutoMoDeConditionFixedProbabilityChocolate();
				break;
			case 50:
				pcNewCondition = new AutoMoDeConditionBlackFloorChocolate();
				break;
			case 51:
				pcNewCondition = new AutoMoDeConditionGrayFloorChocolate();
				break;
			case 52:
				pcNewCondition = new AutoMoDeConditionWhiteFloorChocolate();
				break;
			case 53:
				pcNewCondition = new AutoMoDeConditionNeighborsCountChocolate();
				break;
			case 54:
				pcNewCondition = new AutoMoDeConditionInvertedNeighborsCountChocolate();
				break;
			case 55:
				pcNewCondition = new AutoMoDeConditionFixedProbabilityChocolate();
				break;
		}

		pcNewCondition->SetOriginAndExtremity(0, 0);  // No need of origin and extremity in cas of Behavior Trees. Set them to random value.
		pcNewCondition->SetIndex(0); // Same here, no need of index.
		pcNewCondition->SetIdentifier(unConditionIdentifier);


		// Checking for parameters
		std::vector<std::string>::iterator it;
		std::string vecPossibleParameters[] = {"p", "w", "l", "n"};//{"n", "w", "d"};
		UInt8 unNumberPossibleParameters = sizeof(vecPossibleParameters) / sizeof(vecPossibleParameters[0]);
		for (UInt8 i = 0; i < unNumberPossibleParameters; i++) {
			std::string strCurrentParameter = vecPossibleParameters[i];
			std::stringstream ssParamVariable;
			ssParamVariable << "--" << strCurrentParameter << strNodeIndex;
			it = std::find(vec_bt_condition_config.begin(), vec_bt_condition_config.end(), ssParamVariable.str());
			if (it != vec_bt_condition_config.end()) {
				Real fCurrentParameterValue = strtod((*(it+1)).c_str(), NULL);
				pcNewCondition->AddParameter(strCurrentParameter, fCurrentParameterValue);
			}
		}
		pcNewCondition->Init();

		pcConditionNode->SetCondition(pcNewCondition);
		return pcConditionNode;
	}

	/****************************************/
	/****************************************/

	Node* AutoMoDeBehaviorTreeBuilder::GetNodeFromType(UInt8 un_node_type) {
		Node* pcNode;
		switch(un_node_type) {
			case 0: {
				pcNode = new Selector();
				break;
			}
			case 1: {
				pcNode = new SelectorStar();
				break;
			}
			case 2: {
				pcNode = new Sequence();
				break;
			}
			case 3: {
				pcNode = new SequenceStar();
				break;
			}
			case 4: {
				pcNode = new NegationDecorator();
				break;
			}
			case 5: {
				pcNode = new Action();
				break;
			}
			case 6: {
				pcNode = new Condition();
				break;
			}
		}

		return pcNode;
	}
}
