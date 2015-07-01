## Handle Density-Data
# Read the data from csv-file produced by the C++-Program
data_density <- read.csv2(file = "RandomDensity.csv", dec = ".", strip.white = T, colClasses = c('character', 'factor', 'factor','factor','numeric','numeric') );

# use dplyr-Package for easier handling
library(dplyr)

# use reshape2-Package for colsplit-function
library(reshape2)


# reduce problem name to problem parameter
data_density$Problem <- gsub("^KH_density","",data_density$Problem)  # remove KH_density from problem name
data_density$Problem <- gsub(".dat$","",data_density$Problem)        # remove .dat from problem name
data_density <- cbind(colsplit(data_density$Problem,"-",c("Density", "Instance")), data_density)
data_density <- select(data_density, -Problem, -Algorithm, -Neighborhood, -AlphaValue)


# group data by density
gr_data_density <- group_by(data_density, Density)

# order data by density
gr_data_density <- arrange(gr_data_density, Density)

# summarize data by calculating mean and median values for each module size
# also transform time from values in msec to values in seconds
smry_density <- summarise(gr_data_density, 
                          mean_Time = mean(Time) / 1000, 
                          mean_Iterations = mean(Iterations),
                          median_Time = median(Time) / 1000,
                          median_Iterations = median(Iterations)
)

## Handle PathNum-Data
# Read the data from csv-file produced by the C++-Program
data_pathNum <- read.csv2(file = "RandomPathNum.csv", dec = ".", strip.white = T, colClasses = c('character', 'factor', 'factor','factor','numeric','numeric') );

# use dplyr-Package for easier handling
library(dplyr)

# use reshape2-Package for colsplit-function
library(reshape2)


# reduce problem name to problem parameter
data_pathNum$Problem <- gsub("^KH_path","",data_pathNum$Problem)  # remove KH_path from problem name
data_pathNum$Problem <- gsub(".dat$","",data_pathNum$Problem)  # remove .dat from problem name
data_pathNum <- cbind(colsplit(data_pathNum$Problem,"-",c("PathNum", "Instance")), data_pathNum)
data_pathNum <- select(data_pathNum, -Problem, -Algorithm, -Neighborhood, -AlphaValue)


# group data by density
gr_data_pathNum <- group_by(data_pathNum, PathNum)

# order data by density
gr_data_pathNum <- arrange(gr_data_pathNum, PathNum)

# summarize data by calculating mean and median values for each module size
# also transform time from values in msec to values in seconds
smry_pathNum <- summarise(gr_data_pathNum, 
                          mean_Time = mean(Time) / 1000, 
                          mean_Iterations = mean(Iterations),
                          median_Time = median(Time) / 1000,
                          median_Iterations = median(Iterations)
)

## Hanlde ModuleSize-Data
# Read the data from csv-file produced by the C++-Program
data_moduleSize <- read.csv2(file = "RandomModuleSize.csv", dec = ".", strip.white = T, colClasses = c('character', 'factor', 'factor','factor','numeric','numeric') );

# use dplyr-Package for easier handling
library(dplyr)

# use reshape2-Package for colsplit-function
library(reshape2)


# reduce problem name to problem parameter
data_moduleSize$Problem <- gsub("^KH_moduleSize","",data_moduleSize$Problem)  # remove KH_path from problem name
data_moduleSize$Problem <- gsub(".dat$","",data_moduleSize$Problem)  # remove .dat from problem name
data_moduleSize <- cbind(colsplit(data_moduleSize$Problem,"-",c("ModuleSize", "Instance")), data_moduleSize)
data_moduleSize <- select(data_moduleSize, -Problem, -Algorithm, -Neighborhood, -AlphaValue)


# group data by density
gr_data_moduleSize <- group_by(data_moduleSize, ModuleSize)

# order data by density
gr_data_moduleSize <- arrange(gr_data_moduleSize, ModuleSize)

# summarize data by calculating mean and median values for each module size
# also transform time from values in msec to values in seconds
smry_moduleSize <- summarise(gr_data_moduleSize, 
                             mean_Time = mean(Time) / 1000, 
                             mean_Iterations = mean(Iterations),
                             median_Time = median(Time) / 1000,
                             median_Iterations = median(Iterations)
)


## Handle InterModular-Data
# Read the data from csv-file produced by the C++-Program
data_interModular <- read.csv2(file = "RandomInterModular.csv", dec = ".", strip.white = T, colClasses = c('character', 'factor', 'factor','factor','numeric','numeric') );

# use dplyr-Package for easier handling
library(dplyr)

# use reshape2-Package for colsplit-function
library(reshape2)


# reduce problem name to problem parameter
data_interModular$Problem <- gsub("^KH_intermodular","",data_interModular$Problem)  # remove KH_path from problem name
data_interModular$Problem <- gsub(".dat$","",data_interModular$Problem)  # remove .dat from problem name
data_interModular <- cbind(colsplit(data_interModular$Problem,"-",c("InterModularNum", "Instance")), data_interModular)
data_interModular <- select(data_interModular, -Problem, -Algorithm, -Neighborhood, -AlphaValue)


# group data by density
gr_data_interModular <- group_by(data_interModular, InterModularNum)

# order data by density
gr_data_interModular <- arrange(gr_data_interModular, InterModularNum)

# summarize data by calculating mean and median values for each module size
# also transform time from values in msec to values in seconds
smry_interModular <- summarise(gr_data_interModular, 
                               mean_Time = mean(Time) / 1000, 
                               mean_Iterations = mean(Iterations),
                               median_Time = median(Time) / 1000,
                               median_Iterations = median(Iterations)
)


## start plotting
png(filename = "RandomAllFour.png",
    width = 13,
    height = 12,
    units = "cm",
    res = 600,
    pointsize = 10,
    #type = "windows",
    family = "serif",
    antialias = "cleartype"
)


# Multi-plot layout
par(mfrow=c(2,2))
par(mar = c(4,4,2,2))
y_limits = c(0,5)

# density plot
plot(x = smry_density$Density, y = smry_density$median_Time, type = 'l', xlab = "Besetzungsdichte [%]", ylab = "Laufzeit [s]", ylim = y_limits)
par(new = T)
plot(x = smry_density$Density, y = smry_density$median_Time, type = 'p', xlab = NA, ylab = NA, pch = 20,  ylim = y_limits)

# pathNum plot
plot(log = "x", x = smry_pathNum$PathNum, y = smry_pathNum$median_Time, type = 'l', xlab = "Dienstleistungspfade", ylab = "Laufzeit [s]", ylim=y_limits)
par(new = T)
plot(log = "x", x = smry_pathNum$PathNum, y = smry_pathNum$median_Time, type = 'p', xlab = NA, ylab = NA, pch = 20, ylim = y_limits)

# moduleSize plot
plot(x = smry_moduleSize$ModuleSize, y = smry_moduleSize$median_Time, type = 'l', xlab = "intramodulare Klassen", ylab = "Laufzeit [s]",  ylim = y_limits)
par(new = T)
plot(x = smry_moduleSize$ModuleSize, y = smry_moduleSize$median_Time, type = 'p', xlab = NA, ylab = NA, pch = 20,  ylim = y_limits)

# interModular plot
plot(x = smry_interModular$InterModularNum, y = smry_interModular$median_Time, type = 'l', xlab = "intermodulare Klassen", ylab = "Laufzeit [s]",  ylim = y_limits)
par(new = T)
plot(x = smry_interModular$InterModularNum, y = smry_interModular$median_Time, type = 'p', xlab = NA, ylab = NA, pch = 20,  ylim = y_limits)

dev.off()
