include(CopyTargets)
include(TestDirectory)

gen_path_to_here()


macro(make_exe TargetName MAIN)
    set(TargetGroup Examples)

    include_directories(
        ${Http_INCLUDE}
        ${Sockets_INCLUDE}
        ${Utils_INCLUDE}
        ${Threads_INCLUDE}
        ${ParserBase_INCLUDE}
    )
    add_executable(${TargetName} ${MAIN})
    target_link_libraries(
        ${TargetName} 
        ${Http_LIBRARY}
        ${Sockets_LIBRARY}
        ${Utils_LIBRARY}
        ${Threads_LIBRARY}
        ${ParserBase_LIBRARY}
    )
    set_target_properties(${TargetName} PROPERTIES FOLDER "${TargetGroup}")

    copy_target(${TargetName} ${CMAKE_BINARY_DIR})
endmacro()



make_exe(Basic Samp001.cpp)

