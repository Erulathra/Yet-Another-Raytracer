# CPM - package manager
include(CPM)

CPMAddPackage("gh:S1NU5-P1/cpp-terminal-CPM#1.0.0")

set_target_properties(cpp-terminal PROPERTIES FOLDER "thirdparty")
