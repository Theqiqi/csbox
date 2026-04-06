#include <gtest/gtest.h>
#include "common/ArgumentParser.h"
#include "common/Config.h"
using namespace csbox::common;

TEST(ArgumentParserTest, HandlesNoAntiScreenshotFlag) {
    char* argv[] = {(char*)"csbox.exe", (char*)"--no-anti-screenshot"};
    auto config = ArgumentParser::parse(2, argv);

    EXPECT_FALSE(config.enableAntiScreenshot); // 预期：关闭
    EXPECT_FALSE(config.showHelp);            // 预期：不显示帮助
}

TEST(ArgumentParserTest, HandlesUnknownArgument) {
    char* argv[] = {(char*)"csbox.exe", (char*)"--invalid-param"};
    auto config = ArgumentParser::parse(2, argv);

    EXPECT_TRUE(config.showHelp);             // 预期：因为参数错误，自动跳转帮助
}