# Install script for directory: C:/Users/Andrey/Desktop/open62541-1_4_10/open62541

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/open62541")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/bin/Debug/open62541.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/bin/Release/open62541.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/bin/MinSizeRel/open62541.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/bin/RelWithDebInfo/open62541.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/bin/Debug/open62541.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/bin/Release/open62541.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/bin/MinSizeRel/open62541.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/bin/RelWithDebInfo/open62541.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES
    "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/open62541Config.cmake"
    "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/tools/cmake/open62541Macros.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/open62541ConfigVersion.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541/open62541Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541/open62541Targets.cmake"
         "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541/open62541Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541/open62541Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/open62541" TYPE DIRECTORY FILES
    "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/tools/certs"
    "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/tools/nodeset_compiler"
    FILES_MATCHING REGEX "/[^/]*$" REGEX "/\\_\\_pycache\\_\\_$" EXCLUDE REGEX "/[^/]*\\.pyc$" EXCLUDE REGEX "/\\.git[^/]*$" EXCLUDE PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/open62541/schema" TYPE DIRECTORY FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/tools/schema/" FILES_MATCHING REGEX "/[^/]*\\.xml$" REGEX "/[^/]*types\\.bsd$" REGEX "/statuscode\\.csv$" REGEX "/nodeids\\.csv$" PERMISSIONS OWNER_READ GROUP_READ)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/open62541" TYPE FILE PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE FILES
    "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/tools/generate_datatypes.py"
    "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/tools/generate_nodeid_header.py"
    "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/tools/generate_statuscode_descriptions.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/src_generated/open62541/config.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/src_generated/open62541/statuscodes.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/src_generated/open62541/nodeids.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/common.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/types.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/src_generated/open62541/types_generated.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/src_generated/open62541/types_generated_handling.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/util.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/plugin/log.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/plugin/accesscontrol.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/plugin/pki.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/plugin/securitypolicy.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/plugin/eventloop.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/plugin/nodestore.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/plugin/historydatabase.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/server_pubsub.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/client.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/server.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/client_highlevel.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/client_subscriptions.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/include/open62541/client_highlevel_async.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/plugin/accesscontrol_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/plugin/pki_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/plugin/log_stdout.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/plugin/nodestore_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/server_config_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/client_config_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/plugin/securitypolicy_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/server_config_file_based.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin/historydata" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/plugin/historydata/history_data_backend.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin/historydata" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/plugin/historydata/history_data_gathering.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin/historydata" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/plugin/historydata/history_database_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin/historydata" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/plugin/historydata/history_data_gathering_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin/historydata" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/plugin/historydata/history_data_backend_memory.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541/plugins/include/open62541/plugin/create_certificate.h")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/doc/cmake_install.cmake")
  include("C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/examples/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Andrey/Desktop/open62541-1_4_10/open62541-build64/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
