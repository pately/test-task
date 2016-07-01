#include "convert_to_mp3.h"
#include "helpers.h"
#include <vector>

namespace  {
  const int kWavSize = 8192;
  const int kMp3Size = 8192;
  const char kMp3Extension[] = ".mp3";
  size_t kMp3ExtensionSize = 4;
  size_t kQualityLevelGood = 5;   // 2 : near-best quality, not too slow. 5 : good quality, fast.  7 : ok quality, really fast
}

namespace convert_audio {
  ConvertToMp3::ConvertToMp3(std::string &input_filename) :
    input_filename_(input_filename),
    lame_(lame_init(), [](lame_global_flags * lame_global_flags){ lame_close(lame_global_flags); }) {
  wav_ = std::make_shared<audio::Wav>(input_filename_);
  input_file_ = wav_->GetFilePtr();
  SetLameConfig();
}

void ConvertToMp3::SetLameConfig() {
  if (lame_set_num_channels(lame_.get(), wav_->GetWavHeader().number_of_channels))
    throw std::runtime_error(std::string("Failed to set number of channels. File : ").append(input_filename_));
  if (lame_set_mode(lame_.get(), MPEG_mode_e(wav_->GetWavHeader().number_of_channels)))
    throw std::runtime_error(std::string("Failed to set lame mode. File : ").append(input_filename_));
  if (lame_set_in_samplerate(lame_.get(), wav_->GetWavHeader().samples_per_second))
    throw std::runtime_error(std::string("Failed to set lame sample rate. File : ").append(input_filename_));
  if (lame_set_quality(lame_.get(), kQualityLevelGood))
    throw std::runtime_error(std::string("Failed to set lame quality. File : ").append(input_filename_));
  if (wav_->GetWavHeader().number_of_channels != 1 && wav_->GetWavHeader().number_of_channels != 2)
    throw std::runtime_error(std::string("Unsupported number of channels. File : ").append(input_filename_));
  if (wav_->GetWavHeader().bits_per_sample != 8 && wav_->GetWavHeader().bits_per_sample != 16)
    throw std::runtime_error(std::string("Unsupported bits per sample. File : ").append(input_filename_));
  if (lame_init_params(lame_.get()))
    throw std::runtime_error(std::string("Failed to initialize lame parameters. File : ").append(input_filename_));
}

void ConvertToMp3::Convert() {
  const auto& output_filename = (input_filename_.replace((input_filename_.size() - kMp3ExtensionSize), kMp3ExtensionSize, kMp3Extension));
  output_file_ = (std::shared_ptr<std::FILE>(fopen(output_filename.c_str(), "wb"), std::fclose));
  std::vector<int16_t> pcm_buffer(kWavSize * 2);
  std::vector<unsigned char> mp3_buffer(kMp3Size);
  int read{}, write{};
  do  {
      read = fread(pcm_buffer.data(), 2 * sizeof(int16_t), kWavSize, input_file_.get());
      if (!read)
        write = lame_encode_flush(lame_.get(), mp3_buffer.data(), kMp3Size);
      else {
          std::unique_ptr<int16_t[]> resample;
          int16_t* src = nullptr;
          switch (wav_->GetWavHeader().bits_per_sample) {
            case 8:
              resample.reset(new int16_t[read * wav_->GetWavHeader().number_of_channels]);
              src = resample.get();
              for (int i = 0; i < read * wav_->GetWavHeader().number_of_channels; ++i)
                src[i] = static_cast<int16_t>(pcm_buffer[i] - 0x80) << 8;
              break;
            case 16:
              src = const_cast<int16_t*>(reinterpret_cast<const int16_t*>(pcm_buffer.data()));
              break;
            default: throw std::runtime_error(std::string("Invalid bits per sample. File : ").append(input_filename_));
            }
          switch (wav_->GetWavHeader().number_of_channels) {
            case 1:  write = lame_encode_buffer(lame_.get(), src, nullptr, read, mp3_buffer.data(), kMp3Size); break;
            case 2:  write = lame_encode_buffer_interleaved(lame_.get(), src, read, mp3_buffer.data(), kMp3Size); break;
            default: throw std::runtime_error(std::string("Invalid number of channels. File : ").append(input_filename_));
            }
        }
      fwrite(mp3_buffer.data(), write, 1, output_file_.get());
    } while (read > 0);
}
}  // namespace convert_audio
