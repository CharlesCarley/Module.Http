set(TargetName Html)
include(GroupSet)

set_group(Target_SRC 
    Source:*.cpp
    Header:*.h
)


include_directories(
    ${Utils_INCLUDE}
    ${Sockets_INCLUDE}
    ${Threads_INCLUDE}
    ${Http_INCLUDE}
)

add_library(
    ${TargetName}
    ${Target_SRC}
)

target_link_libraries(
    ${TargetName} 
    ${Utils_LIBRARY}
    ${Sockets_LIBRARY}
    ${Threads_LIBRARY}
    ${Http_LIBRARY}
)

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)
