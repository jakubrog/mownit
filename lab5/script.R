results = read.csv("resultO0.csv", sep = ";")

naive_time_mean = aggregate(naive_time ~ columns_and_rows, data = results, FUN = mean)
better_time_mean = aggregate(better_time ~ columns_and_rows, data = results, FUN = mean)
blas_time_mean = aggregate(blas_time ~ columns_and_rows, data = results, FUN = mean)

####################
#naive
####################
naive_time_mean$sd = aggregate( naive_time ~ columns_and_rows, data=results, FUN=sd)$naive_time

naive_plot <- ggplot(naive_time_mean, aes(x=columns_and_rows, y=naive_time)) + geom_point(color="red") +  
      geom_errorbar(aes(ymin=naive_time - sd, ymax=naive_time + sd)) + labs(title="Naive mulitplication time", 
                        x="Size", y = "Time") + theme_light()
naive_plot

#polynomial
fit_naive = lm( naive_time ~ poly(columns_and_rows, 3, raw=TRUE), data=naive_time_mean)
naive_data = data.frame(columns_and_rows = seq(50,1000, len=250))
naive_data$y = predict(fit_naive, naive_data)
last_plot() + geom_line(data=naive_data, aes(columns_and_rows,y), col = "blue")

####################
#better
####################
better_time_mean$sd = aggregate( better_time ~ columns_and_rows, data=results, FUN=sd)$better_time
better_plot <- ggplot(better_time_mean, aes(x=columns_and_rows, y=better_time)) + geom_point(color="red") +  
  geom_errorbar(aes(ymin=better_time - sd, ymax=better_time + sd)) + labs(title="Better mulitplication time", 
                                                                        x="Size", y = "Time") + theme_light()
better_plot

#polynomial
fit_better = lm( better_time ~ poly(columns_and_rows, 3, raw=TRUE), data=better_time_mean)
better_data = data.frame(columns_and_rows = seq(50,1000, len=250))
better_data$y = predict(fit_better, better_data)
last_plot() + geom_line(data=better_data, aes(columns_and_rows,y), col = "blue")

####################
#blas
####################
blas_time_mean$sd = aggregate(blas_time ~ columns_and_rows, data=results, FUN=sd)$blas_time
blas_plot <- ggplot(blas_time_mean, aes(x=columns_and_rows, y=blas_time)) + geom_point(color="red") +  
  geom_errorbar(aes(ymin=blas_time - sd, ymax=blas_time + sd)) + labs(title="BLAS mulitplication time", 
                                                                          x="Size", y = "Time") + theme_light()
blas_plot

#polynomial
fit_blas = lm( blas_time ~ poly(columns_and_rows, 3, raw=TRUE), data=blas_time_mean)
blas_data = data.frame(columns_and_rows = seq(50,1000, len=250))
blas_data$y = predict(fit_blas, blas_data)
last_plot() + geom_line(data=blas_data, aes(columns_and_rows,y), col = "blue")

##################
##COMPARSION
##################
plot(naive_data, type='l', lwd = 2, ylab = "Time", xlab = "Size", main = "Comparsion", col = "Red")
lines(better_data, lwd = 2, col = "Orange")
lines(blas_data, lwd = 2, col = "darkgreen")
legend("topleft", col = c("red", "orange", "darkgreen"), legend = c("naive", "better", "blas"), lty = 1 )