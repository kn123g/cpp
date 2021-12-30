# 1) generates native header file and class file
javac -h ./bin/com/jniHeaders -d ./bin/com ./src/com/HashMapPrint.java

# 2) generates object file for native cpp 
g++ -c -I"%JAVA_HOME%/include"  -I"%JAVA_HOME%/include/win32" -I"./bin/com/jniHeaders" ./cpp/HashMapPrint.cpp -o ./cpp/HashMapPrint.o

# 3) generates dll file for native cpp
g++ -shared -o ./bin/com/HashMapPrint.dll ./cpp/HashMapPrint.o -Wl,--add-stdcall-alias

# 4) run java class(TemperatureSampler)  -cp(class path) _Djava.library.path(dll path)
java -cp ./bin/com -Djava.library.path=./bin/com com.HashMapPrint