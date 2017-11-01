all:
	rm -rf build
	mkdir build
	touch ./build/__init__.py
	swig -lpointer.i -cpperraswarn -python -c++ -outdir build -o build/trajectory_template_py_wrap.cxx trajectory_template_py.i 
	python setup.py build_ext --build-lib=build