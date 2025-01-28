
cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project(TEST)
enable_testing()

#Prep ourselves for compiling boost
find_package(Boost COMPONENTS 
    unit_test_framework REQUIRED
    system REQUIRED
    thread REQUIRED
)

if (APPLE AND NOT IOS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default")
  if (NOT OpenSSL_DIR)
      EXECUTE_PROCESS(COMMAND brew --prefix openssl
        OUTPUT_VARIABLE OPENSSL_ROOT_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    message(STATUS "Using OpenSSL found at ${OPENSSL_ROOT_DIR}")
  endif()
endif()

find_package(OpenSSL REQUIRED)

set(BELDEX_SRC "contrib/beldex-core-custom")

# add_subdirectory(${BELDEX_SRC}/external/easylogging++)

include_directories(${Boost_INCLUDE_DIRS})
include_directories("src")
include_directories(${BELDEX_SRC})
include_directories("${BELDEX_SRC}/external")
include_directories("${BELDEX_SRC}/external/loki-mq")
include_directories("${BELDEX_SRC}/external/easylogging++")
include_directories("${BELDEX_SRC}/epee/include")
include_directories("${BELDEX_SRC}/common")
include_directories("${BELDEX_SRC}/vtlogger")
include_directories("${BELDEX_SRC}/crypto")
include_directories("${BELDEX_SRC}/cryptonote_basic")
include_directories("${BELDEX_SRC}/multisig")
include_directories("${BELDEX_SRC}/cryptonote_core")
include_directories("${BELDEX_SRC}/cryptonote_protocol")
include_directories("${BELDEX_SRC}/wallet")
include_directories("${BELDEX_SRC}/rpc")
include_directories("${BELDEX_SRC}/mnemonics")
include_directories("${BELDEX_SRC}/contrib/libsodium/include") # support sodium/… paths
include_directories("${BELDEX_SRC}/contrib/libsodium/include/sodium")
include_directories("test")

# keeping test files in a separate source directory 
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/test_*.cpp)

set(
    SRC_FILES
    #
    src/beldex_address_utils.hpp
    src/beldex_address_utils.cpp
    src/beldex_paymentID_utils.hpp
    src/beldex_paymentID_utils.cpp
    src/beldex_key_image_utils.hpp
    src/beldex_key_image_utils.cpp
    src/beldex_fee_utils.hpp
    src/beldex_fee_utils.cpp
    src/beldex_transfer_utils.hpp
    src/beldex_transfer_utils.cpp
    src/beldex_send_routine.hpp
    src/beldex_send_routine.cpp
    src/beldex_fork_rules.hpp
    src/beldex_fork_rules.cpp
    src/beldex_wallet_utils.hpp
    src/beldex_wallet_utils.cpp
    src/serial_bridge_index.hpp
    src/serial_bridge_index.cpp
    src/serial_bridge_utils.hpp
    src/serial_bridge_utils.cpp
    src/tools__ret_vals.hpp
    src/tools__ret_vals.cpp
    src/register_mn_data.hpp
    #
    ${BELDEX_SRC}/cryptonote_basic/cryptonote_basic_impl.cpp
    ${BELDEX_SRC}/cryptonote_basic/account.cpp
    ${BELDEX_SRC}/cryptonote_basic/cryptonote_format_utils.cpp
    ${BELDEX_SRC}/cryptonote_basic/cryptonote_basic.cpp
    ${BELDEX_SRC}/crypto/crypto.cpp
    ${BELDEX_SRC}/crypto/hash.c
    ${BELDEX_SRC}/crypto/cn_heavy_hash_hard_arm.cpp
    ${BELDEX_SRC}/crypto/cn_heavy_hash_hard_intel.cpp
    ${BELDEX_SRC}/crypto/cn_heavy_hash_soft.cpp
    ${BELDEX_SRC}/crypto/cn_turtle_hash.c
    ${BELDEX_SRC}/crypto/oaes_lib.c
    ${BELDEX_SRC}/crypto/crypto-ops.c
    ${BELDEX_SRC}/crypto/crypto-ops-data.c
    ${BELDEX_SRC}/crypto/keccak.c
    ${BELDEX_SRC}/crypto/chacha.c
    ${BELDEX_SRC}/crypto/random.c
    ${BELDEX_SRC}/crypto/aesb.c
    ${BELDEX_SRC}/crypto/tree-hash.c
    ${BELDEX_SRC}/crypto/hash-extra-blake.c
    ${BELDEX_SRC}/crypto/blake256.c
    ${BELDEX_SRC}/crypto/hash-extra-groestl.c
    ${BELDEX_SRC}/crypto/hash-extra-jh.c
    ${BELDEX_SRC}/crypto/hash-extra-skein.c
    ${BELDEX_SRC}/crypto/groestl.c
    ${BELDEX_SRC}/crypto/jh.c
    ${BELDEX_SRC}/crypto/skein.c
    ${BELDEX_SRC}/cryptonote_core/cryptonote_tx_utils.cpp
    ${BELDEX_SRC}/common/base58.cpp
    ${BELDEX_SRC}/common/threadpool.cpp
    ${BELDEX_SRC}/common/aligned.c
    ${BELDEX_SRC}/common/util.cpp
    ${BELDEX_SRC}/common/i18n.cpp
    ${BELDEX_SRC}/common/string_util.cpp
    ${BELDEX_SRC}/epee/src/hex.cpp
    ${BELDEX_SRC}/epee/src/string_tools.cpp
    ${BELDEX_SRC}/epee/src/portable_storage.cpp
    ${BELDEX_SRC}/epee/src/memwipe.c
    ${BELDEX_SRC}/epee/src/mlocker.cpp
    ${BELDEX_SRC}/epee/src/wipeable_string.cpp
    ${BELDEX_SRC}/device/device.cpp
    ${BELDEX_SRC}/device/device_default.cpp
    ${BELDEX_SRC}/ringct/rctOps.cpp
    ${BELDEX_SRC}/ringct/rctTypes.cpp
    ${BELDEX_SRC}/ringct/rctCryptoOps.c
    ${BELDEX_SRC}/ringct/rctSigs.cpp
    ${BELDEX_SRC}/ringct/bulletproofs.cc
    ${BELDEX_SRC}/ringct/multiexp.cc
    ${BELDEX_SRC}/mnemonics/electrum-words.cpp
    ${BELDEX_SRC}/vtlogger/logger.cpp
    ${BELDEX_SRC}/contrib/libsodium/src/crypto_verify/verify.c
)
# needed for slow-hash
add_compile_options(-maes)

add_compile_definitions(BELDEX_CORE_CUSTOM)

#Run through each source
foreach(testSrc ${TEST_SRCS})
    # extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testSrc} NAME_WE)
    add_executable(
        ${testName}
        ${testSrc}
        ${SRC_FILES}
    )
    target_link_libraries(
        ${testName}
        #
        ${Boost_LIBRARIES}
        OpenSSL::SSL
        OpenSSL::Crypto 
    )
    set_target_properties(
        ${testName} PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/build/products
    )
    add_test(
        NAME ${testName} 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/products 
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build/products/${testName} --catch_system_error=yes
    )
endforeach(testSrc)