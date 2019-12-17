#!/bin/bash

make -C "cmake-build-debug/"

for f in tests/* ; do

	if ! cmake-build-debug/Compiler_2_0 -i -d -f "$f";
	then
		echo -e "\e[33mProgram crashed: $f.\e[0m" >> Results; 
	fi
        	
done

echo "Results"
echo "-------"
cat Results
rm Results
