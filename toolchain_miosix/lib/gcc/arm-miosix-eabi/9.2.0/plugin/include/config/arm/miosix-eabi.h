
/*
 * RATIONALE: adding builtin_define to always define _MIOSIX
 * - when libgcc/libstdc++/newlib are compiled, as there are some #ifdef _MIOSIX
 * - when Miosix processes are compiled, to allow #ifdef _MIOSIX
 * Also add versioning to miosix-specific compiler patches.
 * Note: intentionally breaking compatibility with previous compiler patches
 * which defined _MIOSIX_GCC_PATCH_VERSION instead of _MIOSIX_GCC_PATCH_MAJOR
 */

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()         \
    do {                                 \
        TARGET_BPABI_CPP_BUILTINS();     \
        builtin_define("_MIOSIX");       \
        builtin_define("_MIOSIX_GCC_PATCH_MAJOR=3"); \
        builtin_define("_MIOSIX_GCC_PATCH_MINOR=1"); \
        builtin_assert("system=miosix"); \
    } while(false)
