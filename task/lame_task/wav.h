#ifndef LAME_TASK_WAV_H_
#define LAME_TASK_WAV_H_
#include <cstdio>
#include <memory>

namespace audio {
struct WavHeader {
  /* RIFF Chunk Descriptor */
  uint8_t         riff_header[4];            // RIFF Header Magic header
  uint32_t        riff_chunk_size;           // RIFF Chunk Size
  uint8_t         wave_header[4];            // WAVE Header
  /* "fmt" sub-chunk */
  uint8_t         fmt[4];                    // FMT header
  uint32_t        sub_shunk_size;            // Size of the fmt chunk
  uint16_t        audio_format;              // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
  uint16_t        number_of_channels;        // Number of channels 1=Mono 2=Sterio
  uint32_t        samples_per_second;        // Sampling Frequency in Hz
  uint32_t        bytes_per_second;          // bytes per second
  uint16_t        block_align;               // 2=16-bit mono, 4=16-bit stereo
  uint16_t        bits_per_sample;           // Number of bits per sample
  /* "data" sub-chunk */
  uint8_t         sub_chunk_to_id[4];        // "data"  string
  uint32_t        sub_chunk_to_size;         // Sampled data length
};

class Wav {
 public:
  explicit Wav(const std::string& input_filename);
  void GetWaveInfo();
  void WavSanityCheck();
  std::shared_ptr<std::FILE> GetFilePtr();
  WavHeader GetWavHeader();

 private:
  std::string input_filename_{};
  std::shared_ptr<std::FILE> input_file_;
  WavHeader wav_header_;
  uint32_t samples_per_second_;
};
}  // namespace audio

#endif  // LAME_TASK_WAV_H_
