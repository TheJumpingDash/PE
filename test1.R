# Read main dataset
data <- read.csv("\\\\wsl$\\Ubuntu\\home\\nitus\\PE\\PE\\bin\\cut_and_shuffle_20.csv")

# Read second dataset (for extra curve)
data2 <- read.csv("\\\\wsl$\\Ubuntu\\home\\nitus\\PE\\PE\\bin\\randomize1.csv")
row_extra <- as.numeric(data2[1, ])

# Get every 5th row, starting from row 1 
idx <- seq(1, nrow(data), by = 2)
data <- data[idx, ]

# Flatten all values to compute global x range
all_values <- c(as.numeric(as.matrix(data)), row_extra)

x <- seq(
  mean(all_values, na.rm = TRUE) - 4 * sd(all_values, na.rm = TRUE),
  mean(all_values, na.rm = TRUE) + 4 * sd(all_values, na.rm = TRUE),
  length.out = 1000
)

# Colors for main curves
cols <- rainbow(nrow(data), start = 0, end = 5/6)

# Compute global ymax
ymax <- 0

for (i in 1:nrow(data)) {
  row <- as.numeric(data[i, ])
  mu <- mean(row, na.rm = TRUE)
  sigma <- sd(row, na.rm = TRUE)

  if (!is.na(sigma) && sigma > 0) {
    y <- dnorm(x, mean = mu, sd = sigma)
    ymax <- max(ymax, max(y, na.rm = TRUE))
  }
}

# Include extra curve in ymax
mu2 <- mean(row_extra, na.rm = TRUE)
sigma2 <- sd(row_extra, na.rm = TRUE)

if (!is.na(sigma2) && sigma2 > 0) {
  y2 <- dnorm(x, mean = mu2, sd = sigma2)
  ymax <- max(ymax, max(y2, na.rm = TRUE))
}

# Initialize density plot
plot(NULL,
     xlim = range(x),
     ylim = c(0, ymax * 1.1),
     xlab = "Value",
     ylab = "Density")

# Plot main curves
for (i in 1:nrow(data)) {
  row <- as.numeric(data[i, ])
  mu <- mean(row, na.rm = TRUE)
  sigma <- sd(row, na.rm = TRUE)

  if (!is.na(sigma) && sigma > 0) {
    lines(x,
          dnorm(x, mean = mu, sd = sigma),
          col = cols[i],
          lwd = 2)
  }
}

# Plot extra curve (randomize.csv)
if (!is.na(sigma2) && sigma2 > 0) {
  lines(x,
        dnorm(x, mean = mu2, sd = sigma2),
        col = "black",
        lwd = 3,
        lty = 2)
}

# # ---- QQ PLOT for last row of main data ----

# last_row <- as.numeric(data[nrow(data), ])
# last_row <- last_row[!is.na(last_row)]

# qqnorm(last_row,
#        main = "QQ Plot (last row of main dataset)")
# qqline(last_row, col = "red", lwd = 2)