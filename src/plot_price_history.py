import pandas as pd
import matplotlib.pyplot as plt
import sys

print("Plotting the resulting data.")

# file_path = "output/market_performance.csv"
file_path = sys.argv[1]
output_path = sys.argv[2]

data = pd.read_csv(file_path)

# Plotting the data
plt.figure(figsize=(12, 6))
for company in data.columns:
    plt.plot(data.index, data[company], label=company)

# Adding labels, title, and legend
plt.xlabel('Time Steps')
plt.xlim(left=0)
plt.ylabel('Stock Price')
plt.ylim(bottom=0)
plt.title('Stock Price of each Company over Time')
plt.legend(loc='upper right')
plt.grid(True)

# Save the plot to a PDF file
output_pdf = f'{output_path}/stock_prices_plot.pdf'
plt.savefig(output_pdf, format='pdf')

# Display the plot
# plt.show()
