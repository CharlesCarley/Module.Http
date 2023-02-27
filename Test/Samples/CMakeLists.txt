include(CopyTargets)
include(TestDirectory)
include(GroupSet)

gen_path_to_here()


macro(make_exe TargetName)
    set(TargetGroup Examples)

    include_directories(
        ${Http_INCLUDE}
        ${Sockets_INCLUDE}
        ${Utils_INCLUDE}
        ${Threads_INCLUDE}
        ${ParserBase_INCLUDE}
    )
    add_executable(${TargetName} ${ARGN})
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


set_group(Basic_SRC
    Source:Samp001.cpp
    Site:Samp001/*.css
    Site:Samp001/*.html
    Site:Samp001/*.svg
)

make_exe(Basic ${Basic_SRC})

