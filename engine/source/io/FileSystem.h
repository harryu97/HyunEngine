#pragma once
#include <filesystem>
#include <vector>
namespace eng {
class FileSystem {
 public:
  static std::filesystem::path GetExecutableFolder();
  static std::filesystem::path GetAssetsFolder();

  static std::vector<char> LoadFile(const std::filesystem::path& path);
  static std::vector<char> LoadAssetFile(const std::string& relativePath);
  static std::string LoadAssetFileText(const std::string& relativePath);
};

};  // namespace eng
