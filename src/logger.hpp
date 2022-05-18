#include <cstdarg>
#include <fstream>
#include <iostream>
using namespace std;

namespace bloxel {
  namespace logger {
    class Log {
      private:
        inline static std::string logFile = "log.log";
      public:
        static void log_message(string message) {
          ofstream st;
          st.open(Log::logFile, ios::out);
          if(st.is_open()) {
            st << message;
            st.close();
            if(st.is_open())
              std::cout << "Stream could not be closed" << std::endl;
          }
        }

        // Not using vectors here to preserve a fixed h/w
        static std::string construct_log_from_height_map(int *height, size_t rows, size_t cols) {
          std::string output = "";
          for(int i = 0; i < rows; i++){
            std::string sentence = "";
            for(int j = 0; j < cols; j++) {
              int curr_h = *((height+ i * cols) + j);
              sentence+=std::to_string(curr_h)+=" ";
            }
            sentence+="\n";
            output+=sentence;
          }
          return output;
        }
    };
  };
};
