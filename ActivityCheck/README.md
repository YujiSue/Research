# ImageJ plugin to judge animal activity

## Introduction
### What's problem
- It is difficult to confirm the death of animlas withou hearts such as invertebrates and microorganisms.  
> For example, in some cases, even if they appear to be dead, they can suddenly revive when subjected to mechanical stimuli.  

- In the case of nematodes, if there is no activity after repeated observation over a period of time, it is considered dead.  
> But... it is difficult to check with human eyes

### How to resolve
- Get low-resolution time-lapse images for each animal.  
 Binarizes the difference between images during a certain time period (~1 sec).  
 Make an overlay of the generated images during a certain period of time (~10 sec).
  
![](./img/img_diff.png)

  
- Check the activity based on the area of pixels, whose values are 0 or 255.
  
![](./img/activity_check.png)

## Usage




## Citation
Not yet published.
