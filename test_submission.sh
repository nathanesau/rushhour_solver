# test the submission
mkdir -p tmp
cp project.zip tmp
cd tmp
unzip project.zip
rm project.zip
cd src
javac TestSolver.java
java TestSolver
cd ../../
rm -rf tmp