#===============================================================================
#
# Для успешной компиляции требуется наличие заголовочных файлов Google Test
# в стандартной директории заголовочных файлов компилятора. Ну то есть там,
# где компилятор обычно ищет заголовочные файлы.
#   Пример для MinGW (Windows):
# Берем папку include/gtest из скачанных исходников и копируем ее в папку
# MINGW_ROOT_DIRECTORY/include, получается что-то вроде:
#   c:\Program Files\MinGW\include\gtest
# Также необходимо собрать библиотеки и положить их в MINGW_ROOT_DIRECTORY/lib.
# Что я сделал чтобы собрать библиотеки:
# 1. Скачал исходники (gtest-1.6.0.zip, версия может отличаться), распаковал их.
# 2. Зашел в папку /make и запустил mingw32-make. В результате получились файлы
#    gtest_main.a, gtest_main.o, gtest-all.o и прочие.
# 3. Эти три файла я скопировал в c:\Program Files\MinGW\lib и файл
#    gtest_main.a переименовал в libgtest_main.a, чтобы иметь возможность
#    сообщить компилятору о необходимости использования данной библиотеки
#    посредством директивы -lgtest_main.
# 4. PROFIT!
# 5. После этого я попробовал удалить файлы gtest_main.o, gtest-all.o из папки
#    MINGW_ROOT_DIRECTORY/lib и запустить сборку заново. Сборка прошла успешно,
#    из чего можно заключить, что для данного теста необходима только библиотека
#    gtest_main.a.
# 
#===============================================================================

ifeq ($(OS), Windows_NT)
	MAKE_TOOL = mingw32-make
	RMDIR = rmdir /S /Q
	MAKE_OBJ_DIR = if not exist obj mkdir obj
	RM_EXECS = del /Q unittest.exe main.exe
else
	MAKE_TOOL = mingw32-make
	RMDIR = rm -r
	MAKE_OBJ_DIR = mkdir -p obj
	RM_EXECS = rm unittest main
endif

# Flags passed to the C++ compiler.
CXXFLAGS = -g -Wall -Wextra

all :
	$(MAKE_OBJ_DIR)
	$(MAKE_TOOL) main
	$(MAKE_TOOL) unittest

obj/boltnut.o : src/boltnut.cpp src/include/boltnut.hpp
	$(CXX) $(CXXFLAGS) -c src/boltnut.cpp -o obj/boltnut.o

obj/unittest.o : src/unittest.cpp src/include/boltnut.hpp
	$(CXX) $(CXXFLAGS) -c src/unittest.cpp -o obj/unittest.o

unittest : obj/boltnut.o obj/unittest.o
	$(CXX) $(CXXFLAGS) -lpthread -lgtest_main $^ -o $@

obj/main.o : src/boltnut.cpp src/include/boltnut.hpp src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

main : obj/boltnut.o obj/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RMDIR) obj
	$(RM_EXECS)
