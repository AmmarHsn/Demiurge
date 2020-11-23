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
	modules/AutoMoDeBehaviourAttraction3Dot0.h
	modules/AutoMoDeBehaviourRepulsion.h
	modules/AutoMoDeBehaviourRepulsion3Dot0.h
	modules/AutoMoDeBehaviourStop.h
	modules/AutoMoDeBehaviourStop3Dot0.h
	modules/AutoMoDeBehaviourExploration.h
	modules/AutoMoDeBehaviourExploration3Dot0.h
	modules/AutoMoDeBehaviourGoAwayColor3Dot0.h
	modules/AutoMoDeBehaviourGoToColor3Dot0.h
	# Conditions
	modules/AutoMoDeCondition.h
	modules/AutoMoDeConditionBlackFloor.h
	modules/AutoMoDeConditionWhiteFloor.h
	modules/AutoMoDeConditionGrayFloor.h
	modules/AutoMoDeConditionNeighborsCount.h
	modules/AutoMoDeConditionInvertedNeighborsCount.h
	modules/AutoMoDeConditionFixedProbability.h
	modules/AutoMoDeConditionProbColor3Dot0.h)

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
	modules/AutoMoDeBehaviourAttraction3Dot0.cpp
	modules/AutoMoDeBehaviourRepulsion.cpp
	modules/AutoMoDeBehaviourRepulsion3Dot0.cpp
	modules/AutoMoDeBehaviourStop.cpp
	modules/AutoMoDeBehaviourStop3Dot0.cpp
	modules/AutoMoDeBehaviourExploration.cpp
	modules/AutoMoDeBehaviourExploration3Dot0.cpp
	modules/AutoMoDeBehaviourGoAwayColor3Dot0.cpp
	modules/AutoMoDeBehaviourGoToColor3Dot0.cpp
	# Conditions
	modules/AutoMoDeCondition.cpp
	modules/AutoMoDeConditionBlackFloor.cpp
	modules/AutoMoDeConditionWhiteFloor.cpp
	modules/AutoMoDeConditionGrayFloor.cpp
	modules/AutoMoDeConditionNeighborsCount.cpp
	modules/AutoMoDeConditionInvertedNeighborsCount.cpp
	modules/AutoMoDeConditionFixedProbability.cpp
	modules/AutoMoDeConditionProbColor3Dot0.cpp)

add_executable(automode ${AUTOMODE_HEADERS} ${AUTOMODE_SOURCES})
target_link_libraries(automode argos3plugin_${ARGOS_BUILD_FOR}_epuck)
