#include "wav.h"
#include "helpers.h"
#include <iostream>
namespace  {
const uint16_t kPcmFormat = 1;
const char kDataHeader[] = "data";
const char kFmtHeader[] = "fmt ";
const char kRiffHeader[] = "RIFF";
const char kWaveHeader[] = "WAVE";
}

namespace audio {
Wav::Wav(const std::string& input_filename) :
  input_filename_(input_filename),
  input_file_(std::shared_ptr<std::FILE>(fopen(input_filename.c_str(), "rb"), std::fclose)) {
  GetWaveInfo();
  WavSanityCheck();
}

void Wav::GetWaveInfo() {
  auto header_size = sizeof(wav_header_);
  if (input_file_ == nullptr)
    throw std::runtime_error(std::string("Unable to open wave file. File : ").append(input_filename_));

  // Read the header
  auto bytes_read = fread(&wav_header_, 1, header_size, input_file_.get());
  if (bytes_read != header_size || !bytes_read)
    throw std::runtime_error(std::string("Unable to read wave file header. File : ").append(input_filename_));

  auto file_length = helpers::GetFileSize(input_file_.get());
  std::cout << "File name                  :" << input_filename_ << std::endl;
  std::cout << "File is                    :" << file_length << " bytes." << std::endl;
  std::cout << "RIFF header                :" << wav_header_.riff_header[0] << wav_header_.riff_header[1] << wav_header_.riff_header[2] << wav_header_.riff_header[3] << std::endl;
  std::cout << "WAVE header                :" << wav_header_.wave_header[0] << wav_header_.wave_header[1] << wav_header_.wave_header[2] << wav_header_.wave_header[3] << std::endl;
  std::cout << "FMT                        :" << wav_header_.fmt[0] << wav_header_.fmt[1] << wav_header_.fmt[2] << wav_header_.fmt[3] << std::endl;
  std::cout << "Data size                  :" << wav_header_.riff_chunk_size << std::endl;

  // Display the sampling Rate from the header
  std::cout << "Sampling Rate              :" << wav_header_.samples_per_second << std::endl;
  std::cout << "Number of bits used        :" << wav_header_.bits_per_sample << std::endl;
  std::cout << "Number of channels         :" << wav_header_.number_of_channels << std::endl;
  std::cout << "Number of bytes per second :" << wav_header_.bytes_per_second << std::endl;
  std::cout << "Data length                :" << wav_header_.sub_chunk_to_size << std::endl;
  std::cout << "Audio Format               :" << wav_header_.audio_format << std::endl;
  std::cout << "Block align                :" << wav_header_.block_align << std::endl;
  std::cout << "Data string                :" << wav_header_.sub_chunk_to_id[0] << wav_header_.sub_chunk_to_id[1] << wav_header_.sub_chunk_to_id[2] << wav_header_.sub_chunk_to_id[3]
                                              << std::endl << std::endl;
}

void Wav::WavSanityCheck() {
  if (std::string(reinterpret_cast<char*>(&wav_header_.riff_header), sizeof(wav_header_.riff_header)) != kRiffHeader)
    throw std::runtime_error(std::string("File contains wrong RIFF header. File : ").append(input_filename_));
  if (std::string(reinterpret_cast<char*>(&wav_header_.wave_header), sizeof(wav_header_.wave_header)) != kWaveHeader)
    throw std::runtime_error(std::string("File contains wrong WAVE header. File : ").append(input_filename_));
  if (std::string(reinterpret_cast<char*>(&wav_header_.fmt), sizeof(wav_header_.fmt)) != kFmtHeader)
    throw std::runtime_error(std::string("WAVE file FMT header is damaged. File : ").append(input_filename_));
  if (wav_header_.audio_format != kPcmFormat)
    throw std::runtime_error(std::string("Audio is not in PCM format. File : ").append(input_filename_));
}

std::shared_ptr<std::FILE> Wav::GetFilePtr() {
  return input_file_;
}

WavHeader Wav::GetWavHeader() {
  return wav_header_;
}

}  // namespace audio
