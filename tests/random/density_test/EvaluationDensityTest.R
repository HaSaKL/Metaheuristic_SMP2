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

# plot summary
png(filename = "DichteVsLaufzeit.png",
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
plot(x = smry_density$Density, y = smry_density$median_Time, type = 'l', xlab = "Besetzungsdichte in Prozent", ylab = "Laufzeit in Sekunden")
par(new = T)
plot(x = smry_density$Density, y = smry_density$median_Time, type = 'p', xlab = NA, ylab = NA, pch = 20)

dev.off()