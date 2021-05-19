all: arrayMult arrayMultReduce
	
arrayMult: arrayMult.cpp arrayMult.cl
	g++ -o arrayMult arrayMult.cpp /usr/local/apps/cuda/10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp

arrayMultReduce: arrayMultReduce.cpp arrayMultReduce.cl
	g++ -o arrayMultReduce arrayMultReduce.cpp /usr/local/apps/cuda/10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp

clean:
	rm arrayMult arrayMultReduce