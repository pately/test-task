# lame_task

Write a C/C++ command line application that encodes a set of WAV files to MP3
Requirements:
* application is called with pathname as argument, e.g.
<applicationname> F:\MyWavCollection all WAV-files contained directly in that folder are to be encoded to MP3
* use all available CPU cores for the encoding process in an efficient way by utilizing multi-threading
* statically link to lame encoder library
* application should be compilable and runnable on Windows and Linux
* the resulting MP3 files are to be placed within the same directory as the source WAV files, the filename extension should be changed appropriately to .MP3
* non-WAV files in the given folder shall be ignored
* multithreading shall be implemented by means of using Posix Threads (there exist implementations for Windows)
* the Boost library shall not be used
* the LAME encoder should be used with reasonable standard settings (e.g. quality based encoding with quality level "good")

## Linux build
libmp3lame.a static library on Linux using gcc 4.8.4. The prebuild libmp3lame.a is already kept inside include directory.
Steps for making static library are fairly straight forward i.e.
* cd lame-3.99.x
* ./configure --prefix=/desired/path/
* make
* make install

For Building the project on Linux any distribution above gcc 4.8.x can be used.
lame_task project can be build using cmake. To build the project on Linux follow the steps
* cd project_dir
* cmake . && make

## Window build
libmp3lame.lib static library was build using visual studio. just open the solution inside lame/vc_solution using visual studio and build it.

For Building the project on windows using cmake qt creator or visual studio can be used.
Building lame_task on windows also fairly straight forward. (I used the following method)
* Open lame_task camke project using qt creator.
* build the project and run.

# Important notes
* I have used C++11 threads instead of pthread as it more convenient.
* Complete support for converting Wav to Mp3 will take quite an effort.
* So support for only 8 and 16 bit is implemented.
* The quality level is set at 5 i.e. good
* If more time is invested on the task, it can be made much more batter.




