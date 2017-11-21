all:
	rm -rf build
	mkdir build
	touch ./build/__init__.py
	# swig -lpointer.i -cpperraswarn -python -c++ -outdir build -o build/combined.cxx combined.i 
	swig -lpointer.i -cpperraswarn -python -c++ -outdir build -o build/hip_py_wrapper.cxx hip.i 
	swig -lpointer.i -cpperraswarn -python -c++ -outdir build -o build/knee_py_wrapper.cxx knee.i 
	python setup_hip.py build_ext --build-lib=build
	python setup_knee.py build_ext --build-lib=build