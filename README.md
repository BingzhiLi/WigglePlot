# WigglePlot
using daq reconstruction data to draw the wiggle plot

the data are stored in /pnfs/GM2/daq/

to draw the plot one can use the command "gm2 -c runCaloWiggleAna.fcl -s input_reconstruction_data -T output_root"
the runCaloWiggleAna.fcl will use the CaloNearlineHistograms_module.cc in your_develop_area/srcs/gm2calo/analyses/
then one can use the macro fitWiggle.C to draw the wiggle plot
