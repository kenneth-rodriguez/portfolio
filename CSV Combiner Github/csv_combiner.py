# written by Ken Rodriguez
# PMG Interview Problem: CSV Combiner
#   This is script that takes commandline arguments to execute a Python script to read multiple CSV
#   files and output a combined CSV file. To do this, the sys library interprets arguments, os reads files based
#   on those arguments, then pandas reads and concatenates the files into one great big CSV.
# 10/23/2022

import sys  # read arguments w/ argv
import os  # "find" files specified by arguments
import pandas as pd  # read CSV once we've found it


class CsvCombiner:

    # method to append rows with a column describing the file they're from
    @staticmethod
    def append_filename(input_file):
        old_csv = pd.read_csv(input_file)
        filename_csv = pd.DataFrame()

        # split file into distinct columns, then append the filename to the end of each row.
        old_csv['filename'] = input_file.split('/')[-1]
        filename_csv = pd.concat([old_csv, filename_csv])

        return filename_csv

    @staticmethod
    def combine_files(arguments):
        # create an empty structure to hold CSV data
        output_csv = pd.DataFrame()

        # find the number of arguments in the command line
        n = len(arguments)

        # if no arguments are included
        if n <= 1:
            print("No arguments found.")
            return False

        # iterate through each argument, skipping the first as it executes the script
        for x in range(1, n):
            # check if the proposed argument is a FILE
            if os.path.isfile(arguments[x]):
                if arguments[x].endswith('csv'):
                    # IF the file is a file and also a CSV, update and concatenate the current file w/ output file
                    output_csv = pd.concat([output_csv, CsvCombiner.append_filename(arguments[x])])
                else:
                    print("ERROR: argument may not an acceptable format; try CSV.")
            else:
                print("ERROR: argument may be invalid or not a CSV.")

        # check the number of rows in the output dataframe. if number is greater than 0, print results
        row_count = len(output_csv)
        if row_count > 0:
            output_csv.to_csv('combined.csv', index=False)
            print(output_csv)
        else:
            return False


def main():
    csv_combiner = CsvCombiner()
    csv_combiner.combine_files(sys.argv)


if __name__ == "__main__":
    main()
