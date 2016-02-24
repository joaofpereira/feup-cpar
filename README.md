# feup-cpar
A repository to Parallel Computation

Setup PAPI
- Download tar.gz from http://icl.cs.utk.edu/papi/software/
- Extract the folder where you want, so choose a practical place for that
- Go to source (src) directory in PAPI folder : cd yourPath/PAPI/src
- Run the following commands:
  - ./configure
  - make
  - sudo make install
  - make test
  - sudo ldconfig

- Install PAPI tools:
  - sudo apt-get install papi-tools

- Compile matrixProd.cpp
  - g++ "yourFile.cpp" -lpapi
  - run ./a.out and introduce the matrix size values
