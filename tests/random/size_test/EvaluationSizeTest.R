# Read the data from csv-file produced by the C++-Program
data_size <- read.csv2(file = "RandomSize.csv", dec = ".", strip.white = T, colClasses = c('character', 'factor', 'factor','factor','numeric','numeric') );

# use dplyr-Package for easier handling
library(dplyr)

# use reshape2-Package for colsplit-function
library(reshape2)


# reduce problem name to problem parameter
data_size$Problem <- gsub("^KH_size","",data_size$Problem)  # remove KH_density from problem name
data_size$Problem <- gsub(".dat$","",data_size$Problem)        # remove .dat from problem name
data_size <- cbind(colsplit(data_size$Problem,"-",c("Density", "Instance")), data_size)
data_size <- select(data_size, -Problem, -Algorithm, -Neighborhood, -AlphaValue)


# group data by density
gr_data_size <- group_by(data_size, Density)

# order data by density
gr_data_size <- arrange(gr_data_size, Density)

# summarize data by calculating mean and median values for each module size
# also transform time from values in msec to values in seconds
smry_size <- summarise(gr_data_size, 
          mean_Time = mean(Time) / 1000, 
          mean_Iterations = mean(Iterations),
          median_Time = median(Time) / 1000,
          median_Iterations = median(Iterations)
    )

# plot summary
png(filename = "GroesseVsLaufzeit.png",
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
plot(x = smry_size$Density, y = smry_size$mean_Time, type = 'l', xlab = "Anzahl Leistungselemente", ylab = "Laufzeit [s]")
par(new = T)
plot(x = smry_size$Density, y = smry_size$mean_Time, type = 'p', xlab = NA, ylab = NA, pch = 20)

dev.off()