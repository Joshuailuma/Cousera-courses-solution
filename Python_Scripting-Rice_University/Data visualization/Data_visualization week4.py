"""
Project for Week 4 of "Python Data Visualization".
Unify data via common country codes.

Be sure to read the project description page for further information
about the expected behavior of the program.
"""

import csv
import math
import pygal


def build_country_code_converter(codeinfo):
    """
    Inputs:
      codeinfo      - A country code information dictionary

    Output:
      A dictionary whose keys are plot country codes and values
      are world bank country codes, where the code fields in the
      code file are specified in codeinfo.
    """
    table = {}
    # Read the csv file
    with open(codeinfo['codefile'], 'r') as csvfile:
        csvreader = csv.DictReader(csvfile, delimiter=codeinfo['separator'],
                                   quotechar=codeinfo['quote'])
        # Loop through csv reader and ger required info
        for row in csvreader:
            key = row[codeinfo['plot_codes']]
            table[key] = row[codeinfo['data_codes']]

    return table


def reconcile_countries_by_code(codeinfo, plot_countries, gdp_countries):
    """
    Inputs:
      codeinfo       - A country code information dictionary
      plot_countries - Dictionary whose keys are plot library country codes
                       and values are the corresponding country name
      gdp_countries  - Dictionary whose keys are country codes used in GDP data

    Output:
      A tuple containing a dictionary and a set.  The dictionary maps
      country codes from plot_countries to country codes from
      gdp_countries.  The set contains the country codes from
      plot_countries that did not have a country with a corresponding
      code in gdp_countries.

      Note that all codes should be compared in a case-insensitive
      way.  However, the returned dictionary and set should include
      the codes with the exact same case as they have in
      plot_countries and gdp_countries.
    """
    code_converter = build_country_code_converter(codeinfo)

    final_dict = {}
    final_set = set()
    for plot_key, plot_value in plot_countries.items():
        for code_key, code_value in code_converter.items():
            if (plot_key.lower() == code_key.lower()) and (plot_value != "") and (code_value != ""):
                for key1, value1 in gdp_countries.items():
                    if key1.lower() == code_value.lower() and value1 != "":
                        final_dict[plot_key] = key1

    for plot_key, plot_value in plot_countries.items():
        for code_key, code_value in code_converter.items():
            if plot_key.lower() == code_key.lower() and code_value.upper() not in gdp_countries:
                final_set.add(plot_key)

    return final_dict, set(final_set)


def build_map_dict_by_code(gdpinfo, codeinfo, plot_countries, year):
    """
    Inputs:
      gdpinfo        - A GDP information dictionary
      codeinfo       - A country code information dictionary
      plot_countries - Dictionary mapping plot library country codes to country names
      year           - String year for which to create GDP mapping
    Output:
      A tuple containing a dictionary and two sets.  The dictionary
      maps country codes from plot_countries to the log (base 10) of
      the GDP value for that country in the specified year.  The first
      set contains the country codes from plot_countries that were not
      found in the GDP data file.  The second set contains the country
      codes from plot_countries that were found in the GDP data file, but
      have no GDP data for the specified year.
    """
    plot_dict_1 = {}
    new_data_dict = {}
    plot_set_2 = set()
    # Read from the gdp file
    with open(gdpinfo['gdpfile'], 'r') as csvfile:
        csv_reader = csv.DictReader(
            csvfile, delimiter=gdpinfo['separator'], quotechar=gdpinfo['quote'])
        for row in csv_reader:
            # Read data of contry code into new_data_dict
            new_data_dict[row[gdpinfo['country_code']]] = dict(row)

    # Deconstruct reconcile_countries_by_code
    plot_dict, plot_set_1 = reconcile_countries_by_code(
        codeinfo, plot_countries, new_data_dict)

    plot_set_1.clear()
    val = ""
    for key in plot_countries:
        #    for codekey in plot_dict:
        if key in plot_dict:
            val = plot_dict[key]
        else:
            plot_set_1.add(key)
        if val != "" and val not in new_data_dict:
            plot_set_1.add(key)

    for key in plot_dict:
        for key1 in new_data_dict:
            if plot_dict[key].lower() == key1.lower():
                if new_data_dict[key1][year] != '':
                    plot_dict_1[key] = math.log(
                        float(new_data_dict[key1][year]), 10)
                else:
                    plot_set_2.add(key)

    return plot_dict_1, set(plot_set_1), set(plot_set_2)


def test_render_world_map():
    """
    Test the project code for several years
    """
    gdpinfo = {
        "gdpfile": "isp_gdp.csv",
        "separator": ",",
        "quote": '"',
        "min_year": 1960,
        "max_year": 2015,
        "country_name": "Country Name",
        "country_code": "Country Code"
    }

    codeinfo = {
        "codefile": "isp_country_codes.csv",
        "separator": ",",
        "quote": '"',
        "plot_codes": "ISO3166-1-Alpha-2",
        "data_codes": "ISO3166-1-Alpha-3"
    }

    # Get pygal country code map
    pygal_countries = pygal.maps.world.COUNTRIES

    # 1960
    render_world_map(gdpinfo, codeinfo, pygal_countries,
                     "1960", "isp_gdp_world_code_1960.svg")

    # 1980
    render_world_map(gdpinfo, codeinfo, pygal_countries,
                     "1980", "isp_gdp_world_code_1980.svg")

    # 2000
    render_world_map(gdpinfo, codeinfo, pygal_countries,
                     "2000", "isp_gdp_world_code_2000.svg")

    # 2010
    render_world_map(gdpinfo, codeinfo, pygal_countries,
                     "2010", "isp_gdp_world_code_2010.svg")


# Make sure the following call to test_render_world_map is commented
# out when submitting to OwlTest/CourseraTest.

test_render_world_map()
