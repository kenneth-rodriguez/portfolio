# Ken Rodriguez
# Here are some unit tests for our humble csv-combining script.
import sys
import unittest
import pandas as pd

from csv_combiner import CsvCombiner
from io import StringIO


class TestCsvCombiner(unittest.TestCase):
    # initialize variables for EZ testing
    csv_combiner = CsvCombiner()
    output_path = "combined.csv"
    combiner_path = "./csv_combiner.py"
    accessories = "test_fixtures/accessories.csv"
    clothing = "test_fixtures/clothing.csv"
    household_cleaners = "test_fixtures/household_cleaners.csv"

    # "wrong" variables for unit testing
    text_file = "./text_fixtures/textfile.txt"
    missing_file = ""

    #
    # TESTS
    #

    # test "correct" inputs
    def test_correct_inputs(self):
        argument = [self.combiner_path, self.accessories, self.clothing, self.household_cleaners]
        self.csv_combiner.combine_files(argument)

        # count the number of rows in the complete document then each individual document.
        # if the number of rows is equal, each line was successfully added to the complete doc
        combined_doc = pd.read_csv(self.output_path)
        access_doc = pd.read_csv(self.accessories)
        clothes_doc = pd.read_csv(self.clothing)
        house_doc = pd.read_csv(self.household_cleaners)

        self.assertEqual(len(combined_doc), (len(access_doc) + len(clothes_doc) + len(house_doc)))

    # test for no arguments
    def test_no_argument(self):
        self.string_output = StringIO()
        sys.stdout = self.string_output
        argument = []
        self.csv_combiner.combine_files(argument)
        self.assertTrue("No arguments found." in self.string_output.getvalue())

    # test incorrect filetype argument
    def test_incorrect_filetype(self):
        self.string_output = StringIO()
        sys.stdout = self.string_output
        argument = [self.combiner_path, self.text_file]
        self.csv_combiner.combine_files(argument)
        self.assertTrue("ERROR: argument may be invalid or not a CSV." in self.string_output.getvalue())

    # test no file argument
    def test_no_file(self):
        self.string_output = StringIO()
        sys.stdout = self.string_output
        argument = [self.combiner_path, self.missing_file]
        self.csv_combiner.combine_files(argument)
        self.assertTrue("ERROR: argument may be invalid or not a CSV." in self.string_output.getvalue())
