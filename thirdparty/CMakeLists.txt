# CPM - package manager
include(CPM)

CPMAddPackage("gh:gabime/spdlog@1.13.0")

set_target_properties(
        spdlog
        PROPERTIES FOLDER "thirdparty")
