#pragma once
#include <string>

namespace Templates {
const char *const TEMPLATE_DIR = "templates";

// keep name extensions correct for syntax highlighting
const char *const RTL_TEMPLATE = "rtl.v";
const char *const TESTBENCH_TEMPLATE = "tb.v";
const char *const SDC_TEMPLATE = "sdc.sdc";
const char *const MAKEFILE_TEMPLATE = "Makefile";

std::string readTemplate(const std::string &template_name);
std::string procTemplate(const std::string &template_content,
                         const std::string &project_name);
} // namespace Templates
