#ifndef LAME_TASK_CONVERT_TO_MP3_H_
#define LAME_TASK_CONVERT_TO_MP3_H_
#include "wav.h"
#include <stdio.h>
#include <thread>
#include <lame/lame.h>
namespace convert_audio {
class ConvertToMp3 {
public:
  ConvertToMp3(std::string &input_filename);
  void SetLameConfig();
  void Convert();
private:
  std::string input_filename_;
  std::shared_ptr<std::FILE> input_file_;
  std::shared_ptr<lame_global_flags> lame_;
  std::shared_ptr<std::FILE> output_file_;
  std::shared_ptr<audio::Wav> wav_;
};
}  // convert_audio

#endif // LAME_TASK_CONVERT_TO_MP3_H_
