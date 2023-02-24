set(TargetName Http)
include(GroupSet)

set_group(Target_SRC 
    Source:*.cpp
    Source/Request:Request/*.cpp
    Source/Response:Response/*.cpp
    Source/Uri:Uri/*.cpp
    Header:*.h
    Header/Request:Request/*.h
    Header/Response:Response/*.h
    Header/Uri:Uri/*.h
)


include_directories(
    ${Utils_INCLUDE}
    ${Http_INCLUDE}
    ${Sockets_INCLUDE}
    ${ParserBase_INCLUDE}
)

add_library(
    ${TargetName}
    ${Target_SRC}
)

target_link_libraries(
    ${TargetName} 
    ${Utils_LIBRARY}
    ${Sockets_LIBRARY}
    ${ParserBase_LIBRARY}
)

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)
