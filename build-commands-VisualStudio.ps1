cmake -S . -B .\vs-solution
cmake --build .\vs-solution
cp .\src\shaders\Vertex.txt .\build\Vertex.txt
cp .\src\shaders\Fragment.txt .\build\Fragment.txt
cp .\vs-solution\Debug\OpenGL.exe .\build\OpenGL.exe