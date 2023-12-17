/* ********************************
 * Author:       Zhanglele
 * Description:  单元测试框架
 * create time: 2022.4.17
 ********************************/
#ifndef UNITTEST_H
#define UNITTEST_H

#include <stdint.h>
#include <stdbool.h>
#include "unittest_print.h"
#include "unittest_inner.h"


/* 定义测试套准备函数 */
#define TEST_SETUP(group) \
    void TEST_##group##_SETUP(void)

/* 定义测试套析构函数 */
#define TEST_TEAR_DOWN(group) \
    void TEST_##group##_TEAR_DOWN(void)

/* 定义测试用例准备函数 */
#define TEST_CASE_SETUP(group) \
    void TEST_##group##_CASE_SETUP(void)

/* 定义测试用例销毁函数 */
#define TEST_CASE_TEAR_DOWN(group) \
    void TEST_##group##_CASE_TEAR_DOWN(void)

/* 定义测试套用例 */
#define TEST_SUITE_RUNNER(groupval) \
    void TEST_##groupval##_(void); \
    void TEST_##groupval##_SETUP(void); \
    void TEST_##groupval##_TEAR_DOWN(void); \
    void TEST_##groupval##_RUN(void) \
    { \
        unit_test_suite_t test_suite =  {\
            .setup = TEST_##groupval##_SETUP, \
            .test_body = TEST_##groupval##_, \
            .tear_down = TEST_##groupval##_TEAR_DOWN, \
            .group = #groupval, \
        };\
        unit_test_suite_runner(&test_suite); \
    } \
    void TEST_##groupval##_(void)

/* 运行测试套 */
#define RUN_TEST_SUITE(groupval) \
    TEST_##groupval##_RUN();

/* 定义测试用例 */
#define TEST(groupval, nameval) \
    void TEST_##groupval##_##nameval##_(void); \
    void TEST_##groupval##_CASE_SETUP(void); \
    void TEST_##groupval##_CASE_TEAR_DOWN(void); \
    void TEST_##groupval##_##nameval##_RUN(void) \
    { \
        unit_test_case_t test_case =  {\
            .setup = TEST_##groupval##_CASE_SETUP, \
            .test_body = TEST_##groupval##_##nameval##_, \
            .tear_down = TEST_##groupval##_CASE_TEAR_DOWN, \
            .group = #groupval, \
            .name = #nameval \
        };\
        unit_test_case_runner(&test_case); \
    } \
    void TEST_##groupval##_##nameval##_(void)

/* 运行测试用例 */
#define RUN_TEST_CASE(group, name) \
    TEST_##group##_##name##_RUN();

/* 布尔值断言 */
#define EXPECT_TRUE(condition) \
    unit_test_assert_boolean(condition, true, ASSERTION_TYPE_EXPECT, __FILE__, __LINE__);

#define EXPECT_FALSE(condition) \
    unit_test_assert_boolean(condition, false, ASSERTION_TYPE_EXPECT, __FILE__, __LINE__);

#define ASSERT_TRUE(condition) \
    unit_test_assert_boolean(condition, true, ASSERTION_TYPE_ASSERT, __FILE__, __LINE__);

#define ASSERT_FALSE(condition) \
    unit_test_assert_boolean(condition, false, ASSERTION_TYPE_ASSERT, __FILE__, __LINE__);

/* 整数断言 */
#define EXPECT_EQ(actual, expected) \
    unit_test_assert_integer((actual), (expected), ASSERTION_TYPE_EXPECT, __FILE__, __LINE__);

#define ASSERT_EQ(actual, expected) \
    unit_test_assert_integer((actual), (expected), ASSERTION_TYPE_ASSERT, __FILE__, __LINE__);

/* 打印 */
#define TEST_INFO(...) \
    do { \
        unit_print(FONT_GREEN, "[---INFO---] "); \
        unit_print(FONT_WHITE, __VA_ARGS__); \
        unit_print(FONT_WHITE, "\n"); \
    } while (0);

#endif