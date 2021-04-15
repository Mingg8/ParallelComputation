## Install Openmp
```
brew install libomp
```

## Execution (OSX)
```
clang++ -Xpreprocessor -fopenmp -lomp ${src_file}
```
