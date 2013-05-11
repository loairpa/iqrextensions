SET(CMAKE_INSTALL_PREFIX /opt/iqr)

IF(APPLE)
SET(CMAKE_CXX_FLAGS 
"${CMAKE_CXX_FLAGS}  -undefined dynamic_lookup"
)                           
ENDIF(APPLE)
SET (AdaptiveIntegrateFireModSrc neuronAdaptiveIntegrateFireMod.cpp)
SET (AdaptiveIntegrateFireSrc neuronAdaptiveIntegrateFire.cpp)


INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../
)


ADD_LIBRARY(neuronAdaptiveIntegrateFireMod SHARED ${AdaptiveIntegrateFireModSrc})
ADD_LIBRARY(neuronAdaptiveIntegrateFire SHARED ${AdaptiveIntegrateFireSrc})



SET_TARGET_PROPERTIES(neuronAdaptiveIntegrateFireMod PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(neuronAdaptiveIntegrateFire PROPERTIES PREFIX "")


#this is a nasty hack for minGW...
IF(WIN32)
  TARGET_LINK_LIBRARIES(neuronAdaptiveIntegrateFire
  ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Item/libIqrItem.dll
  )

  TARGET_LINK_LIBRARIES(neuronIntegrateFire
  ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Item/libIqrItem.dll
  )

  TARGET_LINK_LIBRARIES(neuronLeakyIntegrateFire
  ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Item/libIqrItem.dll
  )

  TARGET_LINK_LIBRARIES(neuronLinearThreshold
  ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Item/libIqrItem.dll
  )

  TARGET_LINK_LIBRARIES(neuronPyramidApicalShunt
  ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Item/libIqrItem.dll
  )

  TARGET_LINK_LIBRARIES(neuronRandomSpike
  ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Item/libIqrItem.dll
  )

  TARGET_LINK_LIBRARIES(neuronSigmoid
  ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Item/libIqrItem.dll
  )

ENDIF(WIN32)

IF(UNIX)
  INSTALL(TARGETS 
   neuronAdaptiveIntegrateFireMod
    neuronAdaptiveIntegrateFire

    LIBRARY DESTINATION lib/iqr/Neurons/ 
    ARCHIVE DESTINATION lib/iqr/Neurons/
    RUNTIME DESTINATION bin 
  )
ENDIF(UNIX)

IF(WIN32)
  INSTALL(TARGETS 
    neuronAdaptiveIntegrateFireMod
    neuronAdaptiveIntegrateFire

    LIBRARY DESTINATION Neurons/ COMPONENT types 
    ARCHIVE DESTINATION Neurons/ 
    RUNTIME DESTINATION Neurons/ COMPONENT types 
  )
ENDIF(WIN32)
