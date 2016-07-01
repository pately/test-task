#include "convert_to_mp3.h"
#include <dirent.h>
#include <cstring>
#include <iostream>
#include <vector>

namespace {
  const char kWavExtension[] = ".wav";
  std::vector<std::string> GetDirectoryFiles(const std::string& dir) {
    std::vector<std::string> files;
    std::shared_ptr<DIR> directory_ptr(opendir(dir.c_str()), [](DIR* dir){ dir && closedir(dir); });
    struct dirent *dirent_ptr;
    if (!directory_ptr) {
        std::cout << "Error opening : " << std::strerror(errno) << dir << std::endl;
        return files;
      }

    while ((dirent_ptr = readdir(directory_ptr.get())) != nullptr) {
        auto found = std::string(dirent_ptr->d_name).find(kWavExtension);
        if (found != std::string::npos) {
            files.push_back(std::string(dirent_ptr->d_name));
          }
      }
    return files;
  }
}  // namespace

int main(int argc, char** argv) {
  try {
    if (argc != 2) {
        std::cout << "Error: correct usage -> ./lame_task [directory path] " << std::endl;
        return 0;
      }
    const auto& directory_path = std::string(argv[1]);
    const auto& files = GetDirectoryFiles(directory_path);

    if (files.empty()) std::cout << "Error: No wav file found in directory" << std::endl;
    std::vector<std::thread> threads;

    for (const auto& file : files) {
        std::string found_wav = file;
        auto convert = std::make_shared<convert_audio::ConvertToMp3>(found_wav);
        auto  thread= std::thread(&convert_audio::ConvertToMp3::Convert, convert);
        threads.emplace_back(std::move(thread));
      }

    for (std::thread & t : threads) {
        t.join();
      }

    // OK to destroy now
    threads.clear();
  } catch (const std::exception& ex) {
    std::cerr << "Error : " << ex.what() << std::endl;
  }
  return 0;
}
