set(TargetName Http)
include(GroupSet)

set_group(Target_SRC 
    Source:*.cpp
    Header:*.h
)


include_directories(
    ${Utils_INCLUDE}
    ${Http_INCLUDE}
    ${Sockets_INCLUDE}
)

add_library(
    ${TargetName}
    ${Target_SRC}
)

target_link_libraries(
    ${TargetName} 
    ${Utils_LIBRARY}
    ${Sockets_LIBRARY}
)

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)
