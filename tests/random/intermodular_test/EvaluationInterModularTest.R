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

# plot summary
png(filename = "InterModularVsLaufzeit.png",
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
plot(log = "x", x = smry_interModular$InterModularNum, y = smry_interModular$mean_Time, type = 'l', xlab = "Anzahl der intermodularen Koordinationskostenklassen", ylab = "Laufzeit in Sekunden")
par(new = T)
plot(log = "x", x = smry_interModular$InterModularNum, y = smry_interModular$mean_Time, type = 'p', xlab = NA, ylab = NA, pch = 20)

dev.off()