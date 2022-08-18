1.Computed DC shift value for the first 100 samples given in input file 

  Took average average amplitude of 1st 100 samples and later this value is deducted from each sample given in the file.


2.After computing DC shift,the normalization is done 

for normalizing the amplitude values first the absolute max amplitude value is taken from the signal.
Lets say the maximum value is max.
each amplitude value is multiplied by 5000/max.

Now the DC shift is removed and the normalization process is finished 

3.Now the normalized file is opened.
 for each frame of 100 samples, it's STE is computed and STE value is stored in an array caller energy.

4.Now I've found the start point of the word.
 The energy array is traversed and when the energy jumped around 3 times in two consequtive frames then the frame
 is marked as start frame.

5.Similarly energy array is again traversed from reverse and when the energy reduced by 3times in two consequtive frames 
  then the frame is marked as end frame.

6.At this point of time,start and end of the word is kept in two variables.



7.Now,total length of the word is found by the formula end-start+1

8.Now,avg ZCR value of a frame is computed for the first 30% of the frames.
 for YES in 1st 30% of data there is no noisy sound so this average zcr will tend to have smaller ZCR value.
 lets say this value is called zcr_of_first30

9.After step 8 the last 30% data is taken and again the average ZCR value of a frame is computed.Let's say the value is
  called zcr_of_last30 

10.If the spoken word is yes, then zcr_of_last30 will be significantly higher than zcr_of_first30, 
   because the "Yes" sound contains noisy sounds in the tail part.
   

   if(zcr_of_first30 * 1.3 <= zcr_of_last30) //(for the margin of safety 30 percentage is taken.)

   when the above condition is true it says the last part of the word has significant amount of noise.
   So, it can be concluded that in such case the word spoken is 
   "YES"
   and if the above condition is not satisfied we can say that the word spoken is 
   "NO".

  