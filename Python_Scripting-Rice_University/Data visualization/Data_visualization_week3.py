"""
Project for Week 3 of "Python Data Visualization".
Unify data via common country name.

Be sure to read the project description page for further information
about the expected behavior of the program.
"""

import csv
import math
import pygal


def reconcile_countries_by_name(plot_countries, gdp_countries):
    """
    Inputs:
      plot_countries - Dictionary whose keys are plot library country codes
                       and values are the corresponding country name
      gdp_countries  - Dictionary whose keys are country names used in GDP data

    Output:
      A tuple containing a dictionary and a set.  The dictionary maps
      country codes from plot_countries to country names from
      gdp_countries The set contains the country codes from
      plot_countries that were not found in gdp_countries.
    """
    result_dict = {}
    result_set = set()
    # TO get the value of plot countries in plot_countries & store as set
    set_of_plot_countries = set(country[1]
                                for country in plot_countries.items())
    # TO get the value of gdp countries & store as set
    set_of_gdp_countries = set(country for country in gdp_countries.keys())
    # Find the intersection of both
    country_intersect = set_of_plot_countries & set_of_gdp_countries
    plot_countries_kv = {country[1]: country[0]
                         for country in plot_countries.items()}
    for country in country_intersect:
      # Loop through the intersection and store the required field in the resulting dict
        result_dict[plot_countries_kv[country]] = country
    for country in set_of_plot_countries:
        if country not in country_intersect:
            result_set.add(plot_countries_kv[country])

    return result_dict, result_set


def read_csv_as_nested_dict(filename, keyfield, separator, quote):
    """
    Inputs:
      filename  - Name of CSV file
      keyfield  - Field to use as key for rows
      separator - Character that separates fields
      quote     - Character used to optionally quote fields

    Output:
      Returns a dictionary of dictionaries where the outer dictionary
      maps the value in the key_field to the corresponding row in the
      CSV file.  The inner dictionaries map the field names to the
      field values for that row.
    """
    table = {}
    with open(filename, "rt", newline='') as csvfile:
        csvreader = csv.DictReader(
            csvfile, delimiter=separator, quotechar=quote)

        for row in csvreader:
            table[row[keyfield]] = row

    return table


def build_map_dict_by_name(gdpinfo, plot_countries, year):
    """
    Inputs:
      gdpinfo        - A GDP information dictionary
      plot_countries - Dictionary whose keys are plot library country codes
                       and values are the corresponding country name
      year           - String year to create GDP mapping for

    Output:
      A tuple containing a dictionary and two sets.  The dictionary
      maps country codes from plot_countries to the log (base 10) of
      the GDP value for that country in the specified year.  The first
      set contains the country codes from plot_countries that were not
      found in the GDP data file.  The second set contains the country
      codes from plot_countries that were found in the GDP data file, but
      have no GDP data for the specified year.
    """
    base10_dict = dict()
    first_set = set()
    second_set = set()

    # Getting data from gdpinfo
    filename = gdpinfo["gdpfile"]
    keyfield = gdpinfo['country_name']
    separator = gdpinfo['separator']
    quote = gdpinfo['quote']

    # Call read_csv_as_nested_dict and pass in the values
    nested_dict_data = read_csv_as_nested_dict(
        filename, keyfield, separator, quote)
    # Destructure the result of reconcile_contries_by_name
    result_dict, result_set = reconcile_countries_by_name(
        plot_countries, nested_dict_data)

    # Loop through result dict to get country code
    for country_code in result_dict.items():

        # If no GDP data in country, add the code to second set
        indexing = country_code[0]

        if nested_dict_data[result_dict[indexing]][year] == '':
            second_set.add(indexing)
        else:
            print(country_code)
            # If there is GDP data, add the data to the dict
            base10_dict[indexing] = math.log10(
                float(nested_dict_data[result_dict[indexing]][year]))
    # First set with country that contain GDP Data
    first_set = result_set
    return base10_dict, first_set, second_set


def render_world_map(gdpinfo, plot_countries, year, map_file):
    """
    Inputs:
      gdpinfo        - A GDP information dictionary
      plot_countries - Dictionary whose keys are plot library country codes
                       and values are the corresponding country name
      year           - String year to create GDP mapping for
      map_file       - Name of output file to create

    Output:
      Returns None.

    Action:
      Creates a world map plot of the GDP data for the given year and
      writes it to a file named by map_file.
    """
    the_map = pygal.maps.world.World()
    plot, first_set, second_set = build_map_dict_by_name(
        gdpinfo, plot_countries, year)
    the_map.title = 'GDP by country for '+str(year)+' (log scale)'
    the_map.add('GDP for '+str(year), plot)
    the_map.add('Not in world Bank Data', first_set)
    the_map.add('No GDP data', second_set)
    # Show the result in the specified file
    the_map.render_to_file(map_file)


def test_render_world_map():
    """
    Test the project code for several years.
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

    # Get pygal country code map
    pygal_countries = pygal.maps.world.COUNTRIES

    # 1960
    render_world_map(gdpinfo, pygal_countries, "1960",
                     "isp_gdp_world_name_1960.svg")

    # 1980
    render_world_map(gdpinfo, pygal_countries, "1980",
                     "isp_gdp_world_name_1980.svg")

    # 2000
    render_world_map(gdpinfo, pygal_countries, "2000",
                     "isp_gdp_world_name_2000.svg")

    # 2010
    render_world_map(gdpinfo, pygal_countries, "2010",
                     "isp_gdp_world_name_2010.svg")


# Make sure the following call to test_render_world_map is commented
# out when submitting to OwlTest/CourseraTest.

# test_render_world_map()
