# Set up ARGoS compilation information
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS})
link_directories(${ARGOS_LIBRARY_DIRS})

# Headers
set(AUTOMODE_HEADERS
	core/AutoMoDeController.h
	core/AutoMoDeFiniteStateMachine.h
	core/AutoMoDeFsmBuilder.h
	core/AutoMoDeFsmHistory.h
	# Behaviours
	modules/AutoMoDeBehaviour.h
	modules/AutoMoDeBehaviourAntiPhototaxis.h
	modules/AutoMoDeBehaviourPhototaxis.h
	modules/AutoMoDeBehaviourAttraction.h
	modules/AutoMoDeBehaviourAttractionTuttifrutti.h
	modules/AutoMoDeBehaviourRepulsion.h
	modules/AutoMoDeBehaviourRepulsionTuttifrutti.h
	modules/AutoMoDeBehaviourStop.h
	modules/AutoMoDeBehaviourStopTuttifrutti.h
	modules/AutoMoDeBehaviourExploration.h
	modules/AutoMoDeBehaviourExplorationTuttifrutti.h
	modules/AutoMoDeBehaviourGoAwayColorTuttifrutti.h
	modules/AutoMoDeBehaviourGoToColorTuttifrutti.h
	# Conditions
	modules/AutoMoDeCondition.h
	modules/AutoMoDeConditionBlackFloor.h
	modules/AutoMoDeConditionWhiteFloor.h
	modules/AutoMoDeConditionGrayFloor.h
	modules/AutoMoDeConditionNeighborsCount.h
	modules/AutoMoDeConditionInvertedNeighborsCount.h
	modules/AutoMoDeConditionFixedProbability.h
	modules/AutoMoDeConditionProbColorTuttifrutti.h)

# Sources
set(AUTOMODE_SOURCES
	core/AutoMoDeController.cpp
	core/AutoMoDeFiniteStateMachine.cpp
	core/AutoMoDeFsmBuilder.cpp
	core/AutoMoDeFsmHistory.cpp
	# Behaviours
	modules/AutoMoDeBehaviour.cpp
	modules/AutoMoDeBehaviourAntiPhototaxis.cpp
	modules/AutoMoDeBehaviourPhototaxis.cpp
	modules/AutoMoDeBehaviourAttraction.cpp
	modules/AutoMoDeBehaviourAttractionTuttifrutti.cpp
	modules/AutoMoDeBehaviourRepulsion.cpp
	modules/AutoMoDeBehaviourRepulsionTuttifrutti.cpp
	modules/AutoMoDeBehaviourStop.cpp
	modules/AutoMoDeBehaviourStopTuttifrutti.cpp
	modules/AutoMoDeBehaviourExploration.cpp
	modules/AutoMoDeBehaviourExplorationTuttifrutti.cpp
	modules/AutoMoDeBehaviourGoAwayColorTuttifrutti.cpp
	modules/AutoMoDeBehaviourGoToColorTuttifrutti.cpp
	# Conditions
	modules/AutoMoDeCondition.cpp
	modules/AutoMoDeConditionBlackFloor.cpp
	modules/AutoMoDeConditionWhiteFloor.cpp
	modules/AutoMoDeConditionGrayFloor.cpp
	modules/AutoMoDeConditionNeighborsCount.cpp
	modules/AutoMoDeConditionInvertedNeighborsCount.cpp
	modules/AutoMoDeConditionFixedProbability.cpp
	modules/AutoMoDeConditionProbColorTuttifrutti.cpp)

add_executable(automode ${AUTOMODE_HEADERS} ${AUTOMODE_SOURCES})
target_link_libraries(automode argos3plugin_${ARGOS_BUILD_FOR}_epuck)
