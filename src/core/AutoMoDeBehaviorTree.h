/*
 * @file <src/core/AutoMoDeBehaviorTree.h>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 *
 * @brief
 */

#ifndef AUTOMODE_BEHAVIOR_TREE_H
#define AUTOMODE_BEHAVIOR_TREE_H

#include "bt/Node.h"
#include "bt/Action.h"
#include "bt/Condition.h"
#include "bt/NegationDecorator.h"
#include "bt/Selector.h"
#include "bt/SelectorStar.h"
#include "bt/Sequence.h"
#include "bt/SequenceStar.h"
#include "../modules/AutoMoDeBehaviour.h"
#include "../modules/AutoMoDeBehaviourAttractionChocolate.h"
#include "../modules/AutoMoDeBehaviourAttractionCoconut.h"
#include "../modules/AutoMoDeBehaviourAttractionTuttifrutti.h"
#include "../modules/AutoMoDeBehaviourAntiPhototaxisChocolate.h"
#include "../modules/AutoMoDeBehaviourAntiPhototaxisCoconut.h"
#include "../modules/AutoMoDeBehaviourExplorationChocolate.h"
#include "../modules/AutoMoDeBehaviourExplorationCoconut.h"
#include "../modules/AutoMoDeBehaviourExplorationTuttifrutti.h"
#include "../modules/AutoMoDeBehaviourPhototaxisChocolate.h"
#include "../modules/AutoMoDeBehaviourPhototaxisCoconut.h"
#include "../modules/AutoMoDeBehaviourRepulsionChocolate.h"
#include "../modules/AutoMoDeBehaviourRepulsionCoconut.h"
#include "../modules/AutoMoDeBehaviourRepulsionTuttifrutti.h"
#include "../modules/AutoMoDeBehaviourStopChocolate.h"
#include "../modules/AutoMoDeBehaviourStopTuttifrutti.h"
#include "../modules/AutoMoDeBehaviourGoToColorTuttifrutti.h"
#include "../modules/AutoMoDeBehaviourGoAwayColorTuttifrutti.h"
#include "../modules/AutoMoDeCondition.h"
#include "../modules/AutoMoDeConditionBlackFloor.h"
#include "../modules/AutoMoDeConditionGrayFloor.h"
#include "../modules/AutoMoDeConditionWhiteFloor.h"
#include "../modules/AutoMoDeConditionFixedProbability.h"
#include "../modules/AutoMoDeConditionNeighborsCount.h"
#include "../modules/AutoMoDeConditionInvertedNeighborsCount.h"
#include "../modules/AutoMoDeConditionProbColorTuttifrutti.h"

#include <string>
#include <ctime>
#include <algorithm>

namespace argos {
	class AutoMoDeBehaviorTree {

		public:

			/*
			 * Class constructor.
			 */
			AutoMoDeBehaviorTree();

			/*
			 * Class destructor.
			 */
			virtual ~AutoMoDeBehaviorTree();

			/*
			 * Copy constructor.
			 */
			AutoMoDeBehaviorTree(const AutoMoDeBehaviorTree* pc_fsm);

			/*
			 * Initialize the Behavior Tree.
			 */
			void Init();

			/*
			 * Reset the Behavior Tree.
			 */
			void Reset();

			void ControlStep();

			const UInt32& GetTimeStep() const;

			const std::string GetReadableFormat();

			void SetRootNode(Node* pc_root_node);

			Node* GetRootNode() const;

			void ShareRobotDAO();

			void SetRobotDAO(EpuckDAO* m_pcRobotDAO);

		private:

			Node* m_pcRootNode;

			/*
			 * Pointer to the object representing the state of the robot.
			 * @see EpuckDAO.
			 */
			EpuckDAO* m_pcRobotDAO;

			UInt32 m_unTimeStep;

			Node::ReturnState m_eTreeStatus;

	};
}

#endif
