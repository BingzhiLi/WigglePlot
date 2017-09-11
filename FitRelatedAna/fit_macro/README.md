macro to fit the wiggle plot

1. fitWiggle.C 
   
  using fit function to fit the data

2. obtain_parameter.C

  obtain the fit parameters in diff fit range and diff energy threshold, and store them in a tree
  each leaf is in array structure, leaf[i] correspond the i_th energy threshold

  leaf[0]-1.86GeV
  leaf[1]-1.6 GeV
  leaf[2]-1.7 GeV
  leaf[3]-1.8 GeV
  leaf[4]-1.9 GeV
  leaf[5]-2.0 GeV
  leaf[6]-2.1 GeV
  leaf[7]-2.2 GeV

3. diff_start_point.C

  obtain the fit parameter in diff fit range with diff fit start point and same threshold 
  
  the fit range : 10-40 ... 10-200 ns
                  20-40 ... 20-200 ns
                  25-40 ... 25-200 ns

4. FitRelatedAna.C
  
  read the tree in the root file which produced by the 2.obtain_parameter.C macro 
  draw the parameters vs fit range

5. energy_slice_parameter.C

  like 2.obtain_parameter.C , obtain the fit parameters in diff energy slice with same threshold, and 
  store them in a tree, each leaf is in array structure, leaf[[i] correspond the i_th energy slice

  leaf[0]-1.6-1.9 GeV
  leaf[1]-1.9-2.2 GeV
  leaf[2]-2.2-3.1 GeV

6. energy_slice_Fit.C

  read the tree in the rooot file which produced by the 5.energy_slice_parameter.C macro
  draw the parameters vs fit range
