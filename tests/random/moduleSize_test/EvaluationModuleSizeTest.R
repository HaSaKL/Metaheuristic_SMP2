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

# plot summary
png(filename = "ModuleSizeVsLaufzeit.png",
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
plot(x = smry_moduleSize$ModuleSize, y = smry_moduleSize$mean_Time, type = 'l', xlab = "Anzahl der inramodularen Koordinationskostenklassen", ylab = "Laufzeit in Sekunden")
par(new = T)
plot(x = smry_moduleSize$ModuleSize, y = smry_moduleSize$mean_Time, type = 'p', xlab = NA, ylab = NA, pch = 20)

dev.off()