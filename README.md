# Codes for research use
## For NGS Data analysis
### 1. General Analysis
Pipeline scripts to run the analysis are available from each link.
1. [VariantCall]()
2. [RNA-seq]()
3. [ChIP-seq]()

#### Publications:
* [Ikari N, Aoyama S, Seshimo A, <b><u>Suehiro Y</u></b>, Motohashi T, Mitani S, Yoshina S, Tanji E, Serizawa A, Yamada T, Taniguchi K, Yamamoto M, Furukawa T. Somatic mutations and increased lymphangiogenesis observed in a rare case of intramucosal gastric carcinoma with lymph node metastasis. Oncotarget. 2018 Jan 22;9(12):10808-10817.](https://pubmed.ncbi.nlm.nih.gov/29535844/)    
* [Zhou Q, Li H, Li H, Nakagawa A, Lin JL, Lee ES, Harry BL, Skeen-Gaar RR, <b><u>Suehiro Y</u></b>, William D, Mitani S, Yuan HS, Kang BH, Xue D. Mitochondrial endonuclease G mediates breakdown of paternal mitochondria upon fertilization. Science. 2016 Jul 22;353(6297):394-9.](https://pubmed.ncbi.nlm.nih.gov/27338704/)  
* [Zhao P, Zhang Z, Lv X, Zhao X, <b><u>Suehiro Y</u></b>, Jiang Y, Wang X, Mitani S, Gong H, Xue D. One-step homozygosity in precise gene editing by an improved CRISPR/Cas9 system. Cell Res. 2016 May;26(5):633-6.](https://pubmed.ncbi.nlm.nih.gov/27055372/)

### 2. Variant detection from whole genome sequence


#### Citation:
* [<b><u>Suehiro Y</u></b>, Yoshina S, Motohashi T, Iwata S, Dejima K, Mitani S. Efficient collection of a large number of mutations by mutagenesis of DNA damage response defective animals. Sci Rep. 2021 Apr 7;11(1):7630.](https://pubmed.ncbi.nlm.nih.gov/33828169/)  

#### Other publications:
* [Dejima K, Hori S, Iwata S, <b><u>Suehiro Y</u></b>, Yoshina S, Motohashi T, Mitani S. An Aneuploidy-Free and Structurally Defined Balancer Chromosome Toolkit for Caenorhabditis elegans. Cell Rep. 2018 Jan 2;22(1):232-241.](https://pubmed.ncbi.nlm.nih.gov/29298424/)  
* [Iwata S, Yoshina S, <b><u>Suehiro Y</u></b>, Hori S, Mitani S. Engineering new balancer chromosomes in C. elegans via CRISPR/Cas9. Sci Rep. 2016 Sep 21;6:33840.](https://pubmed.ncbi.nlm.nih.gov/27650892/)

### 3. Unpubliched ChIP-seq analysis
### Codes
* [chip_analyze.cpp]() (Written in C++)
* [chip_analyze.ipynb]() (Google Colab notebook)

## Required libraries
### For C++ code
>* [libsobj]()
>* [libsapp]()
>* [libsbioinfo]()
>* [libcurl]()
### For Python code
>* numpy
>* pandas
>* matplotlib
>* scikit-learn
>* umap

## How to use
* The C++ codes are required to be compile before running.  

> For Mac users  
> Please install [XCode](https://developer.apple.com/download/) (Command line toolkit) to compile.  
> For Unix/Linux users  
> Please install GCC (g++) or [Clang](https://clang.llvm.org/) to compile.  

> For windows users  
Please install [VisualStudio](https://visualstudio.microsoft.com/downloads/) to cpmpile and run.  
Sorry, but I have not checked if it works well with MinGW.

* The notebooks(.ipynb) are able to be opened and run on Google Colab.  
> If you have a google account, please login and import the ipynb file. Then, please run the programs according to the guidance.  
> You can learn about the google colab on the [official web site](https://colab.research.google.com/notebooks/welcome.ipynb).  

> Otherwise, you can also run the programs uing [Jupyter](https://jupyter.org/).  


