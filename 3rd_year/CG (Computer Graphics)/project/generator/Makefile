LIBS = -lglut -lGLU -lGL

link: model.o point3d.o triangle.o sphere.o cone.o box.o plane.o torus.o bezier.o generator.o 
	g++ build/generator.o build/sphere.o build/cone.o build/box.o build/plane.o build/bezier.o build/torus.o build/model.o build/triangle.o build/point3d.o $(LIBS) -o generator

model.o:
	g++ -o build/model.o -c -Wall -g src/Model.cpp

point3d.o:
	g++ -o build/point3d.o -c -Wall -g ../utils/Point3D.cpp

triangle.o:
	g++ -o build/triangle.o -c -Wall -g src/Triangle.cpp

sphere.o:
	g++ -o build/sphere.o -c -Wall -g src/Sphere.cpp

cone.o:
	g++ -o build/cone.o -c -Wall -g src/Cone.cpp

box.o:
	g++ -o build/box.o -c -Wall -g src/Box.cpp

plane.o:
	g++ -o build/plane.o -c -Wall -g src/Plane.cpp

torus.o: 
	g++ -o build/torus.o -c -Wall -g src/Torus.cpp

bezier.o:
	g++ -o build/bezier.o -c -Wall -g src/Bezier.cpp

generator.o:
	g++ -o build/generator.o -c -Wall -g src/main.cpp $(LIBS)

clean:
	rm build/*.o generator *.3d 
