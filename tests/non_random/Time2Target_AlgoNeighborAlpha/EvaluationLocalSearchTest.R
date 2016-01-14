# Read the data from csv-file produced by the C++-Program
data <- read.csv2(file = "Test16-13-7.csv", dec = ".", strip.white = T, colClasses = c('factor', 'factor', 'factor','factor','numeric','numeric') );

# label search stategy and neighborhood definition
data$Algorithm <- factor(data$Algorithm,
                          levels = c(1,2),
                          labels = c("Best improvement", "First improvement"))
data$Neighborhood <- factor(data$Neighborhood,
                            levels = c(1,2),
                            labels = c("Adjacent element flip", "Element flip"))

data$AlphaValue <- factor(data$AlphaValue,
                          levels = c("0","0.1","0.3","0.6","1","E","R"),
                          labels = c("purely greedy", 
                                     "alpha = 0.1",
                                     "alpha = 0.3",
                                     "alpha = 0.6",
                                     "purely random",
                                     "uniform random alpha",
                                     "Reactive GRASP"
                                     )
                          )


## get nice summary table
# use dplyr-Packe for easier handling
library(dplyr)

# group data by Neighborhood, Algorithm and Alphavalue
gr_data <- group_by(data, Neighborhood, Algorithm, AlphaValue)

# order data Neighborhood, Algorithm and Alphavalue
gr_data <- arrange(gr_data, Neighborhood, Algorithm, AlphaValue)

# summarize data by calculating mean and median values for each module size for viewing pleasure
smry <- summarise(gr_data, 
                  mean_Time = mean(Time), 
                  mean_Iterations = mean(Iterations),
                  median_Time = median(Time),
                  median_Iterations = median(Iterations)
)

library(ggplot2)

## exploratroy drawing of Time-To-Target Plots to find out good parameter combinations
png("Neighborhood_vs_Algorithm_vs_Alpha.png",
    width = 20,
    height = 20,
    units = "cm",
    res = 1200,
    pointsize = 10,
    family = "serif",
    antialias = "cleartype"
)
ggplot(gr_data, aes(Time + 0.1, color = AlphaValue, linetype = AlphaValue)) + 
    stat_ecdf(geom='line') + 
    geom_hline(yintercept = 1) + xlim(0,750) +
    facet_grid(Algorithm ~ Neighborhood, labeller = label_both) +
    ylab("ECDF") +
    xlab("Runtime")
    
dev.off()

## filter the relevant data points
graph_data1 <- filter(gr_data, Algorithm == "Best improvement", Neighborhood == "Adjacent element flip", AlphaValue == "alpha = 0.1")
graph_data2 <- filter(gr_data, Algorithm == "Best improvement", Neighborhood == "Element flip", AlphaValue == "alpha = 0.1")
graph_data3 <- filter(gr_data, Algorithm == "First improvement", Neighborhood == "Adjacent element flip", AlphaValue == "alpha = 0.1")
graph_data4 <- filter(gr_data, Algorithm == "First improvement", Neighborhood == "Element flip", AlphaValue == "alpha = 0.1")

# combine data for plot
graphdata <- rbind(graph_data1, graph_data2, graph_data3, graph_data4)

# draw plot on different graphdatas
png("ECDF_Neighborhood_Algorithm_ger.png",
    width = 13,
    height = 8,
    units = "cm",
    res = 600,
    pointsize = 10,
    family = "serif",
    antialias = "cleartype"
)

ggplot(graphdata, aes(Time + 0.1, linetype = Neighborhood, color = Algorithm)) +
    stat_ecdf(geom='line') +
    scale_colour_grey(start = 0.6, end=0, name ="Suchalgorithmus", labels = c("Best Improvement", "First Improvement")) +
    scale_linetype_discrete(name = "Nachbarschaft", labels = c("Adj. Element Flip", "Element Flip")) +
    geom_hline(yintercept=1) +
    xlim(0,750) +
    xlab("Laufzeit in ms") +
    ylab("Kumulative Empirische Distributionsfunktion") +
    theme_bw(base_size = 10, base_family="serif") + 
    theme(panel.grid.major = element_blank(),
          panel.grid.minor = element_blank(),
          panel.border = element_blank(),
          axis.line = element_line(size=.7, color = "black"),
          legend.position = c(.85,.30),
          legend.box = "vertical",
          legend.box.just = "left",
          legend.title = element_text(face = "plain"),
          legend.key = element_rect(color = "white")
         )
    
dev.off()

png("ECDF_Neighborhood_Algorithm_eng.png",
    width = 16,
    height = 7,
    units = "cm",
    res = 1200,
    pointsize = 12,
    family = "serif",
    antialias = "cleartype"
)

ggplot(graphdata, aes(Time + 0.1, linetype = Neighborhood, color = Algorithm)) +
  stat_ecdf(geom='line') +
  scale_colour_grey(start = 0.6, end=0, name ="Search Strategy", labels = c("Best Improvement", "First Improvement")) +
  scale_linetype_discrete(name = "Neighborhood ", labels = c("Adjacent Element Flip", "Element Flip")) +
  geom_hline(yintercept = 1) + 
  xlim(0,750) +
  xlab("Runtime in msec") +
  ylab("Empirical Cumulative \n Distribution Function") +
  theme_bw(base_size = 12, base_family="serif") + 
  theme(panel.grid.major = element_blank(),
        panel.grid.minor = element_blank(),
        panel.border = element_blank(),
        axis.line = element_line(size=.7, color = "black"),
        legend.position = c(.85,.4),
        legend.box = "vertical",
        legend.box.just = "left",
        legend.title = element_text(face = "plain"),
        legend.key = element_rect(color = "white")
  )

dev.off()




graphdata_small = filter(gr_data, Algorithm == "First improvement", Neighborhood == "Element flip")

png("Runtime_vs_Construction_Method.png",
    width = 16,
    height = 7,
    units = "cm",
    res = 1200,
    pointsize = 12,
    family = "serif",
    antialias = "cleartype"
)

ggplot(graphdata_small, aes(Time + 0.1, linetype = AlphaValue, color = AlphaValue)) +
  stat_ecdf(geom='line') +
  scale_color_grey(start=0.4, end=0) +
  geom_hline(yintercept = 1) +
  xlim(0,750) +
  xlab("Runtime in msec") +
  ylab("Empirical Cumulative \n Distribution Function") +
  theme_bw(base_size = 12, base_family="serif") + 
  theme(panel.grid.major = element_blank(),
        panel.grid.minor = element_blank(),
        panel.border = element_blank(),
        axis.line = element_line(size=.7, color = "black"),
        legend.position = c(.85,0.5),
        legend.box = "vertical",
        legend.box.just = "left",
        legend.title = element_text(face = "plain"),
        legend.key = element_rect(color = "white")
  )

dev.off()