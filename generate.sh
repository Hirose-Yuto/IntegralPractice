clang++ -std=c++14 -o generator/generate.out \
  generator/main.cpp \
  generator/fraction.cpp \
  generator/polynomial.cpp \
  generator/generator.cpp
./generator/generate.out
platex TeX/integration.tex
mv integration.aux Tex/integration.aux
mv integration.log Tex/integration.log
dvipdfmx integration.dvi
mv integration.dvi Tex/integration.dvi