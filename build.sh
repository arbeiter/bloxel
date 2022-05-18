if [[ ! -d bin ]]; then
  exit
fi
cd bin
rm -rf *
cmake -DCMAKE_BUILD_TYPE=Debug  ..; make
./OpenGLTestApp
