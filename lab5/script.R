results = read.csv("resultO0.csv", sep = ";")

naive_time_mean = aggregate(naive_time ~ columns_and_rows, data = results, FUN = mean)
better_time_mean = aggregate(better_time ~ columns_and_rows, data = results, FUN = mean)
blas_time_mean = aggregate(blas_time ~ columns_and_rows, data = results, FUN = mean)
#naive
naive_time_mean$sd = aggregate( naive_time ~ columns_and_rows, data=results, FUN=sd)$naive_time

naive_plot <- ggplot(naive_time_mean, aes(x=columns_and_rows, y=naive_time)) + geom_point(color="red") +  
      geom_errorbar(aes(ymin=naive_time - sd, ymax=naive_time + sd)) + labs(title="Naive mulitplication time", 
                        x="Size", y = "Time") + theme_light()
naive_plot

#better
better_time_mean$sd = aggregate( better_time ~ columns_and_rows, data=results, FUN=sd)$better_time
better_plot <- ggplot(better_time_mean, aes(x=columns_and_rows, y=better_time)) + geom_point(color="red") +  
  geom_errorbar(aes(ymin=better_time - sd, ymax=better_time + sd)) + labs(title="Better mulitplication time", 
                                                                        x="Size", y = "Time") + theme_light()
better_plot
#blas
blas_time_mean$sd = aggregate(blas_time ~ columns_and_rows, data=results, FUN=sd)$blas_time
blas_plot <- ggplot(blas_time_mean, aes(x=columns_and_rows, y=blas_time)) + geom_point(color="red") +  
  geom_errorbar(aes(ymin=blas_time - sd, ymax=blas_time + sd)) + labs(title="BLAS mulitplication time", 
                                                                          x="Size", y = "Time") + theme_light()
blas_plot

