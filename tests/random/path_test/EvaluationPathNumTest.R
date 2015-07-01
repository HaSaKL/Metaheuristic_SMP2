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

# plot summary
png(filename = "PfadeVsLaufzeit.png",
    width = 13,
    height = 7,
    units = "cm",
    res = 600,
    pointsize = 10,
    #type = "windows",
    family = "serif",
    antialias = "cleartype"
    )

par(mar = c(4,4,1,4))
plot(log = "x",x = smry_pathNum$PathNum, y = smry_pathNum$mean_Time, type = 'l', xlab = "Anzahl Dienstleistungspfade", ylab = "Laufzeit in Sekunden")
par(new = T)
plot(log = "x",x = smry_pathNum$PathNum, y = smry_pathNum$mean_Time, type = 'p', xlab = NA, ylab = NA, pch = 20)

dev.off()