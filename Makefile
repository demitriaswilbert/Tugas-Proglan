CXX ?=g++ 
CXXFLAGS += --std=c++17 -O3 -Wall -Wextra -I.
SOURCES = src/main.cpp src/person.cpp src/mahasiswa.cpp src/dosen.cpp src/kelas.cpp src/matkul.cpp src/form.cpp

src/%.o: src/%.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

sim: $(SOURCES:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f src/*.o sim.exe
