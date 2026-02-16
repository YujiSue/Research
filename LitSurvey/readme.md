# Overview
This repository contains the data and Google Colab/Jupyter Notebook utilized in a review of the activities and achievements of the Japanese _C. elegans_ bioresource center.

# Files and directory
/  
|- NBRPReviewNotebook.ipynb   
|- RefDB_Demo.ipynb  
|- README.md  
|- Data  
&nbsp;&nbsp;&nbsp;&nbsp;|- reference.db  # A bibliographic database for _C. elegans_ research.  
&nbsp;&nbsp;&nbsp;&nbsp;|- distributing.tsv  # Available mutants and other strains in our resource center.  
&nbsp;&nbsp;&nbsp;&nbsp;|- requests.tsv  # Requeted strains by the year.  
&nbsp;&nbsp;&nbsp;&nbsp;|- shipping.tsv  # Destination countries and the number of shipped alleles/strains.  

\* The "requests.tsv" and "shipping.tsv" files were exported from the database used by the resource center to manage order information. The original database has not been made public because it contains customer information and other sensitive data.  

## NBRPReviewNotebook.ipynb 
All the tables, figures, and supplementary data are exported using this notebook.  
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/YujiSue/Research/blob/main/LitSurvey/NBRPReviewNotebook.ipynb)  

## RefDB_Demo.ipynb
This notebook includes sample scripts for storing PubMed search results and text-mining outputs as a SQLite database file. The "reference.db" used in this study was constructed using the scripts, and contains accumulated data intended to cover publications from 1999 through early 2024.   
  
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/YujiSue/Research/blob/main/LitSurvey/RefDB_Demo.ipynb)  
  

# Citation
Under submission
