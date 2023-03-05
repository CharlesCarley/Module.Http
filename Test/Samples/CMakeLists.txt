include(CopyTargets)
include(TestDirectory)
include(GroupSet)
include(TargetDebugOptions)

gen_path_to_here()


macro(make_exe TargetName)
    set(TargetGroup Examples)

    include_directories(
        ${Http_INCLUDE}
        ${Html_INCLUDE}
        ${Sockets_INCLUDE}
        ${Utils_INCLUDE}
        ${Threads_INCLUDE}
        ${ParserBase_INCLUDE}
    )
    add_executable(${TargetName} 
        ${ARGN})
    
    target_link_libraries(
        ${TargetName} 
        ${Html_LIBRARY}
        ${Http_LIBRARY}
        ${Sockets_LIBRARY}
        ${Utils_LIBRARY}
        ${Threads_LIBRARY}
        ${ParserBase_LIBRARY}
    )

    set_target_properties(
        ${TargetName} 
        PROPERTIES FOLDER "${TargetGroup}"
    )

    copy_target(${TargetName} ${CMAKE_BINARY_DIR})
endmacro()


set_group(Sample_01_SRC
    Source:Samp001.cpp
    Site:Samp001/*.html
    Site/css:Samp001/css/*.css
)
make_exe(Sample_01 ${Sample_01_SRC})


set_group(Sample_02_SRC
    Source:Samp002.cpp
    Site:Sample002/*.html
    Site/css:Sample002/.content/css/*.css
)
make_exe(Sample_02 ${Sample_02_SRC})
target_debug(Sample_02 
    ${CMAKE_CURRENT_SOURCE_DIR}
    "--host 127.0.0.1:5000 --root ${CMAKE_CURRENT_SOURCE_DIR}/Sample002/ --browse F://Internal/"
)
