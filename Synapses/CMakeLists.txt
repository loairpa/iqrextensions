SET(CMAKE_INSTALL_PREFIX /opt/iqr)
SET(CMAKE_VERBOSE_MAKEFILE TRUE) 


IF(APPLE)
SET(CMAKE_CXX_FLAGS 
"${CMAKE_CXX_FLAGS}  -undefined dynamic_lookup"
)                           
ENDIF(APPLE)



SET (ExponentialSrc        synapseExponential.cpp)
SET (synpsemodulatefeedbackSrc synapsemodulatefeedback.cpp)
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../
)


ADD_LIBRARY(synapseExponential        SHARED ${ExponentialSrc})
ADD_LIBRARY(synapseHebbian  	      SHARED ${HebbianSrc})  	     
ADD_LIBRARY(synapsemodulatefeedback   SHARED ${synpsemodulatefeedbackSrc})



SET_TARGET_PROPERTIES(synapseExponential PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(synapsemodulatefeedback PROPERTIES PREFIX "")


#this is a nasty hack for minGW...
IF(WIN32)


  TARGET_LINK_LIBRARIES(synapseExponential
  ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Item/libIqrItem.dll
  )

  TARGET_LINK_LIBRARIES(synapsemodulatefeedback
  ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Item/libIqrItem.dll
  )
ENDIF(WIN32)

IF(UNIX)
  INSTALL(TARGETS 
    synapseExponential
    synapsemodulatefeedback
    LIBRARY DESTINATION lib/iqr/Synapses/ 
    ARCHIVE DESTINATION lib/iqr/Synapses/
    RUNTIME DESTINATION bin 
  )
ENDIF(UNIX)

IF(WIN32)
  INSTALL(TARGETS  
    synapseExponential
    synapsemodulatefeedback
    LIBRARY DESTINATION Synapses/ COMPONENT types 
    ARCHIVE DESTINATION Synapses/
    RUNTIME DESTINATION Synapses/ COMPONENT types 
  )
ENDIF(WIN32)
