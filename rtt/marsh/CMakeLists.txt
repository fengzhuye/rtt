
IF (PLUGINS_ENABLE_MARSHALLING)
  # Due to generation of some .h files in build directories, we also need to include some build dirs in our include paths.
  INCLUDE_DIRECTORIES(BEFORE ${PROJ_SOURCE_DIR} ${PROJ_SOURCE_DIR}/rtt ${PROJ_SOURCE_DIR}/rtt/os ${PROJ_SOURCE_DIR}/rtt/os/${OROCOS_TARGET} )
  INCLUDE_DIRECTORIES(BEFORE ${PROJ_BINARY_DIR}/rtt ${PROJ_BINARY_DIR}/rtt/os ${PROJ_BINARY_DIR}/rtt/os/${OROCOS_TARGET} )
  INCLUDE_DIRECTORIES(BEFORE ${PROJ_BINARY_DIR}/rtt/marsh )
  INCLUDE_DIRECTORIES(BEFORE ${PROJ_BINARY_DIR}/rtt/typekit ) # For rtt-typekit-config.h

  GLOBAL_ADD_INCLUDE( rtt/marsh PropertyMarshaller.hpp PropertyDemarshaller.hpp MarshallInterface.hpp MarshallingService.hpp PropertyBagIntrospector.hpp)
  SET( CPPS PropertyMarshaller.cpp PropertyDemarshaller.cpp PropertyBagIntrospector.cpp)

  GLOBAL_ADD_INCLUDE( rtt/marsh CPFMarshaller.hpp
           XMLRPCDemarshaller.hpp XMLRPCMarshaller.hpp CPFDTD.hpp
           StreamProcessor.hpp Marshalling.hpp PropertyLoader.hpp)
  list(APPEND CPPS CPFDTD.cpp CPFMarshaller.cpp Marshalling.cpp MarshallingService.cpp PropertyLoader.cpp)

  IF (XERCES_FOUND AND NOT OS_NOEXCEPTIONS)
    GLOBAL_ADD_INCLUDE( rtt/marsh CPFDemarshaller.hpp)
    list(APPEND CPPS  CPFDemarshaller.cpp )
  ELSE (XERCES_FOUND AND NOT OS_NOEXCEPTIONS)
    GLOBAL_ADD_INCLUDE( rtt/marsh TinyDemarshaller.hpp )
    list(APPEND CPPS  TinyDemarshaller.cpp tinyxml.cpp tinyxmlparser.cpp tinyxmlerror.cpp tinystr.cpp )
  ENDIF (XERCES_FOUND AND NOT OS_NOEXCEPTIONS)
  
  SET(RTT_DEFINITIONS ${OROCOS-RTT_DEFINITIONS})
  set(DLL_EXPORT_PREFIX marsh)
  ADD_RTT_PLUGIN( rtt-marshalling ${RTT_VERSION} ${CPPS})
  GLOBAL_ADD_INCLUDE( rtt/marsh ${CMAKE_CURRENT_BINARY_DIR}/rtt-marsh-config.h)
  target_link_libraries( rtt-marshalling-${OROCOS_TARGET}_plugin )
  
ENDIF(PLUGINS_ENABLE_MARSHALLING)
