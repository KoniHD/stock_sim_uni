import argparse
import pandas as pd
import matplotlib.pyplot as plt

def main(optt):
    print("Plotting the resulting data.")


    data = pd.read_csv(opt.input_file)

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
    output_pdf = f'{opt.output_directory}/stock_prices_plot.pdf'
    plt.savefig(output_pdf, format='pdf')

def parse_opt(known=False):
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input-file', type=str, default='output/market_performance.csv', help='path of .csv data file')
    parser.add_argument('-o', '--output-directory', type=str, default='output', help='directory for .pdf plot.')

    return parser.parse_known_args()[0] if known else parser.parse_args()


if __name__ == "__main__":
    opt = parse_opt()
    main(opt)