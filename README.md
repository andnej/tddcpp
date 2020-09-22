 This repository is my play ground for learning C++
 In order for this repository to work, you will need to install `google test` before hand, and all the prerequisite that follows `google test`

 This project is using CMake to build, so you will also need cmake installed, which coincidentally you also need it to build `google test`

 The drill is the same as `google test`
 mkdir build
 cd build
 cmake ..
 make

 You can run the unit test inside the build/test, it is an executable named `UnitTest`
 If you use Visual Studio Code to view this project, using an extension called `CMake Tools` will help the development/building process.

 Soundex is just an example that the book `Modern C++ Programming with Test Driven Development` use, I don't really get the requirement but using the knowledge that I got from previous work experience, I constructed CommandLineInterface using Char based and List based. This was a coding test from one of the companies that I applied in past, that explains why I'm not using vector (simply because its purpose was a skill test)

 I hope by sharing this, more people is using C++ and Test Driven Development