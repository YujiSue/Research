# Codes used in the research (unpublished)
## Overview
![Workflow](https://github.com/YujiSue/Research/raw/main/CustomChIP/workflow.png)
  
## Codes
### * [chip_analyze.ipynb](https://github.com/YujiSue/Research/blob/main/CustomChIP/chip_analyze.ipynb)
### * [chip_analyze.cpp](https://github.com/YujiSue/Research/blob/main/CustomChIP/chip_analyze.cpp)
  
## How to use
### chip_analyze.ipynb :  
1. Create google account if you do not have.  
2. Please download and copy to your Google Drive and access from [Google Colab.](https://colab.research.google.com/notebooks/welcome.ipynb)  
3. Run the cells.  
  
### chip_analyze.cpp :  
1. Install libsobj and libsbioinfo according to the guidance of [slib]() repositories.
2. Download and compile the file (.cpp).
Compile command example:  
For linux (* require gcc)  
```
$ g++ -std=c++11 -I -L -O2 -o chip_analyze {donwload directory}/chip_analyze.cpp -lsobj -lsbioinfo -lcurl
```  
  
For mac (* require clang bundled with Xcode)  
```
$ g++ -std=c++11 -I -L -O2 -o chip_analyze {donwload directory}/chip_analyze.cpp -lsobj -lsbioinfo -lcurl
```
  
For windows (* require build toolkits and terminal for developpers bundled with VisualStudio)  
```

``` 

## Publication
Not yet.
