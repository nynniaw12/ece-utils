#include "templates.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

namespace Templates {

std::string getExeDir() {
  std::filesystem::path exe_path = std::filesystem::current_path();
#if defined(_WIN32)
  exe_path = std::filesystem::path(__argv[0]).remove_filename();
#elif defined(__linux__)
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  exe_path = std::filesystem::path(std::string(result, (count > 0) ? count : 0))
                 .parent_path();
#elif defined(__APPLE__)
  char buffer[1024];
  uint32_t size = sizeof(buffer);
  if (_NSGetExecutablePath(buffer, &size) == 0) {
    exe_path = std::filesystem::path(buffer).parent_path();
  } else {
    throw std::runtime_error("Error determining executable path.");
  }
#endif
  return exe_path.string();
}

std::string readTemplate(const std::string &template_name) {
  // dynamiclally locate
  std::filesystem::path template_path =
      std::filesystem::path(getExeDir()) / "templates" / template_name;

  std::ifstream file(template_path);
  if (!file) {
    throw std::runtime_error("Cannot open template: " + template_path.string());
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

std::string procTemplate(const std::string &template_content,
                         const std::string &project_name) {
  std::string result = template_content;

  // Replace ${PROJECT_NAME} with actual project name
  const std::string placeholder = "${PROJECT_NAME}";
  size_t pos = 0;
  while ((pos = result.find(placeholder, pos)) != std::string::npos) {
    result.replace(pos, placeholder.length(), project_name);
    pos += project_name.length();
  }

  return result;
}
} // namespace Templates

