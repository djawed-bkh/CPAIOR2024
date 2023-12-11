# You can execute the following approaches by launching the commands below from the CPAIOR2024 directory.



## GC4CIP Execution:
```bash
export  LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH; /bin/time -f "%E real , %U user , %S sys"  timeout 43200 ./MyClosedConstraint --gc4cip-cpsolver DATA/<path of a dataset file finishing with _T.dat> <Absolute minimum support>
```

## CP4CIP execution: 

```bash
export  LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH; /bin/time -f "%E real , %U user , %S sys"  timeout 43200 ./MyClosedConstraint --cp4cip-cpsolver DATA/<path of a dataset file finishing with _T.dat> <Absolute minimum support> 43200
```


## CP4IM execution (carried internally):
```bash
export  LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH; /bin/time -f "%E real , %U user , %S sys"  timeout 43200 ./MyClosedConstraint --cp4im-cpsolver DATA/<path of a dataset file finishing with _T.dat> <absolute value for frequency> 43200
```

## closedPattern execution:
```bash
export  LD_LIBRARY_PATH=./ClosedPattern:$LD_LIBRARY_PATH; /bin/time -f "%E real , %U user , %S sys"  timeout 43200 ./ClosedPattern/pattern_closed-noavx --dataset ./DATA/<path of a dataset file finishing with _IS.dat> --fmin <Absolute minimum support> [Optionnal --show]
```




## MinIntChange execution: 
```bash
/bin/time -f "%E real , %U user , %S sys"  timeout 43200 java -jar './MinIntChange.jar' 'DATA/<Choose a dataset file finishing with _T.dat>' <Absolute minimum support> ; echo "Exit status: $?"
```


## Pre-processing (Binarization) execution: 
```bash
/bin/time -f "%E real , %U user , %S sys"  timeout 43200 ./Interordinal_Scaling_Binarization/ISBinarization ./DATA/<path of a dataset file finishing with _T.dat> [Optional --show]
```
## Post-processing (Itemset to Interval Pattern) execution: 

**You can test it by running the closedPattern command with --show &>output.txt  Then use the output file as input in <path of a file containing itemsets obtained from closedPattern or CP4IM>**

```bash
./Itemsets_to_Interval_Patterns/Reverse_Binarisation --numericaldataset DATA/<path of a dataset file finishing with _T.dat> --itemsetsResult <path of a file containing itemsets obtained from closedPattern or CP4IM>
```

## 3-clustering with GC4CIP execution: 
```bash
export  LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH; /bin/time -f "%E real , %U user , %S sys"  timeout 43200 ./Clustering_with_GC4CIP/3Clustering/Clustering_GC4CIP --gc4cip-cpsolver DATA/<path of a dataset file finishing with _T.dat> <Absolute frequency>
```

## 4-clustering with GC4CIP execution: 
```bash
export  LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH; /bin/time -f "%E real , %U user , %S sys"  timeout 43200 ./Clustering_with_GC4CIP/4Clustering/Clustering_GC4CIP --gc4cip-cpsolver DATA/<path of a dataset file finishing with _T.dat> <Absolute frequency>
```

## 5-clustering with GC4CIP execution: 
```bash
export  LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH; /bin/time -f "%E real , %U user , %S sys"  timeout 43200 ./Clustering_with_GC4CIP/5Clustering/Clustering_GC4CIP --gc4cip-cpsolver DATA/<Choose a dataset file finishing with _T.dat> <Absolute frequency>
```
