IK_GetTargetName(core "${PROJECT_SOURCE_DIR}/src/core")
IK_AddTarget(
    TEST
    MODE EXE
    LIB "${core}"
)