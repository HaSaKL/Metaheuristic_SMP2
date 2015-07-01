# Read the data from csv-file produced by the C++-Program
data <- read.csv2(file = "ModuleTest16-13-7-a.csv", dec = ".", strip.white = T, colClasses = c('character', 'factor', 'factor','factor','numeric','numeric') );

## get nice summary table
# use dplyr-Packe for easier handling
library(dplyr)

# group data by module size (coded in problem name)
gr_data <- group_by(data, Problem)

# order data by module size
gr_data <- arrange(gr_data, Problem)


# filter data for alpha
gr_data <- filter(gr_data, AlphaValue == "0.1")

# summarize data by calculating mean and median values for each module size
smry <- summarise(gr_data, 
          mean_Time = mean(Time), 
          mean_Iterations = mean(Iterations),
          median_Time = median(Time),
          median_Iterations = median(Iterations)
    )

# rename problem to number describing module size, e.g. 'M06.dat' -> '6'
smry$Problem <- as.integer(substring(smry$Problem,2,3))

# ggplot(smry, aes(Problem))  +
#     geom_line(aes(y = mean_Time, color = "Time")) +
#     geom_line(aes(y = mean_Iterations, color = "Iterations")) +
#     scale_colour_grey(start = 0.5, end = 0) +
#     theme_bw(base_size = 12)

png(filename = "ModulzahlVsLaufzeit.png",
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
plot(x = smry$Problem, y = smry$mean_Time, type = 'l', xlab = "Modulzahl", ylab = "Laufzeit in ms")
par(new = T)
plot(x = smry$Problem, y = smry$mean_Time, type = 'p', xlab = NA, ylab = NA, pch = 20)
par(new = T)
plot(x = smry$Problem, y = smry$mean_Iterations, type = 'l', lty=3, axes = F, xlab = NA, ylab = NA)
par(new = T)
plot(x = smry$Problem, y = smry$mean_Iterations, type = 'p',  axes = F, xlab = NA, ylab = NA, pch = 20)
axis(side = 4)
mtext(side = 4, line = 3, "GRASP-Iterationen")
legend(11.0, 13, c("Laufzeit","Iterationen"), lty=c(1,3), bty = "n")

dev.off()