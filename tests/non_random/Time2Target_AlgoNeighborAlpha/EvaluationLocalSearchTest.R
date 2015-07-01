# Read the data from csv-file produced by the C++-Program
data <- read.csv2(file = "Test16-13-7.csv", dec = ".", strip.white = T, colClasses = c('factor', 'factor', 'factor','factor','numeric','numeric') );

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
    geom_hline(y=1) + xlim(0,750) +
    facet_grid(Algorithm ~ Neighborhood, labeller = label_both) +
    ylab("ECDF") +
    xlab("Laufzeit")
    
dev.off()

## filter the relevant data points
graph_data1 <- filter(gr_data, Algorithm == '1', Neighborhood == '1', AlphaValue == '0.1')
graph_data2 <- filter(gr_data, Algorithm == '1', Neighborhood == '2', AlphaValue == '0')
graph_data3 <- filter(gr_data, Algorithm == '2', Neighborhood == '1', AlphaValue == 'E')
graph_data4 <- filter(gr_data, Algorithm == '2', Neighborhood == '2', AlphaValue == '0.1')

# combine data for plot
graphdata <- rbind(graph_data1, graph_data2, graph_data3, graph_data4)

# draw plot on different graphdatas
png("ECDF_Neighborhood_Algorithm.png",
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
    geom_hline(y=1) + xlim(0,750) +
    xlab("Laufzeit in ms") +
    ylab("Kumulative Empirische Distributionsfunktion") +
    theme_bw(base_size = 10, base_family="serif") + 
    theme(panel.grid.major = element_blank(),
          panel.grid.minor = element_blank(),
          panel.border = element_blank(),
          axis.line = element_line(size=.7, color = "black"),
          legend.position = c(.85,.30),
          legend.box = "vertical",
          legend.title = element_text(face = "plain"),
          legend.key = element_rect(color = "white")
         )
    
dev.off()