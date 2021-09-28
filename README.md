# Codes for research use

The codes in this repository were mainly used for research with collaborators.

## 1. For ChIP-seq analysis
### i) Main codes
* [analyze.cpp]() (Written in C++)
* [analyze.ipynb]() (Created by Google Colab)

### ii) Required libraries
#### For Python code
>* numpy
>* pandas
>* matplotlib
>* scikit-learn
>* umap

### iii) How to use
* The C++ code analyze.cpp is required to be compile before running.  

> For Mac users  
> Please install [XCode](https://developer.apple.com/download/) (Command line toolkit) to compile.  
> For Unix/Linux users  
> Please install GCC (g++) or [Clang](https://clang.llvm.org/) to compile.  

> For windows users  
Please install [VisualStudio](https://visualstudio.microsoft.com/downloads/) to cpmpile and run.  
Sorry, but I have not checked if it works well with MinGW.

* The notebook [analyze.ipynb]() is able to be opened and run on Google Colab.  
> If you have a google account, please login and import the ipynb file. Then, please run the programs according to the guidance.  
> You can learn how to use the google colab on the [official web site](https://colab.research.google.com/notebooks/welcome.ipynb).  

> Otherwise, you can also use the programs as [Jupyter](https://jupyter.org/) file.  
> Please install the required libraries listed above and run as a Jupyter file.


