
for f in tests/* ; do 
	cmake-build-debug/Compiler_2_0 $f 1; 
done

echo "Results"
echo "-------"
cat Results
rm Results
