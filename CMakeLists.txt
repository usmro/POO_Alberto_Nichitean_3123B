cmake_minimum_required(VERSION 3.10)
project(MotorCautare)
set(CMAKE_CXX_STANDARD 17)

# Executabilul principal (Aplicatia ta)
add_executable(app 
    "src/main.cpp"
    "src/TextDocument.cpp"
    "src/InvertedIndex.cpp"
    "src/Logger.cpp"
)

# Executabilul pentru Teste
add_executable(run_tests 
    "tests/test_index.cpp"
    "src/TextDocument.cpp"
    "src/InvertedIndex.cpp"
    "src/Logger.cpp"
)