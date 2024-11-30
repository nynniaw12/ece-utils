#include "templates.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

class ProjectGenerator {
private:
  std::string project_name;
  std::filesystem::path project_dir;

  bool create_file(const std::filesystem::path &path,
                   const std::string &template_name) {
    try {
      std::string template_content = Templates::readTemplate(template_name);
      std::string processed_content =
          Templates::procTemplate(template_content, project_name);
      std::ofstream file(path);
      if (!file)
        return false;
      file << processed_content;
      return true;
    } catch (const std::exception &e) {
      std::cerr << "Error processing template " << template_name << ": "
                << e.what() << std::endl;
      return false;
    }
  }

public:
  ProjectGenerator(const std::string &name)
      : project_name(name), project_dir(name) {}

  bool generate() {
    std::error_code ec;
    // project directory
    if (!std::filesystem::create_directories(project_dir, ec) && ec) {
      std::cerr << "Error creating directory: " << ec.message() << std::endl;
      return false;
    }

    struct FileTemplate {
      std::string filename;
      const char *template_name;
    };

    FileTemplate files[] = {
        {project_name + ".v", Templates::RTL_TEMPLATE},
        {project_name + "_tb.v", Templates::TESTBENCH_TEMPLATE},
        {project_name + ".sdc", Templates::SDC_TEMPLATE},
        {"Makefile", Templates::MAKEFILE_TEMPLATE}};

    bool success = true;
    for (const auto &file : files) {
      std::filesystem::path file_path = project_dir / file.filename;
      if (!create_file(file_path, file.template_name)) {
        std::cerr << "Error creating " << file_path << std::endl;
        success = false;
      } else {
        std::cout << "Created " << file_path << std::endl;
      }
    }

    if (success) {
      std::cout << "\nProject '" << project_name << "' created successfully!"
                << std::endl;
      std::cout << "Location: " << project_dir << "\n\n";
      std::cout << "To get started:\n";
      std::cout << "  cd " << project_name << std::endl;
      std::cout << "  make run        # Run simulation" << std::endl;
      std::cout << "  make run SYNTH=1  # Run with synthesis" << std::endl;
      std::cout << "  make clean      # Clean generated files" << std::endl;
    }

    return success;
  }
};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <project_name>" << std::endl;
    return 1;
  }

  std::string project_name = argv[1];
  ProjectGenerator generator(project_name);
  return generator.generate() ? 0 : 1;
}
