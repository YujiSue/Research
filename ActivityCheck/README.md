# ImageJ plugin for assessing animal activity
## Introduction
  is a source code of ImageJ Plugin to check activity of animals.

### What's problem
- When assessing stress, measuring longevity, etc..., it is difficult to confirm the death of animlas without hearts such as invertebrates and microorganisms.  
> For example, in some cases, even if they appear to be dead, they can suddenly revive when subjected to stimuli.  

- In the case of nematodes, if there is no activity after repeated observation over a period of time, it is considered dead.  
> But it is difficult to check with human eyes

### What this code does

- From time-lapse images, the difference of adjacent images are calculated in each ROIs.  
- A binary overlay image of the difference during a certain period of time (~10 sec) is generated.  
  
![](./img/img_diff.png)
  
- The area of the pixels, whose values are 1 (255), in the overlay image are measured.  
Setting the threshold will output whether animals in a particular ROI are active or not.   
  
![](./img/activity_check.png)

## Usage




## Citation
Not yet published.
