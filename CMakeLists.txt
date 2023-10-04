# установка версии CMake
cmake_minimum_required(VERSION 3.16)

# название проекта (обязательно)
project(oopprog2)

# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 20)

# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# добавление подпроекта с библиотекой
add_subdirectory(wagon)

# добавление подпроекта с тестами
add_subdirectory(testsSimpleClass)

# создание исполняемого файла для диалоговой программы
add_executable(SimpleClass mainSimpleClass.cpp)

# подключение библиотеки circle к диалоговой программе
target_link_libraries(simpleslass wagon)


# для сборки из консоли:
#
# mkdir build   # создание директории для файлов сборки
# cd build      # переход в директорию сборки
# cmake ..      # генерация файлов сборки на основе CMakeLists.txt
# make          # сборка проекта