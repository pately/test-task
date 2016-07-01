# lame_task

Write a C/C++ command line application that encodes a set of WAV files to MP3
Requirements:
1. application is called with pathname as argument, e.g.
<applicationname> F:\MyWavCollection all WAV-files contained directly in that folder are to be encoded to MP3
2. use all available CPU cores for the encoding process in an efficient way by utilizing multi-threading
3. statically link to lame encoder library
4. application should be compilable and runnable on Windows and Linux
5. the resulting MP3 files are to be placed within the same directory as the source WAV files, the filename extension should be changed appropriately to .MP3
6. non-WAV files in the given folder shall be ignored
7. multithreading shall be implemented by means of using Posix Threads (there exist implementations for Windows)
8. the Boost library shall not be used
9. the LAME encoder should be used with reasonable standard settings (e.g. quality based encoding with quality level "good")

## Linux build
libmp3lame.a static library on linux using gcc 4.8.4. The prebuild libmp3lame.a is already kept inside include directory.
steps for making static library are fairly straight forward i.e.
$ cd lame-3.99.x
$ ./configure --prefix=/desired/path/
$ make
$ make install

For Building the project on linux any distribution above gcc 4.8.x can be used.
lame_task project can be build using cmake. To bulid the project on linux follow the steps
$ cd project_dir
§ cmake . && make

## Window build
libmp3lame.lib static library was bulid using visual studio. just open the solution inside lame/vc_solution using visual studio and build it.

For Building the project on windows using cmake qt creater or visual studio can be used.
building lame_task on windows also fairly straight forward. (I used the following method)
* open lame_task camke project using qt creator.
* build the project and run.

# important notes
* I have used C++11 threads insted of pthread as it more convenient.
* Complete support for converting Wav to Mp3 will take quite an effort.
* So support for only 8 and 16 bit is implemented.
* The quality level is set at 5 i.e. good
* if more time is invested on the task, it can be made much more performent.




